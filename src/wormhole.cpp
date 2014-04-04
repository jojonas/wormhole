#include "wormhole.h"

#include <QSettings>
#include <QContextMenuEvent>
#include <QMenu>
#include <QInputDialog>
#include <QDesktopServices>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

#include "connectioninputdialog.h"

Wormhole::Wormhole(QWidget *parent)
: QMainWindow(parent)
, service(this)
{
	ui.setupUi(this);

	setupApplication();
	setupWindow();
	setupWidgets();
	setupActions();
	setupService();
}

Wormhole::~Wormhole()
{
}

void Wormhole::setupApplication()
{
	QCoreApplication::setApplicationName("Wormhole");
	QCoreApplication::setOrganizationName("Jonas Lieb");
	QCoreApplication::setOrganizationDomain("jonaslieb.de");

	settings = new QSettings(this);
}

void Wormhole::setupWindow()
{
	//setWindowFlags(Qt::Tool); // maybe also: Qt::FramelessWindowHint
}

void Wormhole::setupWidgets()
{
	ui.progressBar->setMinimum(0);
	ui.progressBar->setMaximum(1000);
	ui.progressBar->setValue(ui.progressBar->maximum());
}

void Wormhole::setupActions()
{
	connectToHostAction = new QAction(tr("&Connect..."), this);
	connectToHostAction->setStatusTip(tr("Connect to server"));
	QObject::connect(connectToHostAction, SIGNAL(triggered()), this, SLOT(connectToHost()));

	staysOnTopAction = new QAction(tr("Stay on top"), this);
	staysOnTopAction->setStatusTip(tr("Keep application on top of all windows"));
	staysOnTopAction->setCheckable(true);
	staysOnTopAction->setChecked(settings->value("Window/StaysOnTop", defaultStaysOnTop).toBool());
	QObject::connect(staysOnTopAction, SIGNAL(changed()), this, SLOT(changeStaysOnTop()));
	changeStaysOnTop();

	changePortAction = new QAction(tr("Change port..."), this);
	changePortAction->setStatusTip(tr("Change listening port"));
	QObject::connect(changePortAction, SIGNAL(triggered()), this, SLOT(changePort()));
}

void Wormhole::setupService()
{
	service.startListening(settings->value("Service/Port", defaultPort).toUInt());
	service.setOutputDirectory(QDir(settings->value("Service/OutputDirectory", QDir::tempPath()).toString()));

	QObject::connect(&service, SIGNAL(sendProgress(float)), this, SLOT(updateProgress(float)));
	QObject::connect(&service, SIGNAL(receiveProgress(float)), this, SLOT(updateProgress(float)));
	QObject::connect(&service, SIGNAL(receivedFile(QFile*)), this, SLOT(receivedFile(QFile*)));
	QObject::connect(ui.dropPanel, SIGNAL(fileDropped(QFile*)), &service, SLOT(sendFile(QFile*)));
}

void Wormhole::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	menu.addAction(connectToHostAction);
	menu.addAction(tr("Connected to %1 peer(s).").arg(service.getPeerCount()));
	menu.addSeparator();
	menu.addAction(staysOnTopAction);
	menu.addAction(changePortAction);
	menu.exec(event->globalPos());
}

void Wormhole::connectToHost()
{
	ConnectionInputDialog dialog;
	dialog.setModal(false);
	dialog.setPort(settings->value("Service/Port", defaultPort).toUInt());
	QDialog::DialogCode retval = (QDialog::DialogCode)dialog.exec();
	if (retval == QDialog::Accepted) {
		QHostAddress address(dialog.getIpAddress());
		service.connectToHost(address, dialog.getPort());
	}
}


void Wormhole::changeStaysOnTop()
{
	const bool stayOnTop = staysOnTopAction->isChecked();
	settings->setValue("Window/StaysOnTop", stayOnTop);
	setStayOnTop(stayOnTop);
}

void Wormhole::changePort()
{
	const int oldPort = settings->value("Service/Port", defaultPort).toUInt();
	const int newPort = QInputDialog::getInt(this,
		tr("Choose Port"),
		tr("Enter port to listen on:"),
		oldPort,
		1, 65535
		);
	settings->setValue("Service/Port", newPort);
	service.startListening(newPort);
}

void Wormhole::updateProgress(float ratio)
{
	ui.progressBar->setValue(ratio * ui.progressBar->maximum());
}

void Wormhole::setStayOnTop(bool stayOnTop)
{
	// this preprocessor-magic is an ugly workaround for a bug in Qt with disabling setWindowFlage(Qt::WindowStaysOnTopHint)
	if (stayOnTop) {
#ifdef Q_OS_WIN
		SetWindowPos((HWND)winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
#else
		setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
#endif
	}
	else {
#ifdef Q_OS_WIN
		SetWindowPos((HWND)winId(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
#else
		setWindowFlags(windowFlags() ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
#endif
	}
}

void Wormhole::receivedFile(QFile* file)
{
	QFileInfo fileInfo(*file);
	QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
	QDesktopServices::openUrl(url);
}
