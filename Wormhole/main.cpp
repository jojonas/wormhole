#include "wormhole.h"
#include <QtWidgets/QApplication>

#include <QtGlobal>
#include <QtDebug>
#include <QMessageBox>

#include <Windows.h>

#if defined(WIN32) && defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

void winMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
	QString severity;

	switch (type) {
	case QtDebugMsg: severity = "Debug"; break;
	case QtWarningMsg: severity = "Warning"; break;
	case QtCriticalMsg: severity = "Critical"; break;
	case QtFatalMsg: severity = "Fatal"; break;
	default: severity = "Unknown"; break;
	}
	
	QString output = QObject::tr("%1:%2 [%3]: %4\n").arg(context.file).arg(context.line).arg(severity).arg(msg);
	OutputDebugStringW(output.toStdWString().c_str());

	if (type == QtFatalMsg || type == QtCriticalMsg) {
		__debugbreak();
	}
}

void msgBoxMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QMessageBox* msgBox = new QMessageBox(0);
	QObject::connect(msgBox, SIGNAL(finished(int)), msgBox, SLOT(deleteLater()));

	msgBox->setText(msg);

	QMessageBox::Icon icon = QMessageBox::NoIcon;
	QString title = QObject::tr("Message");
	switch (type) {
	case QtDebugMsg:
		icon = QMessageBox::Information;
		title = QObject::tr("Debug");
		break;
	case QtWarningMsg:
		icon = QMessageBox::Warning;
		title = QObject::tr("Warning");
		break;
	case QtCriticalMsg:
		icon = QMessageBox::Critical;
		title = QObject::tr("Critical");
		break;
	case QtFatalMsg:
		icon = QMessageBox::Critical;
		title = QObject::tr("Fatal");
		abort();
	}
	msgBox->setIcon(icon);
	msgBox->setWindowTitle(title);

	msgBox->open();
}

int main(int argc, char *argv[])
{
	qInstallMessageHandler(winMessageHandler);

	QApplication app(argc, argv);
	Wormhole w;
	w.show();
	return app.exec();
}
