#include "connectionhandler.h"

#include <QMessageBox>

ConnectionHandler::ConnectionHandler(QObject *parent)
	: QObject(parent)
	, server(this)
{
	QObject::connect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

ConnectionHandler::~ConnectionHandler()
{
	server.close();

	foreach (SocketPointer socket, connections.values()) {
		if (!socket.isNull()) {
			socket->close();
			socket->deleteLater();
		}
	}
}

SocketPointer ConnectionHandler::getConnection(Peer peer)
{
	SocketPointer socket = connections.value(peer);

	// socket is null in case of disconnection (SIGNAL/SLOT) or if not in list at all
	if (socket.isNull() || socket->state() != QAbstractSocket::ConnectedState)  {
		socket = new QTcpSocket(this);
		QObject::connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

		socket->connectToHost(peer.getAddress(), peer.getPort());

		if (socket->state() == QAbstractSocket::ConnectedState || socket->waitForConnected()) {
			trustedPeers.insert(peer);
			connections.insert(peer, socket);
		}
		else {
			qCritical("TCP Connection to '%s' failed: %s", peer.toString().toStdString().c_str(), socket->errorString().toStdString().c_str());
			socket->close();
			delete socket;
		}
	}

	return socket;
}

void ConnectionHandler::newConnection()
{
	SocketPointer connection = server.nextPendingConnection();

	Peer peer(connection->peerAddress(), connection->peerPort());

	if (trustedPeers.contains(peer) || requestAcceptConnection(peer)) {
		trustedPeers.insert(peer);
		connections.insert(peer, connection);
	}
	else {
		qDebug("Connection from %s rejected.", peer.toString().toStdString().c_str());
	}
}

bool ConnectionHandler::requestAcceptConnection(Peer peer) const
{
	QMessageBox messageBox;
	messageBox.setIcon(QMessageBox::Question);
	messageBox.setText(tr("Do you want to accept the incoming connection from '%1'?").arg(peer.toString()));
	messageBox.addButton(QMessageBox::Yes);
	messageBox.addButton(QMessageBox::No);
	int result = messageBox.exec();

	switch (result) {
	case QMessageBox::Yes:
		return true;
		break;
	case QMessageBox::No:
		return false;
		break;
	}

	return false;
}

QList<SocketPointer> ConnectionHandler::getAllConnections() const
{
	return connections.values();
}

void ConnectionHandler::start(quint16 port)
{
	server.listen(QHostAddress::Any, port);
}

void ConnectionHandler::stop()
{
	if (server.isListening()) {
		server.close();
	}
}

void ConnectionHandler::disconnect(Peer peer)
{
	SocketPointer socket = connections.value(peer);
	if (!socket.isNull()) {
		socket->close();
		delete socket;
	}
	connections.remove(peer);
}

void ConnectionHandler::addTrustedPeer(Peer peer)
{
	trustedPeers.insert(peer);
}

void ConnectionHandler::removeTrustedPeer(Peer peer)
{
	trustedPeers.remove(peer);
}

QSet<Peer> ConnectionHandler::getTrustedPeers() const
{
	return trustedPeers; // I am aware of copying here!
}

