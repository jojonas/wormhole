#include "peer.h"

Peer::Peer(QHostAddress address, qint16 port)
: address(address)
, port(port)
{}

Peer::~Peer()
{

}

QHostAddress Peer::getAddress() const{
	return address;
}

quint16 Peer::getPort() const
{
	return port;
}

QString Peer::toString() const
{
	return QString("%1:%2").arg(address.toString()).arg(port);
}
