#include "bankomat.h"
#include "database.h"
#include "ui_bankomat.h"

#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

Bankomat::Bankomat(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Bankomat)
{
	ui->setupUi(this);

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(7);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->groupBox->setGraphicsEffect(effect);
}

Bankomat::~Bankomat()
{
	delete ui;
}

void Bankomat::on_createButton_clicked()
{
		if (ui->cardNumber->text().isEmpty() || ui->deposit->text().isEmpty()) {
			QMessageBox message;
			message.setText("Убедитесь, что вы заполнили все данные");
			message.exec();

			return;
		}

		QString cardNumber = ui->cardNumber->text();
		int sum = ui->deposit->text().toInt();

		QString pin = ui->pin->text();

		if (ui->comboBox->currentIndex() == 0) {
			if (pin == "") {
				QMessageBox message;
				message.setText("Убедитесь, что вы заполнили все данные");
				message.exec();

				return;
			}

			QSqlDatabase db = DataBase::getInstance()->getDb();
			QSqlQuery *query = new QSqlQuery(db);
			query->prepare("Execute GetCardBalance '" + cardNumber + "', '" + pin + "';");
			query->exec();
			query->next();

			int balance = query->value(0).toInt();

			if (sum > balance) {
				QMessageBox message;
				message.setText("Недостаточно средств");
				message.exec();

				return;
			}

			query->clear();
			query->prepare("Execute WithdrawMoneyFromCard '" + cardNumber + "', '" + pin + "', " + QString::number(sum) + ";");
			query->exec();

			query->clear();
			query->prepare("Execute GetCardBalance '" + cardNumber + "', '" + pin + "';");
			query->exec();
			query->next();

			QMessageBox message;
			message.setText("Теперь у вас " + query->value(0).toString() + " рублей");
			message.exec();
		}
		else {
			QSqlDatabase db = DataBase::getInstance()->getDb();
			QSqlQuery *query = new QSqlQuery(db);

			query->prepare("Execute TopUpCardBalance '" + cardNumber + "', " + QString::number(sum) + ";");
			query->exec();

			if (pin != "") {
				query->clear();
				query->prepare("Execute GetCardBalance '" + cardNumber + "', '" + pin + "';");
				query->exec();
				query->next();

				QMessageBox message;
				message.setText("Теперь у вас " + query->value(0).toString() + " рублей");
				message.exec();
			}
			else {
				QMessageBox message;
				message.setText(QString::number(sum) + "внесено!");
				message.exec();
			}
		}
}

void Bankomat::on_cancel_2_clicked()
{
		ui->cardNumber->clear();
		ui->deposit->clear();
		ui->pin->clear();
}

void Bankomat::on_cancel_clicked()
{
		this->close();
}

void Bankomat::on_createButton_2_clicked()
{
	if (ui->cardNumber->text().isNull() || ui->pin->text().isNull()) {
		QMessageBox message;
		message.setText("Убедитесь, что заполнили номер карты и ее PIN");
		message.exec();

		return;
	}

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);
	query->prepare("Execute GetCardBalance '" + ui->cardNumber->text() + "', '" + ui->pin->text() + "';");
	query->exec();

	if (query->next()) {
		int balance = query->value(0).toInt();
		QMessageBox message;
		message.setText("Баланс: " + QString::number(balance));
		message.exec();

		return;
	}
	else {
		QMessageBox message;
		message.setText("Что-то пошло не так, перепроверьте введенные вами данные");
		message.exec();

		return;
	}
}
