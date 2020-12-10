#ifndef MANAGER2_H
#define MANAGER2_H

#include <QDialog>

namespace Ui {
	class Manager2;
}

class Manager2 : public QDialog
{
	Q_OBJECT

public:
	explicit Manager2(int, QWidget *parent = nullptr);
	~Manager2();

private slots:
	void on_investRequest_2_clicked();

	void on_getRequest_2_clicked();

	void on_clientInfoButton_2_clicked();

	void on_creditRequests_7_clicked();

	void on_compute_clicked();

	void on_cancel_clicked();

	void on_checkData_clicked();

	void on_creditRequests_8_clicked();

	void on_creditRequests_6_clicked();

	void on_creditRequests_9_clicked();

	void on_creditRequests_11_clicked();

	void on_creditRequests_10_clicked();

	void on_cancel_3_clicked();

private:
	Ui::Manager2 *ui;
	int id_;
	QVector<int> vecId;
};

#endif // MANAGER2_H
