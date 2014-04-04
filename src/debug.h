#ifndef DEBUG_H
#define DEBUG_H

#ifdef WIN32
#include <vld.h>
#include <Windows.h>
#endif

#include <QDebug>

void outputMessageHandlerQt4(QtMsgType type, const char* msg);

#if QT_VERSION >= 0x050000
void outputMessageHandlerQt5(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#endif

void setupDebugging();

#endif // DEBUG_H
