#include "database.h"
#include "payforcredit.h"
#include "ui_payforcredit.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

PayForCredit::PayForCredit(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PayForCredit)
{
	ui->setupUi(this);
}

PayForCredit::~PayForCredit()
{
	delete ui;
}

void PayForCredit::on_pushButton_clicked()
{
	if (ui->creditNumber->text().isEmpty() || ui->cardNumber->text().isEmpty() || ui->pin->text().isEmpty()) {
		QMessageBox message;
		message.setText("Убедитесь, что заполнили все поля");
		message.exec();

		return;
	}

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);

	query->prepare("Execute PayForCredit '" + ui->creditNumber->text() + "', '" + ui->cardNumber->text() + "', '" + ui->pin->text() + "';");
	query->exec();

	if (query->next()) {
		if (query->value(0).toString() == "Недостаточно средств") {
			QMessageBox message;
			message.setText("Недостаточно средств");
			message.exec();
		}
		else {
			QMessageBox message;
			message.setText("Оплачено! Осталось заплатить: " + query->value(0).toString() + "рублей \nСледующий платеж " + query->value(1).toString() + " рублей " + query->value(2).toString());
			message.exec();
		}
	}
	else {
		QMessageBox message;
		message.setText("Что-то пошло не так. Попробуйте повторить операцию позже");
		message.exec();
	}
}

void PayForCredit::on_canceButton_clicked()
{
		this->close();
}
