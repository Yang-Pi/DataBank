#include "database.h"
#include "movemoneyfromcardtocard.h"
#include "ui_movemoneyfromcardtocard.h"

#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

MoveMoneyFromCardToCard::MoveMoneyFromCardToCard(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MoveMoneyFromCardToCard)
{
	ui->setupUi(this);

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(7);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->groupBox->setGraphicsEffect(effect);
}

MoveMoneyFromCardToCard::~MoveMoneyFromCardToCard()
{
	delete ui;
}

void MoveMoneyFromCardToCard::on_createButton_clicked()
{
		if (ui->cardNumber1->text().isEmpty() || ui->pin->text().isEmpty() || ui->sum->text().isEmpty() || ui->cardNumber_2->text().isEmpty()) {
			QMessageBox message;
			message.setText("Убедитесь, что вы заполнили все поля");
			message.exec();

			return;
		}

		QString card1 = ui->cardNumber1->text();
		QString pin = ui->pin->text();
		int sum = ui->sum->text().toInt();
		QString card2 = ui->cardNumber_2->text();

		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);
		query->prepare("Execute GetCardBalance '" + card1 + "', '" + pin + "';");
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
		query->prepare("Execute MoveMoneyFromCardToCard '" + card1 + "', '" + pin + "', '" + card2 + "', " + QString::number(sum) + ";");

		query->clear();
		query->prepare("Execute GetCardBalance '" + card1 + "', '" + pin + "';");
		query->exec();

		if (query->next()) {
			QMessageBox message;
			message.setText("Перевод успешно осуществлен! \nТеперь у вас " + query->value(0).toString() + " рублей");
			message.exec();
		}
		else {
			QMessageBox message;
			message.setText("Что-то пошло не так, попробуйте еще раз");
			message.exec();
		}
}

void MoveMoneyFromCardToCard::on_cancel_clicked()
{
		this->close();
}
