#include "debug.h"

void debugOutput(const QString& message) {
#if defined(WIN32) && defined(_DEBUG)
	OutputDebugStringW(message.toStdWString().c_str());
#else
	puts(message.toStdString().c_str());
#endif 
}

QString msgTypeToString(QtMsgType type) {
	QString severity;
	switch (type) {
	case QtDebugMsg: severity = "Debug"; break;
	case QtWarningMsg: severity = "Warning"; break;
	case QtCriticalMsg: severity = "Critical"; break;
	case QtFatalMsg: severity = "Fatal"; break;
	default: severity = "Unknown"; break;
	}
	return severity;
}

void outputMsgHandler(QtMsgType type, const char* msg) {
	QString output = QObject::tr("[%1]: %2\n").arg(msgTypeToString(type)).arg(msg);
	debugOutput(output);

#if defined(WIN32) && defined(_DEBUG)
	if (type == QtFatalMsg || type == QtCriticalMsg) {
		__debugbreak();
	}
#endif 
}

#if QT_VERSION >= 0x050000
void outputMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
	QString output = QObject::tr("%1:%2 : %4\n").arg(context.file).arg(context.line).arg(msg);
	outputMsgHandler(type, output.toStdString().c_str());
}
#endif

#ifdef _DEBUG
void setupDebugging() {
#if QT_VERSION >= 0x050000
	qInstallMessageHandler(outputMessageHandler);
#else
	qInstallMsgHandler(outputMsgHandler);
#endif
}
#else
void setupDebugging() {}
#endif
