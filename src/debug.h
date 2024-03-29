#ifndef DEBUG_H
#define DEBUG_H

#ifdef WIN32
#include <vld.h>
#include <Windows.h>
#endif

#include <QDebug>

void outputMsgHandler(QtMsgType type, const char* msg);

#if QT_VERSION >= 0x050000
void outputMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#endif

void setupDebugging();

#endif // DEBUG_H
