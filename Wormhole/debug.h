#ifndef DEBUG_H
#define DEBUG_H

#ifdef WIN32
#include <vld.h>
#include <Windows.h>
#endif

#include <QDebug>

void outputMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void setupDebugging();

#endif // DEBUG_H