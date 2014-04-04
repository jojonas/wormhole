#ifndef NETHANDLER_H
#define NETHANDLER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QIODevice>

#include <google/protobuf/message.h>
typedef google::protobuf::Message Message;
#include "file.pb.h"

class NetHandler : public QObject
{
	Q_OBJECT

public:
	NetHandler(QObject *parent = 0);
	~NetHandler();

	void handle(QIODevice* device, Message** outMessage, MessageType* outType);
	void sendMessage(QIODevice* device, Message* message, MessageType type);

private:
	Q_DISABLE_COPY(NetHandler);

	const QDataStream::Version streamVersion;
	
};

#endif // NETHANDLER_H
