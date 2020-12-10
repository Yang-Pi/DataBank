#include "cardcreator.h"
#include "database.h"
#include "ui_cardcreator.h"

#include <QDate>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

CardCreator::CardCreator(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CardCreator)
{
	ui->setupUi(this);

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(7);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->groupBox->setGraphicsEffect(effect);
}

CardCreator::~CardCreator()
{
	delete ui;
}

void CardCreator::on_createButton_clicked()
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

		QString cardNumber = "";
		for (int i = 0; i < 16; ++i) {
			cardNumber += QString::number(qrand() % 10);
		}

		QString pinCode = "";
		QString Cvv = "";
		for (int i = 0; i < 4; ++i) {
			pinCode += QString::number(qrand() % 10);
			if (i < 3) {
				Cvv += QString::number(qrand() % 10);
			}
		}

		QString validity = QString::number(QDate::currentDate().month()) + "/" + QString::number(QDate::currentDate().addYears(4).year() % 100);

		query->clear();
		query->prepare("Execute ArrangeCard "
									 + QString::number(clientId) + ", '"
									 + cardNumber + "', '"
									 + validity + "', '"
									 + Cvv + "', '"
									 + pinCode + "';");
		query->exec();
		qDebug() << query->lastQuery();

		query->clear();
		query->prepare("Exec GetCardSecretData " + QString::number(pasportSeries) + "," + QString::number(pasportNumber) + ", '" + cardNumber + "';");
		query->exec();

		if (query->next()) {
			ui->cardNumber->setText(cardNumber);
			QMessageBox message;
			message.setText("Данные вашей карты \nНомер: " + cardNumber + "\nСрок действия: " + validity + "\nCVV: " + Cvv + " PIN: " + pinCode);
			message.exec();
		}
		else {
			QMessageBox message;
			message.setText("Что-то пошло не так, попробуйте еще раз");
			message.exec();
		}
}

void CardCreator::on_checkData_clicked()
{
	if (ui->pasportSeries->text().isEmpty() || ui->pasportNumber->text().isEmpty() & ui->cardNumber->text().isEmpty()) {
			QMessageBox message;
			message.setText("Убедитесь, что вы заполнили все паспортные данные и номер карты");
			message.exec();

			return;
		}
		int pasportSeries = ui->pasportSeries->text().toInt();
		int pasportNumber = ui->pasportNumber->text().toInt();
		QString cardNumber = ui->cardNumber->text();

		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);
		query->prepare("Exec GetCardSecretData " + QString::number(pasportSeries) + "," + QString::number(pasportNumber) + ", '" + cardNumber + "';");
		query->exec();

		if (query->next()) {
			QMessageBox message;
			message.setText("Данные вашей карты \nНомер: " + query->value(0).toString() + "\nСрок действия: " + query->value(1).toString() + "\nCVV: " + query->value(2).toString() + " PIN: " + query->value(3).toString());
			message.exec();
		}
		else {
			QMessageBox message;
			message.setText("Проверьте введенные вами данные");
			message.exec();
		}
}

void CardCreator::on_cancel_clicked()
{
		this->close();
}
