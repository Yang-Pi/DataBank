#include "database.h"
#include "manager.h"
#include "ui_manager.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <qsqlquery.h>

Manager::Manager(int id, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Manager),
	id_(id)

{
	ui->setupUi(this);

	ui->setupUi(this);
	ui->eId->setText(QString::number(id_));

	ui->comboBox->addItem("Крeдит");
	ui->comboBox->addItem("Вклад");
}

Manager::~Manager()
{
	delete ui;
}

void Manager::on_investRequest_clicked()
{
	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	query->prepare("Execute GetActiveInvestOutRequests;");
	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);
}

void Manager::on_getRequest_clicked()
{
	if (!ui->rId->text().isEmpty()) {
		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);

		query->prepare("Execute SetEmployeeInvestOutRequest " + QString::number(id_) + ", " + ui->rId->text() + ";");
		query->exec();

		QMessageBox message;
		message.setText("Вы начали работау над заявкой" + ui->rId->text());
		message.exec();
	}
	else {
		QMessageBox message;
		message.setText("Введите номер заявки");
		message.exec();
	}

	on_investRequest_clicked();
}

void Manager::on_clientInfoButton_clicked()
{
	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	if (ui->clId->text().isEmpty()) {
		QMessageBox message;
		message.setText("Введите номер клиента");
		message.exec();

		return;
	}

	query->prepare("Execute GetClientFullInfo " + ui->clId->text() + ";");
	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);

	query->clear();
	query->prepare("Execute GetClientFinanceData " + ui->clId->text() + ";");
	query->exec();

	QSqlQueryModel *model2 = new QSqlQueryModel;
	model2->setQuery(*query);
	ui->tableView->setModel(model2);
}
