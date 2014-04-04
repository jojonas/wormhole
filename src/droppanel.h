#ifndef DROPPANEL_H
#define DROPPANEL_H

#include <QFrame>
#include "ui_droppanel.h"

class QFile;
class QDragEnterEvent;
class QDragLeaveEvent;
class QDragMoveEvent;
class QDropEvent;

class DropPanel : public QFrame
{
	Q_OBJECT

public:
	DropPanel(QWidget *parent = 0);
	~DropPanel();

protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dragMoveEvent(QDragMoveEvent* event);
	void dragLeaveEvent(QDragLeaveEvent* event);
	void dropEvent(QDropEvent* event);

signals:
	void fileDropped(QFile* file);

private:
	Q_DISABLE_COPY(DropPanel);

	Ui::DropPanel ui;
};

#endif // DROPPANEL_H
