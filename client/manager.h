#ifndef MANAGER_H
#define MANAGER_H

#include <QDialog>

namespace Ui {
	class Manager;
}

class Manager : public QDialog
{
	Q_OBJECT

public:
	explicit Manager(int, QWidget *parent = nullptr);
	~Manager();

private slots:
	void on_investRequest_clicked();
	void on_getRequest_clicked();
	void on_clientInfoButton_clicked();

private:
	Ui::Manager *ui;
	int id_;
	QVector<int> vecId;
};

#endif // MANAGER_H
