#ifndef WORMHOLE_H
#define WORMHOLE_H

#include <QMainWindow>

#include "ui_wormhole.h"

#include "wormholeservice.h"

class QWinTaskbarProgress;
class QWinTaskbarButton;
class QSettings;

class Wormhole : public QMainWindow
{
	Q_OBJECT

public:
	Wormhole(QWidget *parent = 0);
	~Wormhole();

protected:
	void contextMenuEvent(QContextMenuEvent *event);

private slots:
	void connectToHost();
	void changeStaysOnTop();
	void changePort();

	void updateProgress(float ratio);
	void receivedFile(QFile* file);

private:
	Q_DISABLE_COPY(Wormhole);

	const int defaultPort;
	const int defaultStaysOnTop;

	void setupApplication();
	void setupWindow();
	void setupWidgets();
	void setupActions();
	void setupService();

	void setStayOnTop(bool stayOnTop);

	
	WormholeService service;

	Ui::WormholeClass ui;
	QSettings* settings;
	QAction* connectToHostAction;
	QAction* staysOnTopAction;
	QAction* changePortAction;
};

#endif // WORMHOLE_H
