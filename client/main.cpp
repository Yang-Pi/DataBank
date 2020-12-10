#include "database.h"
#include "mainwindow.h"

#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
	DataBase::getInstance();

	QApplication a(argc, argv);

	MainWindow w;
	w.show();


	return a.exec();
}
