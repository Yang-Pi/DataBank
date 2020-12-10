#include "database.h"
#include "manager2.h"
#include "ui_manager2.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

Manager2::Manager2(int id, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Manager2),
	id_(id)
{
	ui->setupUi(this);
	ui->eId->setText(QString::number(id_));

	ui->comboBox->addItem("Кредиты");
	ui->comboBox->addItem("Вклады");
}

Manager2::~Manager2()
{
	delete ui;
}

void Manager2::on_investRequest_2_clicked()
{
	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	query->prepare("Execute GetActiveInvestOutRequests;");
	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);
}

void Manager2::on_getRequest_2_clicked()
{
	if (!ui->requestId->text().isEmpty()) {
		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);

		query->prepare("Execute SetEmployeeInvestOutRequest " + QString::number(id_) + ", " + ui->requestId->text() + ";");
		query->exec();

		QMessageBox message;
		message.setText("Вы начали работау над заявкой" + ui->requestId->text());
		message.exec();
	}
	else {
		QMessageBox message;
		message.setText("Введите номер заявки");
		message.exec();
	}

	on_investRequest_2_clicked();
}

void Manager2::on_clientInfoButton_2_clicked()
{
	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	if (ui->clientId->text().isEmpty()) {
		QMessageBox message;
		message.setText("Введите номер клиента");
		message.exec();

		return;
	}

	query->prepare("Execute GetClientFullInfo " + ui->clientId->text() + ";");
	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);

	query->clear();
	query->prepare("Execute GetClientFinanceData " + ui->clientId->text() + ";");
	query->exec();

	QSqlQueryModel *model2 = new QSqlQueryModel;
	model2->setQuery(*query);
	ui->tableView->setModel(model2);
}

void Manager2::on_creditRequests_7_clicked()
{
	if (ui->clientId->text().isEmpty()) {
		QMessageBox message;
		message.setText("Заполните номер клиента");
		message.exec();

		return;
	}

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);
	query->prepare("Execute GetClientIvests " + ui->clientId->text() + ";");
	query->exec();

	QSqlQueryModel *model2 = new QSqlQueryModel;
	model2->setQuery(*query);
	ui->tableView->setModel(model2);
}

void Manager2::on_compute_clicked()
{
		if (ui->investId->text().isEmpty()) {
			QMessageBox message;
			message.setText("Введите номер инвестиции");
			message.exec();

			return;
		}

		int investId = ui->investId->text().toInt();

		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);

		query->prepare("Execute GetInvestInfoForComputing " + QString::number(investId));
		query->exec();

		if (query->next()) {
			int clientSum = query->value(0).toInt();
			int wasFullSum = query->value(1).toInt();
			int currentSum = query->value(2).toInt();

			srand(static_cast<unsigned int>(time(nullptr)));
			double x = 1 + (-1. + rand() % 10 + 1) / 100;

			double res = (currentSum * x - wasFullSum ) * clientSum / wasFullSum + clientSum;
			ui->resSum->setText(QString::number(res));
		}
		else {
			QMessageBox message;
			message.setText("Что-то пошло не так, проверьте введенные вами данные");
			message.exec();
		}
}

void Manager2::on_cancel_clicked()
{
	if (ui->requestId->text().isEmpty()) {
		QMessageBox message;
		message.setText("Убедитесь, что заполнили все поля!");
		message.exec();

		return;
	}

	int investId = ui->investId->text().toInt();

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	query->prepare("Execute CloseInvestOutRequest " + ui->requestId->text() + "," + QString::number(investId) + ";");
	query->exec();

	query->clear();
	query->prepare("Execute GetActiveInvestOutRequests;");
	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);
}

void Manager2::on_checkData_clicked()
{
	if (ui->period->text().isEmpty()) {
		QMessageBox message;
		message.setText("Убедитесь, что заполнили все поля!");
		message.exec();

		return;
	}
	int period = ui->period->text().toInt();

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);
	query->prepare("Execute AnalyzeBankProfitabilityForPeriod " + QString::number(period));
	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);
}

void Manager2::on_creditRequests_8_clicked()
{
	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	if (ui->comboBox->currentIndex() == 0) {
		query->prepare("Select * From Credit_tarif;");
	}
	else {
		query->prepare("Select * From Deposit_tarif;");
	}

	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);
}

void Manager2::on_creditRequests_6_clicked()
{
	if (ui->tarifId->text().isEmpty() || ui->rate->text().isEmpty() || ui->sum->text().isEmpty()) {
		QMessageBox message;
		message.setText("Убедитесь, что заполнили все поля!");
		message.exec();

		return;
	}

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	if (ui->comboBox->currentIndex() == 0) {
		query->prepare("Execute UpdateCreditTarif " + ui->tarifId->text() + "," + ui->rate->text() + "," + ui->sum->text());
		query->exec();
	}
	else {
		query->prepare("Execute UpdateDepositTarif " + ui->tarifId->text() + "," + ui->rate->text() + "," + ui->sum->text());
		query->exec();
	}

	QMessageBox message;
	message.setText("Успешно! Теперь обновите таблицу тарифов в приложении");
	message.exec();
}

void Manager2::on_creditRequests_9_clicked()
{
	if (ui->rate->text().isEmpty() || ui->sum->text().isEmpty()) {
		QMessageBox message;
		message.setText("Убедитесь, что заполнили все поля!");
		message.exec();

		return;
	}

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	if (ui->comboBox->currentIndex() == 0) {
		query->prepare("Execute CreateCreditTarif " + ui->rate->text() + "," + ui->sum->text());
		query->exec();
	}
	else {
		query->prepare("Execute CreateDepositTarif " + ui->rate->text() + "," + ui->sum->text());
		query->exec();
	}

	QMessageBox message;
	message.setText("Успешно! Теперь обновите таблицу тарифов в приложении");
	message.exec();
}

void Manager2::on_creditRequests_11_clicked()
{
	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);
	query->prepare("Select * From Credit_request Where employee_id Is Not Null");
	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);
}

void Manager2::on_creditRequests_10_clicked()
{
	if (ui->employeeId->text().isEmpty() || ui->extraSum->text().isEmpty()) {
		QMessageBox message;
		message.setText("Убедитесь, что заполнили все поля!");
		message.exec();

		return;
	}

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);
	query->prepare("Execute AppointEmployeeExtraSalary " + ui->employeeId->text() + ", " + ui->extraSum->text() + ";");
	query->exec();

	QSqlQueryModel *model = new QSqlQueryModel;
	model->setQuery(*query);
	ui->tableView->setModel(model);
}

void Manager2::on_cancel_3_clicked()
{
	QSqlQueryModel *model = new QSqlQueryModel;
	model->clear();
	ui->tableView->setModel(model);
}
