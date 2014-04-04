#ifndef CONNECTIONINPUTDIALOG_H
#define CONNECTIONINPUTDIALOG_H

#include <QDialog>
#include "ui_connectioninputdialog.h"

class ConnectionInputDialog : public QDialog
{
	Q_OBJECT

public:
	ConnectionInputDialog(QWidget *parent = 0);
	~ConnectionInputDialog();

	QString getIpAddress() const;
	quint16 getPort() const;

	void setIpAddress(QString address);
	void setPort(quint16 port);

public slots:
	void validateInput();

private:
	Ui::ConnectionInputDialog ui;
};

#endif // CONNECTIONINPUTDIALOG_H
