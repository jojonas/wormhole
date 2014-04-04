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

#if QT_VERSION < 0x050000
// workaround, already implemented in Qt>=5.0.0 (???)
inline uint qHash(const QHostAddress& key, uint seed = 0) {
	Q_IPV6ADDR address = key.toIPv6Address();
	QByteArray array = QByteArray::fromRawData(reinterpret_cast<const char*>(&address), 16);
	return qHash(array);
}
#endif

inline uint qHash(const Peer& key, uint seed = 0)
{
	return qHash(key.getAddress(), seed) ^ key.getPort();
}

#endif // PEER_H
