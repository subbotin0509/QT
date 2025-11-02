#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QInputDialog>

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
    // Цифры
    void on_btn0_clicked();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();

    // Точка
    void on_btnDot_clicked();

    // Очистка
    void on_btnClear_clicked();

    // Операции
    void on_btnPlus_clicked();
    void on_btnMinus_clicked();
    void on_btnMul_clicked();
    void on_btnDiv_clicked();
    void on_btnEquals_clicked();

    // Специальные функции
    void on_btnPlusMinus_clicked();
    void on_btnSin_clicked();
    void on_btnLog_clicked();
    void on_btnHarmonic_clicked();

private:
    Ui::MainWindow *ui;

    double operand1;
    char pendingOperator;
    QString currentInput;
    bool waitingForOperand;

    void displayValue(double value);
    void displayValue(const QString &text);
    void displayInput(); // ← новая функция для отображения ввода
};

#endif // MAINWINDOW_H
