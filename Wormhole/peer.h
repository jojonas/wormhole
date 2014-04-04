#ifndef PEER_H
#define PEER_H

#include <QHostAddress>

class Peer
{

public:
	Peer(QHostAddress address, qint16 port);
	~Peer();

	QHostAddress getAddress() const;
	quint16 getPort() const;

	QString toString() const;

private:
	QHostAddress address;
	quint16 port;
};

inline bool operator==(const Peer& p1, const Peer& p2)
{
	return p1.getAddress() == p2.getAddress() && p1.getPort() == p2.getPort();
}

inline uint qHash(const Peer& key, uint seed)
{
	return qHash(key.getAddress(), seed) ^ key.getPort();
}

#endif // PEER_H
