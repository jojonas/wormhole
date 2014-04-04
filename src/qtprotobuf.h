#ifndef QTPROTOBUF_H
#define QTPROTOBUF_H

#include <QDataStream>
#include <google/protobuf/message.h>


QDataStream& operator<<(QDataStream& stream, const google::protobuf::Message& message);
QDataStream& operator>>(QDataStream& stream, google::protobuf::Message& message);

#endif // QTPROTOBUF_H
