#include "database.h"
#include "investout.h"
#include "ui_investout.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

InvestOut::InvestOut(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::InvestOut)
{
	ui->setupUi(this);
}

InvestOut::~InvestOut()
{
	delete ui;
}

void InvestOut::on_pushButton_clicked()
{
	if (ui->pasportSeries->text().isEmpty() || ui->pasportNumber->text().isEmpty()) {
		QMessageBox message;
		message.setText("Убедитесь, что вы заполнили все паспортные данные");
		message.exec();

		return;
	}
	int pasportSeries = ui->pasportSeries->text().toInt();
	int pasportNumber = ui->pasportNumber->text().toInt();

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);
	query->prepare("Execute GetClientInfo " + QString::number(pasportSeries) + ", " + QString::number(pasportNumber) + ";");
	query->exec();

	qDebug() << query->lastQuery();

	int clientId = 0;

	if (!query->next()) {
		QMessageBox message;
		message.setText("Вы пока не являетесь клиентом нашего банка, зарегиструйтесь, пожалуйста");
		message.exec();

		return;
	}
	else {
		clientId = query->value(0).toInt();
	}

	query->clear();
	query->prepare("Execute CreateInvestOutRequest " + QString::number(clientId) + ";");
	query->exec();

	QMessageBox message;
	message.setText("Заявка передана нашему менеджеру, скоро с вами свяжутся по телефону");
	message.exec();

	this->close();
}
