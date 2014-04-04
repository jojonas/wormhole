#include "qtprotobuf.h"

// message TO stream
QDataStream& operator<<(QDataStream& stream, const google::protobuf::Message& message) {
	const int length = message.ByteSize();
	char* buffer = new char[length];
	message.SerializeToArray(buffer, length);
	stream.writeRawData(buffer, length);
	delete[] buffer;
	return stream;
}

// stream TO message
QDataStream& operator>>(QDataStream& stream, google::protobuf::Message& message) {
	const int length = message.ByteSize();
	char* buffer = new char[length];
	stream.readRawData(buffer, length);
	message.ParseFromArray(buffer, length);
	delete[] buffer;
	return stream;
}