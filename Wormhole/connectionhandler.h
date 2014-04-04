#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "peer.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QPointer>

typedef QPointer<QTcpSocket> SocketPointer;

class ConnectionHandler : public QObject
{
	Q_OBJECT
	
public:
	ConnectionHandler(QObject *parent = 0);
	~ConnectionHandler();

	void start(quint16 port);
	void stop();

	SocketPointer getConnection(Peer peer);
	QList<SocketPointer> getAllConnections() const;

	void disconnect(Peer peer);

	void addTrustedPeer(Peer peer);
	void removeTrustedPeer(Peer peer);
	QSet<Peer> getTrustedPeers() const;

private slots:
	void newConnection();

protected:
	virtual bool requestAcceptConnection(Peer peer) const;

private:
	Q_DISABLE_COPY(ConnectionHandler);

	QTcpServer server;	
	QHash<Peer, SocketPointer> connections;
	QSet<Peer> trustedPeers;
};

#endif // CONNECTIONHANDLER_H
