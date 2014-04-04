#include "debug.h"

#include "wormhole.h"
#include <QtWidgets/QApplication>

#include <QtGlobal>
#include <QtDebug>
#include <QMessageBox>

int main(int argc, char *argv[])
{
	setupDebugging();
	QApplication app(argc, argv);
	Wormhole w;
	w.show();
	const int retval = app.exec();
	w.dumpObjectTree();
	return retval;
}
