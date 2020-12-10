#include "creditrequestcreator.h"
#include "database.h"
#include "ui_creditrequestcreator.h"

#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

CreditRequestCreator::CreditRequestCreator(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::creditRequestCreator)
{
	ui->setupUi(this);

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(7);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->groupBox->setGraphicsEffect(effect);

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

CreditRequestCreator::~CreditRequestCreator()
{
	delete ui;
}

void CreditRequestCreator::on_createButton_clicked()
{
	if (ui->pasportSeries->text().isEmpty() || ui->pasportNumber->text().isEmpty() || ui->sum->text().isEmpty() || ui->avgSelary->text().isEmpty()) {
		QMessageBox message;
		message.setText("Убедитесь, что вы заполнили все паспортные данные и информаю о кредите");
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
		message.setText("Вы пока не являетесь клиентом нашего банка. Пожалуйста, пройдите регистрицию.");
		message.exec();

		return;
	}
	else {
		clientId = query->value(0).toInt();
	}

	int tarifId = vecId.at(ui->comboBox->currentIndex());
	int sum = ui->sum->text().toInt();

	/*if (sum > vecSums.at(ui->comboBox->currentIndex()) || sum != 0) {
		QMessageBox message;
		message.setText("Запрашиваемая вами сумма не соответсвеует тарифу");
		message.exec();

		return;
	}*/

	int avgSelary = ui->avgSelary->text().toInt();

	query->clear();
	query->prepare("Execute ApplyForCredit "
								 + QString::number(clientId) + ", "
								 + QString::number(avgSelary) + ", "
								 + QString::number(sum) + ";");
	query->exec();

	if (query->next()) {
		ui->requestId->setText(query->value(0).toString());
		ui->requestId_2->setText(query->value(1).toString());
	}
	else {
		QMessageBox message;
		message.setText("Что-то пошло не так, попробуйте еще раз");
		message.exec();
	}
}

void CreditRequestCreator::on_checkData_clicked()
{
	if (ui->pasportSeries->text().isEmpty() || ui->pasportNumber->text().isEmpty() || ui->requestId->text().isEmpty()) {
		QMessageBox message;
		message.setText("Убедитесь, что вы заполнили все паспортные данные и статус заявки");
		message.exec();

		return;
	}
	int pasportSeries = ui->pasportSeries->text().toInt();
	int pasportNumber = ui->pasportNumber->text().toInt();
	int id = ui->requestId->text().toInt();

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	query->prepare("Execute CheckRequestStatus " + QString::number(id) + ", " + QString::number(pasportSeries) + ", " + QString::number(pasportNumber) + ";");
	query->exec();

	if (query->next()) {
		ui->requestId_2->setText(query->value(1).toString());
	}
	else {
		QMessageBox message;
		message.setText("Что-то пошло не так, попробуйте еще раз");
		message.exec();
	}
}

void CreditRequestCreator::on_cancel_2_clicked()
{
		ui->pasportSeries->clear();
		ui->pasportNumber->clear();
		ui->sum->clear();
		ui->avgSelary->clear();
		ui->requestId->clear();
		ui->requestId_2->clear();
}

void CreditRequestCreator::on_cancel_clicked()
{
		this->close();
}
