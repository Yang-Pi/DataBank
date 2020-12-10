#include "database.h"
#include "investcreator.h"
#include "investout.h"
#include "ui_investcreator.h"

#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

InvestCreator::InvestCreator(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::InvestCreator)
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

	query->prepare("Select source_id, type, sum From Extra_money_source");
	query->exec();

	while (query->next()) {
		ui->comboBox->addItem("Компания: " + query->value(1).toString() + ",\n" + "Вложенная в нее сумма: " + query->value(2).toString());
		vecId.push_back(query->value(0).toInt());
		vecSums.push_back(query->value(2).toInt());
	}
}

InvestCreator::~InvestCreator()
{
	delete ui;
}

void InvestCreator::on_createButton_clicked()
{
		if (ui->cardNumber->text().isEmpty() || ui->pin->text().isEmpty() || ui->sum->text().isEmpty()) {
			QMessageBox message;
			message.setText("Убедитесь, что заполнили все данные");
			message.exec();

			return;
		}

		QString cardNumber = ui->cardNumber->text();
		QString pin = ui->pin->text();
		int investId = vecId.at(ui->comboBox->currentIndex());
		int sum = ui->sum->text().toInt();

		if (sum > vecSums.at(ui->comboBox->currentIndex())) {
			QMessageBox message;
			message.setText("Сумма превышает лимит");
			message.exec();

			return;
		}

		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);

		query->prepare("Execute MakeInvestIntoBank '" + cardNumber + "', '" + pin + "', " + QString::number(investId) + ", " + QString::number(sum) + ";");
		query->exec();
		qDebug() << query->lastQuery();

		QMessageBox message;
		message.setText("Теперь вы инвестор!");
		message.exec();
}

void InvestCreator::on_cancel_2_clicked()
{
		ui->cardNumber->clear();
		ui->pin->clear();
		ui->sum->clear();
}

void InvestCreator::on_cancel_clicked()
{
		this->close();
}

void InvestCreator::on_createButton_2_clicked()
{
		InvestOut *investOutForm = new InvestOut;
		investOutForm->show();
}
