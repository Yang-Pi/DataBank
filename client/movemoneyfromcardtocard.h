#ifndef MOVEMONEYFROMCARDTOCARD_H
#define MOVEMONEYFROMCARDTOCARD_H

#include <QDialog>

namespace Ui {
	class MoveMoneyFromCardToCard;
}

class MoveMoneyFromCardToCard : public QDialog
{
	Q_OBJECT

public:
	explicit MoveMoneyFromCardToCard(QWidget *parent = nullptr);
	~MoveMoneyFromCardToCard();

private slots:
	void on_createButton_clicked();

	void on_cancel_clicked();

private:
	Ui::MoveMoneyFromCardToCard *ui;
};

#endif // MOVEMONEYFROMCARDTOCARD_H
