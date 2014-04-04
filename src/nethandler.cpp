#include "nethandler.h"

#include <QBuffer>
#include <QDebug>

#include <google/protobuf/io/coded_stream.h>
#include "qtprotobuf.h"
#include "file.pb.h"


NetHandler::NetHandler(QObject *parent)
	: QObject(parent)
	, streamVersion(QDataStream::Qt_4_0)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
}

NetHandler::~NetHandler()
{
	// do NOT delete the device ;)
}

void NetHandler::handle(QIODevice* device, Message** outMessage, MessageType* outType)
{
	QDataStream stream(device);
	stream.setVersion(streamVersion);

	qint64 size;
	qint64 type;

	stream >> size;
	stream >> type;

	Message* message = 0;
	switch (type) {
	case FILE_MESSAGE:
		message = new FileMessage();
		break;
	case FILE_PART_MESSAGE:
		message = new FilePartMessage();
		break;
	case MIME_MESSAGE:
		message = new MimeMessage();
		break;
	default:
		qWarning("Unknown packet type %d.", type);
		stream.skipRawData(size);
	}
	if (message != 0) {
		stream >> *message;
	}

	*outMessage = message;
	*outType = (MessageType)type;
}

void NetHandler::sendMessage(QIODevice* device, Message* message, MessageType type)
{
	QDataStream stream(device);
	stream.setVersion(streamVersion);

	stream << (qint64)message->ByteSize();
	stream << (qint64)type;
	stream << *message;
}
