#include "accountcreator.h"
#include "bankomat.h"
#include "cardcreator.h"
#include "employee.h"
#include "investcreator.h"
#include "mainwindow.h"
#include "manager.h"
#include "manager2.h"
#include "movemoneyfromcardtocard.h"
#include "payforcredit.h"
#include "signup.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QGraphicsDropShadowEffect>
#include <CreditRequestCreator.h>
#include <Login.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setStyles();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setStyles()
{
	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(7);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->employeeButton->setGraphicsEffect(effect);

	effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(7);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->groupBox_1->setGraphicsEffect(effect);

	effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(7);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->groupBox_2->setGraphicsEffect(effect);

	effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(7);
	effect->setXOffset(0);
	effect->setYOffset(1);
	effect->setColor("#909090");

	ui->groupBox_3->setGraphicsEffect(effect);
}

void MainWindow::successLogin(int employee_id)
{
	if (employee_id == 3) {
		Manager2 *manager2 = new Manager2(3);
		manager2->show();
	}
	else {
		Employee *employeeForm = new Employee(employee_id);
		employeeForm->show();
	}
}


void MainWindow::on_signUpButton_clicked()
{
	SignUp *signUpForm = new SignUp();
	signUpForm->show();
}

void MainWindow::on_createCardButton_clicked()
{
		CardCreator *cardForm = new CardCreator;
		cardForm->show();
}

void MainWindow::on_createAccountButton_clicked()
{
		AccountCreator *accountForm = new AccountCreator;
		accountForm->show();
}

void MainWindow::on_createCreditRequestButton_clicked()
{
		CreditRequestCreator *creditForm = new CreditRequestCreator;
		creditForm->show();
}

void MainWindow::on_createInvestButton_clicked()
{
		InvestCreator *investForm = new InvestCreator;
		investForm->show();
}

void MainWindow::on_pushButton_13_clicked()
{
		Bankomat *bankomatForm = new Bankomat;
		bankomatForm->show();
}

void MainWindow::on_pushButton_15_clicked()
{
		MoveMoneyFromCardToCard *moveForm = new MoveMoneyFromCardToCard;
		moveForm->show();
}

void MainWindow::on_employeeButton_clicked()
{
		login *loginForm = new login;

		connect(loginForm, SIGNAL(successLogin(int)), this, SLOT(successLogin(int)));

		loginForm->show();
}

void MainWindow::on_pushButton_14_clicked()
{
	PayForCredit *payCreditForm = new PayForCredit;
	payCreditForm->show();
}
