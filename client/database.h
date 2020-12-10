#ifndef DATABASE_H
#define DATABASE_H

#include <qDebug>
#include <QSqlDatabase>

class DataBase
{
public:
	static DataBase *getInstance();
	QSqlDatabase getDb();

private:
	DataBase(int);
	DataBase(DataBase &other) = delete;
	void operator=(const DataBase &) = delete;

	static DataBase *instance;
	QSqlDatabase db;
};

#endif // DATABASE_H
