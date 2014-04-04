#include "debug.h"

void outputMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
	QString severity;

	switch (type) {
	case QtDebugMsg: severity = "Debug"; break;
	case QtWarningMsg: severity = "Warning"; break;
	case QtCriticalMsg: severity = "Critical"; break;
	case QtFatalMsg: severity = "Fatal"; break;
	default: severity = "Unknown"; break;
	}

	QString output = QObject::tr("%1:%2 [%3]: %4\n").arg(context.file).arg(context.line).arg(severity).arg(msg);
#if defined(WIN32) && defined(_DEBUG)
	OutputDebugStringW(output.toStdWString().c_str());

	if (type == QtFatalMsg || type == QtCriticalMsg) {
		__debugbreak();
	}
#else
	puts(output.toStdString().c_str());
#endif 
}

#ifdef _DEBUG
void setupDebugging() {
	qInstallMessageHandler(outputMessageHandler);
}
#else
void setupDebugging() {}
#endif
