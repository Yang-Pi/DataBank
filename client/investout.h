#ifndef INVESTOUT_H
#define INVESTOUT_H

#include <QDialog>

namespace Ui {
	class InvestOut;
}

class InvestOut : public QDialog
{
	Q_OBJECT

public:
	explicit InvestOut(QWidget *parent = nullptr);
	~InvestOut();

private slots:
	void on_pushButton_clicked();

private:
	Ui::InvestOut *ui;
};

#endif // INVESTOUT_H
