#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QDialog>

namespace Ui {
	class Employee;
}

class Employee : public QDialog
{
	Q_OBJECT

public:
	explicit Employee(int, QWidget *parent = nullptr);
	~Employee();

private slots:
	void on_creditRequests_clicked();

	void on_creditRequests_2_clicked();

	void on_creditRequests_4_clicked();

	void on_creditRequests_3_clicked();

	void on_creditRequests_5_clicked();

	void on_cancel_clicked();

	void on_cancel_2_clicked();

	void on_cancel_3_clicked();

private:
	Ui::Employee *ui;
	int id_;
	QVector<int> vecId;
	QVector<int> vecSums;
};

#endif // EMPLOYEE_H
