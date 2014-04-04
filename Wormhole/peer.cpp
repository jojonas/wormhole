#include "peer.h"

Peer::Peer(QHostAddress address, PortNumber port)
: address(address)
, port(port)
{}

Peer::~Peer()
{

}

QHostAddress Peer::getAddress() const{
	return address;
}

PortNumber Peer::getPort() const
{
	return port;
}

QString Peer::toString() const
{
	return QString("%1:%2").arg(address.toString()).arg(port);
}
