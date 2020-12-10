#ifndef CARDCREATOR_H
#define CARDCREATOR_H

#include <QDialog>

namespace Ui {
	class CardCreator;
}

class CardCreator : public QDialog
{
	Q_OBJECT

public:
	explicit CardCreator(QWidget *parent = nullptr);
	~CardCreator();

private slots:
	void on_createButton_clicked();

	void on_checkData_clicked();

	void on_cancel_clicked();

private:
	Ui::CardCreator *ui;
};

#endif // CARDCREATOR_H
