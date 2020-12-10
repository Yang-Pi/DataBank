#ifndef BANKOMAT_H
#define BANKOMAT_H

#include <QDialog>

namespace Ui {
	class Bankomat;
}

class Bankomat : public QDialog
{
	Q_OBJECT

public:
	explicit Bankomat(QWidget *parent = nullptr);
	~Bankomat();

private slots:
	void on_createButton_clicked();

	void on_cancel_2_clicked();

	void on_cancel_clicked();

	void on_createButton_2_clicked();

private:
	Ui::Bankomat *ui;
};

#endif // BANKOMAT_H
