#include "droppanel.h"

#include <QFile>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMimeData>

#include <QDebug>

DropPanel::DropPanel(QWidget *parent)
: QFrame(parent)
{
	ui.setupUi(this);
	setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
	setAutoFillBackground(true);
	setAcceptDrops(true);
}

DropPanel::~DropPanel()
{
}

void DropPanel::dropEvent(QDropEvent* event) {
	const QMimeData* mimeData = event->mimeData();
	
	if (mimeData->hasUrls()) {
		QStringList pathList;
		QList<QUrl> urlList = mimeData->urls();

		for (int i = 0; i < urlList.size(); i++){
			QFile* file = new QFile(urlList.at(i).toLocalFile(), this);
			emit fileDropped(file);
		}
		event->acceptProposedAction();
	}
	setBackgroundRole(QPalette::Window);
}

void DropPanel::dragEnterEvent(QDragEnterEvent* event) {
	setBackgroundRole(QPalette::Highlight);
	event->acceptProposedAction();
}

void DropPanel::dragMoveEvent(QDragMoveEvent* event)
{
	event->acceptProposedAction();
}

void DropPanel::dragLeaveEvent(QDragLeaveEvent* event)
{
	event->accept();
	setBackgroundRole(QPalette::Window);
}
