#ifndef ACCOUNTCREATOR_H
#define ACCOUNTCREATOR_H

#include <QDialog>

namespace Ui {
	class AccountCreator;
}

class AccountCreator : public QDialog
{
	Q_OBJECT

public:
	explicit AccountCreator(QWidget *parent = nullptr);
	~AccountCreator();

private slots:
	void on_createButton_clicked();

	void on_checkData_clicked();

	void on_cancel_clicked();

	void on_cancel_2_clicked();

private:
	Ui::AccountCreator *ui;

	QVector<int> vecId;
	QVector<int> vecDeposit;
};

#endif // ACCOUNTCREATOR_H
