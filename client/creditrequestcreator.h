#ifndef CREDITREQUESTCREATOR_H
#define CREDITREQUESTCREATOR_H

#include <QDialog>

namespace Ui {
	class creditRequestCreator;
}

class CreditRequestCreator : public QDialog
{
	Q_OBJECT

public:
	explicit CreditRequestCreator(QWidget *parent = nullptr);
	~CreditRequestCreator();

private slots:
	void on_createButton_clicked();

	void on_checkData_clicked();

	void on_cancel_2_clicked();

	void on_cancel_clicked();

private:
	Ui::creditRequestCreator *ui;

	QVector<int> vecId;
	QVector<int> vecSums;
};

#endif // CREDITREQUESTCREATOR_H
