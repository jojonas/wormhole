#ifndef WORMHOLESERVICE_H
#define WORMHOLESERVICE_H

#include <QObject>

#include <QHostAddress>
#include <QSignalMapper>
#include <QFile>

#include "connectionhandler.h"
#include "nethandler.h"
#include "file.pb.h"

class WormholeService : public QObject
{
	Q_OBJECT

public:
	WormholeService(QObject *parent = 0);
	~WormholeService();

	void connectToHost(QHostAddress address, PortNumber port);
	void startListening(PortNumber port);
	void setOutputDirectory(QDir dir);

	QSet<Peer> getPeers() const;
	int getPeerCount() const;

public slots:
	void sendFile(QFile* file);

signals:
	void receivedFile(QFile* file);
	void sendProgress(float progress);
	void receiveProgress(float progress);

private slots:
	void readSocket(QObject* socket); // must be connected to signal mapper to all sockets!

private:
	Q_DISABLE_COPY(WormholeService);

	void sendToAllPeers(Message* message, MessageType type);
	void flushAllPeers();
	void handleFileMessage(QIODevice* socket, FileMessage* message);

	const quint64 chunksize;
	QDir outDirectory;

	QSet<Peer> peers;
	ConnectionHandler connectionManager;
	NetHandler netHandler;
	QSignalMapper socketReadyReadMapper;
	
};

#endif // WORMHOLESERVICE_H
