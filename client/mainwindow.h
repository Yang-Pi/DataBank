#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_signUpButton_clicked();

	void on_createCardButton_clicked();

	void on_createAccountButton_clicked();

	void on_createCreditRequestButton_clicked();

	void on_createInvestButton_clicked();

	void on_pushButton_13_clicked();

	void on_pushButton_15_clicked();

	void on_employeeButton_clicked();

private:
	Ui::MainWindow *ui;

	void setStyles();

private slots:
		void successLogin(int);
		void on_pushButton_14_clicked();
};
#endif // MAINWINDOW_H
