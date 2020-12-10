#include "signup.h"
#include "ui_signup.h"
#include "database.h"

#include <QGraphicsDropShadowEffect>
#include <qsqlquery.h>
#include <qDebug>
#include <QMessageBox>

SignUp::SignUp(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SignUp)
{
	ui->setupUi(this);

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(7);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->groupBox->setGraphicsEffect(effect);
}

SignUp::~SignUp()
{
	delete ui;
}

void SignUp::on_pushButton_clicked()
{
		QString surname = ui->surname->text();
		QString name = ui->name->text();
		QString fatherName = ui->fatherName->text();
		int pasportSeries = ui->pasportSeries->text().toInt();
		int pasportNumber = ui->pasportNumber->text().toInt();
		QDate date = ui->dateEdit->date();
		QString phoneNumber = ui->phoneNumber->text();

		if (!surname.isEmpty() || !name.isEmpty()
				|| ui->pasportSeries->text().length() == 4
				|| ui->pasportNumber->text().length() == 6) {

			QSqlDatabase db = DataBase::getInstance()->getDb();

			QSqlQuery *query = new QSqlQuery(db);
			query->prepare("Execute SignUp '"
										 + name + "', '"
										 + surname + "', '"
										 + fatherName + "', "
										 + QString::number(pasportSeries) + ", "
										 + QString::number(pasportNumber) + ", '"
										 + date.toString(Qt::DateFormat::DefaultLocaleShortDate) + "', '"
										 + phoneNumber + "';");
			qDebug() << query->lastQuery();
			int res = query->exec();

			QMessageBox::StandardButton reply;

			QMessageBox message;
			message.setText(name + " " + fatherName + ", вы были успешно зарегистрированы!");
			message.exec();

			this->close();
		}
		else {
			QMessageBox message;
			message.setText("Убедитесь, что вы заполнили все поля");
			message.exec();
		}
}

void SignUp::on_pushButton_2_clicked()
{
		this->close();
}
