#include "connectioninputdialog.h"

#include <QDebug>
#include <QRegExp>

ConnectionInputDialog::ConnectionInputDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QRegExp ipRegExp("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
	QRegExpValidator* ipValidator = new QRegExpValidator(ipRegExp, this);
	ui.ipAddress->setValidator(ipValidator);

	QIntValidator* portValidator = new QIntValidator(this);
	portValidator->setRange(1, 65535);
	ui.port->setValidator(portValidator);

	QObject::connect(ui.ipAddress, SIGNAL(textEdited(const QString&)), this, SLOT(validateInput()));
	QObject::connect(ui.port, SIGNAL(textEdited(const QString&)), this, SLOT(validateInput()));
	validateInput();

	QObject::connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
	QObject::connect(ui.okButton, SIGNAL(clicked()), this, SLOT(accept()));
}

ConnectionInputDialog::~ConnectionInputDialog()
{

}

QString ConnectionInputDialog::getIpAddress() const
{
	return ui.ipAddress->text();
}

PortNumber ConnectionInputDialog::getPort() const
{
	return ui.port->text().toUInt();
}

void ConnectionInputDialog::validateInput()
{
	const bool acceptableIp = ui.ipAddress->hasAcceptableInput();
	const bool acceptablePort = ui.port->hasAcceptableInput();
	ui.okButton->setEnabled(acceptableIp && acceptablePort);
}

void ConnectionInputDialog::setIpAddress(QString address)
{
	ui.ipAddress->setText(address);
}

void ConnectionInputDialog::setPort(PortNumber port)
{
	ui.port->setText(QString::number(port));
}

