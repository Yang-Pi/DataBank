#include "database.h"

#include <QSqlDatabase>

DataBase *DataBase::instance = nullptr;

DataBase *DataBase::getInstance()
{
	if (instance == nullptr) {
		instance = new DataBase(1);
	}

	return instance;
}

DataBase::DataBase(int a)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	QString connectString = QStringLiteral(
			"DRIVER={SQL Server};"
			"SERVER={LAPTOP-6L6A4F3S};"
			"DATABASE=Sber;"
			"Trusted_Connection=yes;");
	db.setDatabaseName(connectString);

	if (db.open()) {
		qDebug() << "CONNECTED";
	}
	else {
		qDebug() << "NO";
	}
}

QSqlDatabase DataBase::getDb()
{
	return db;
}


