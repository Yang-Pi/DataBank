#include "accountcreator.h"
#include "database.h"
#include "ui_accountcreator.h"

#include <QGraphicsDropShadowEffect>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <qmessagebox.h>
#include <QDate>

AccountCreator::AccountCreator(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AccountCreator)
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

	query->prepare("Select deposit_tarif_id, rate, min_deposit From Deposit_tarif");
	query->exec();

	while (query->next()) {
		ui->comboBox->addItem("Ставка: " + query->value(1).toString() + "%,\n" + "Минимальный депозит: " + query->value(2).toString());
		vecId.push_back(query->value(0).toInt());
		vecDeposit.push_back(query->value(2).toInt());
	}

	int period = 6; //months
	while (period < 60) {
		ui->comboBox_2->addItem(QString::number(period) + " месяцев");
		period += 6;
	}

//	QSqlQueryModel *modelTarifs = new QSqlQueryModel;
//	modelTarifs->setQuery(*query);
//	ui->comboBox->setModel(modelTarifs);
	//ui->comboBox->setModelColumn(1);
}

AccountCreator::~AccountCreator()
{
	delete ui;
}

void AccountCreator::on_createButton_clicked()
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

	int tarifId = vecId.at(ui->comboBox->currentIndex());

	QString number = "";
	for (int i = 0; i < 16; ++i) {
		number += QString::number(qrand() % 10);
	}

	int deposit = ui->deposit->text().toInt();
	if (deposit < vecDeposit.at(ui->comboBox->currentIndex())) {
		QMessageBox message;
		message.setText("Указанная сумма вклада не соответсвует тарифному плану");
		message.exec();

		return;
	}

	QDate date = QDate::currentDate().addMonths(ui->comboBox_2->currentIndex() *6);

	query->clear();
	query->prepare("Execute OpenAccount " + QString::number(clientId) + "," +  QString::number(tarifId) + ", '" + number + "', " + QString::number(deposit) + ", '" + date.toString(Qt::DateFormat::DefaultLocaleShortDate) + "';");
	query->exec();

	qDebug() << query->lastQuery();

	ui->lineEdit->setText(number);

	QMessageBox message;
	message.setText("Вклад успешно сделан! Проверьте, что номер счета появился в соответствующем поле");
	message.exec();
}

void AccountCreator::on_checkData_clicked()
{
	if (ui->pasportSeries->text().isEmpty() || ui->pasportNumber->text().isEmpty() || ui->lineEdit->text().isEmpty()) {
		QMessageBox message;
		message.setText("Убедитесь, что вы заполнили все паспортные данные и номер счета");
		message.exec();

		return;
	}
	int pasportSeries = ui->pasportSeries->text().toInt();
	int pasportNumber = ui->pasportNumber->text().toInt();
	QString number = ui->lineEdit->text();

	QSqlDatabase db = DataBase::getInstance()->getDb();
	QSqlQuery *query = new QSqlQuery(db);
	query->prepare("Execute GetAccountBalance " + QString::number(pasportSeries) + ", " + QString::number(pasportNumber) + ", '" + number + "';");
	query->exec();

	if (query->next()) {
		QMessageBox message;
		message.setText("Информация о вкладе \nНомер: " + query->value(0).toString() + "\nСумма: " + query->value(1).toString() + "\nНакопления: " + query->value(2).toString() + "\nДата закрытия: " + query->value(3).toString());
		message.exec();
	}
	else {
		QMessageBox message;
		message.setText("Что-то пошло не так, проверьте введенные вами данные");
		message.exec();
	}

}

void AccountCreator::on_cancel_clicked()
{
		this->close();
}

void AccountCreator::on_cancel_2_clicked()
{
		ui->pasportSeries->clear();
		ui->pasportNumber->clear();
		ui->lineEdit->clear();
		ui->deposit->clear();
}
