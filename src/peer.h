#ifndef PEER_H
#define PEER_H

#include <QHostAddress>

typedef quint16 PortNumber;

class Peer
{

public:
	Peer(QHostAddress address, PortNumber port);
	~Peer();

	QHostAddress getAddress() const;
	PortNumber getPort() const;

	QString toString() const;

private:
	QHostAddress address;
	PortNumber port;
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
