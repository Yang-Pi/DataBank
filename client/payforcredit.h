#ifndef PAYFORCREDIT_H
#define PAYFORCREDIT_H

#include <QDialog>

namespace Ui {
	class PayForCredit;
}

class PayForCredit : public QDialog
{
	Q_OBJECT

public:
	explicit PayForCredit(QWidget *parent = nullptr);
	~PayForCredit();

private slots:
	void on_pushButton_clicked();

	void on_canceButton_clicked();

private:
	Ui::PayForCredit *ui;
};

#endif // PAYFORCREDIT_H
