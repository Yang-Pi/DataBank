#ifndef INVESTCREATOR_H
#define INVESTCREATOR_H

#include <QDialog>

namespace Ui {
	class InvestCreator;
}

class InvestCreator : public QDialog
{
	Q_OBJECT

public:
	explicit InvestCreator(QWidget *parent = nullptr);
	~InvestCreator();

private slots:
	void on_createButton_clicked();

	void on_cancel_2_clicked();

	void on_cancel_clicked();

	void on_createButton_2_clicked();

private:
	Ui::InvestCreator *ui;

	QVector<int> vecId;
	QVector<int> vecSums;
};

#endif // INVESTCREATOR_H
