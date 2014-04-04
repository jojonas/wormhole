#include "wormholeservice.h"

#include "nethandler.h"
#include "checksum.h"

WormholeService::WormholeService(QObject *parent)
: QObject(parent)
, connectionManager(this)
, netHandler(this)
, peers()
, chunksize(1024)
, socketReadyReadMapper(this)
, outDirectory(".")
{
	QObject::connect(&socketReadyReadMapper, SIGNAL(mapped(QObject*)), this, SLOT(readSocket(QObject*)));
}

WormholeService::~WormholeService()
{

}

void WormholeService::connectToHost(QHostAddress address, quint16 port)
{
	Peer peer(address, port);
	if (!peers.contains(peer)) {
		SocketPointer socket = connectionManager.getConnection(peer);
		if (!socket.isNull()) {
			QObject::connect(socket, SIGNAL(readyRead()), &socketReadyReadMapper, SLOT(map()));
			peers.insert(peer);
		} 
	}
	else {
		qWarning("Peer list already contains peer %s.", peer.toString().toStdString().c_str());
	}
}

void WormholeService::sendFile(QFile* file)
{
	if (file->open(QIODevice::ReadOnly)) {
		FileMessage fileMessage;

		QFileInfo fileInfo(*file);
		fileMessage.set_filename(fileInfo.fileName().toStdString());
		fileMessage.set_size(fileInfo.size());
		fileMessage.set_parts_count(ceil(file->size() / chunksize));

		sendToAllPeers(&fileMessage, FILE_MESSAGE);

		char* buffer = new char[chunksize];
		while (file->bytesAvailable() > 0) {
			qint64 retval = file->read(buffer, chunksize);
			if (retval >= 0) {
				FilePartMessage filePartMessage;
				filePartMessage.set_length(retval);
				filePartMessage.set_content(buffer, retval);
				filePartMessage.set_checksum(adler32(buffer, retval));

				sendToAllPeers(&filePartMessage, FILE_PART_MESSAGE);

				emit sendProgress(1. - file->bytesAvailable() / fileMessage.size());
			}
			else {
				qWarning("Error while reading file '%s': %s", file->fileName().toStdString().c_str(), file->errorString().toStdString().c_str());
			}
		}

		flushAllPeers();
	}
	else {
		qCritical("Could not open file '%s' for reading.", file->fileName().toStdString().c_str());
	}
}

void WormholeService::sendToAllPeers(Message* message, MessageType type)
{
	foreach (Peer peer, peers) {
		SocketPointer socket = connectionManager.getConnection(peer);
		netHandler.sendMessage(socket, message, type);
	}
}

void WormholeService::flushAllPeers()
{
	foreach(Peer peer, peers) {
		SocketPointer socket = connectionManager.getConnection(peer);
		socket->flush();
	}
}

void WormholeService::readSocket(QObject* object)
{
	QIODevice* socket = dynamic_cast<QIODevice*>(object);

	Message* message = 0;
	MessageType type;
	netHandler.handle(socket, &message, &type);

	if (message != 0) {
		switch (type) {
		case FILE_MESSAGE:
			handleFileMessage(socket, dynamic_cast<FileMessage*>(message));
			break;
		}
		delete message;
	}
}

void WormholeService::handleFileMessage(QIODevice* socket, FileMessage* message)
{
	QFile* file = new QFile(outDirectory.filePath(message->filename().c_str()), this);

	if (file->open(QIODevice::WriteOnly)) {
		const int partsCount = message->parts_count();
		Message* partMessage = 0;
		MessageType partType;
		for (unsigned int i = 0; i < partsCount; i++) {
			netHandler.handle(socket, &partMessage, &partType);
			if (partType == FILE_PART_MESSAGE) {
				FilePartMessage* filePartMessage = dynamic_cast<FilePartMessage*>(partMessage);

				const char* data = filePartMessage->content().c_str();
				const quint32 length = filePartMessage->length();

				if (adler32(data, length) == filePartMessage->checksum()) {
					file->write(data, length);
				}
				else {
					qWarning("Checksum mismatch.");
				}
			}
			else {
				qCritical("Received different type than expected: %d", partType);
			}
			delete partMessage;
			emit receiveProgress((float)(i+1) / partsCount);
		}
		file->close();
		emit receivedFile(file);
	}
	else {
		qCritical("Could not open file '%s' for writing.", file->fileName().toStdString().c_str());
	}
}

QSet<Peer> WormholeService::getPeers() const
{
	return peers; // yes, they are copied. Wanted to keep it thread safe. (Does that help?)
}

int WormholeService::getPeerCount() const
{
	return peers.size();
}

void WormholeService::startListening(quint16 port)
{
	connectionManager.stop();
	connectionManager.start(port);
}

void WormholeService::setOutputDirectory(QDir dir)
{
	outDirectory = dir;
}



