#include "employee.h"
#include "ui_employee.h"

#include <DataBase.h>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <qsqlquery.h>
#include <qsqlquerymodel.h>

Employee::Employee(int id, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Employee),
	id_(id)
{
	ui->setupUi(this);
	ui->eId->setText(QString::number(id_));

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	query->prepare("Select credit_tarif_id, rate, max_credit From Credit_tarif");
	query->exec();

	while (query->next()) {
		ui->comboBox->addItem("Ставка: " + query->value(1).toString() + "%,\n" + "Максимальная сумма: " + query->value(2).toString());
		vecId.push_back(query->value(0).toInt());
		vecSums.push_back(query->value(2).toInt());
	}
}

Employee::~Employee()
{
	delete ui;
}

void Employee::on_creditRequests_clicked()
{
	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	query->prepare("Execute GetActiveCreditRequests;");
	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);
}

void Employee::on_creditRequests_2_clicked()
{
	if (!ui->rId->text().isEmpty()) {
		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);

		query->prepare("Execute SetEmployeeToCreditRequest " + QString::number(id_) + ", " + ui->rId->text() + ";");
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

	on_creditRequests_clicked();
}

void Employee::on_creditRequests_4_clicked()
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
	ui->tableView_2->setModel(model2);
}

void Employee::on_creditRequests_3_clicked()
{
		if (ui->clId->text().isEmpty() || ui->rId->text().isEmpty() || ui->payment->text().isEmpty() || ui->period->text().isEmpty()) {
			QMessageBox message;
			message.setText("Убедитесь, что заполинили все поля!");
			message.exec();

			return;
		}

		QString crediNumber = "";
		for (int i = 0; i < 10; ++i) {
			crediNumber += QString::number(qrand() % 10);
		}

		int requestId = ui->rId->text().toInt();
		int period = ui->period->text().toInt();
		int payment = ui->payment->text().toInt();

		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);

		query->prepare("Execute ApproveCreditRequest "
									 + QString::number(requestId) + ", "
									 + QString::number(period) + ", "
									 + QString::number(vecId.at(ui->comboBox->currentIndex())) + ", "
									 + QString::number(payment) + ", '"
									 + crediNumber + "';");
		query->exec();

		ui->creditNumber->setText(crediNumber);

		QMessageBox message;
		message.setText("Кредит успешно выдан");
		message.exec();
}

void Employee::on_creditRequests_5_clicked()
{
		if (ui->clId->text().isEmpty()) {
			QMessageBox message;
			message.setText("Заполните номер клиента");
			message.exec();

			return;
		}

		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);
		query->prepare("Execute GetClientActivity " + ui->clId->text() + ";");
		query->exec();

		QSqlQueryModel *model2 = new QSqlQueryModel;
		model2->setQuery(*query);
		ui->tableView_2->setModel(model2);
}

void Employee::on_cancel_clicked()
{
	if (ui->rId->text().isEmpty()) {
		QMessageBox message;
		message.setText("Заполните номер заявки");
		message.exec();

		return;
	}

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);
	query->prepare("Execute RefuseCreditRequest " + ui->rId->text() + ";");
	query->exec();

	query->clear();
	query->prepare("Execute GetActiveCreditRequests;");
	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);
}

void Employee::on_cancel_2_clicked()
{
		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);
		query->prepare("Execute GetDebtors;");
		query->exec();

		QSqlQueryModel *model = new QSqlQueryModel;
		model->setQuery(*query);
		ui->tableView->setModel(model);
}

void Employee::on_cancel_3_clicked()
{
	QSqlQueryModel *model = new QSqlQueryModel;
	model->clear();
	ui->tableView->setModel(model);
	ui->tableView_2->setModel(model);
}
