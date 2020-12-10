#include "database.h"
#include "login.h"
#include "ui_login.h"

#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

login::login(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::login)
{
	ui->setupUi(this);

	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(7);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->groupBox->setGraphicsEffect(effect);
}

login::~login()
{
	delete ui;
}

void login::on_pushButton_clicked()
{
		if (ui->login_2->text().isEmpty() || ui->password->text().isEmpty()) {
			QMessageBox message;
			message.setText("Вы не заполнили некоторые поля");
			message.exec();

			return;
		}

		QString login = ui->login_2->text();
		QString password = ui->password->text();

		QSqlDatabase db = DataBase::getInstance()->getDb();
		QSqlQuery *query = new QSqlQuery(db);

		query->prepare("Select E.employee_id From Employee_login_data Elog Join Employee E On E.login_data_id = Elog.login_data_id Where username = '" + login + "' And password = '" + password + "'");
		query->exec();

		if (query->next()) {
			this->close();
			emit successLogin(query->value(0).toInt());
		}
		else {
			QMessageBox message;
			message.setText("Неверные логин или пароль");
			message.exec();
		}
}
