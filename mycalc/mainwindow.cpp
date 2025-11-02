#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    operand1 = 0.0;
    pendingOperator = '\0';
    currentInput = "0";
    waitingForOperand = false;
    ui->display->setText("0");
    ui->display->setReadOnly(true);
    ui->display->setAlignment(Qt::AlignRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayValue(const QString &text)
{
    ui->display->setText(text);
    ui->display->setReadOnly(true);
    ui->display->setAlignment(Qt::AlignRight);
}

void MainWindow::displayValue(double value)
{
    QString str = QString::number(value, 'g', 15);
    if (str.length() > 12) {
        str = QString::number(value, 'e', 6);
    }
    ui->display->setText(str);
    ui->display->setReadOnly(true);
    ui->display->setAlignment(Qt::AlignRight);
}

// Новая функция: отображает currentInput с умным форматом при длинном вводе
void MainWindow::displayInput()
{
    // Попробуем преобразовать в число и обратно — чтобы проверить длину
    bool ok;
    double val = currentInput.toDouble(&ok);

    if (ok) {
        QString compact = QString::number(val, 'g', 15);
        // Если compact короче и не теряет точность — можно использовать?
        // Но мы хотим сохранить ввод как есть, если он короткий
        if (currentInput.length() <= 12) {
            ui->display->setText(currentInput);
        } else {
            // Слишком длинный ввод — показываем в e-формате
            QString exp = QString::number(val, 'e', 6);
            ui->display->setText(exp);
        }
    } else {
        // Если не число (например, "5 +"), показываем как есть
        ui->display->setText(currentInput);
    }
    ui->display->setReadOnly(true);
    ui->display->setAlignment(Qt::AlignRight);
}

// === ЦИФРЫ ===
void MainWindow::on_btn0_clicked()
{
    if (waitingForOperand) {
        currentInput = "0";
        waitingForOperand = false;
    } else {
        if (currentInput == "0")
            currentInput = "0";
        else
            currentInput += "0";
    }
    displayInput();
}

void MainWindow::on_btn1_clicked()
{
    if (waitingForOperand) {
        currentInput = "1";
        waitingForOperand = false;
    } else {
        if (currentInput == "0")
            currentInput = "1";
        else
            currentInput += "1";
    }
    displayInput();
}

void MainWindow::on_btn2_clicked()
{
    if (waitingForOperand) {
        currentInput = "2";
        waitingForOperand = false;
    } else {
        if (currentInput == "0")
            currentInput = "2";
        else
            currentInput += "2";
    }
    displayInput();
}

void MainWindow::on_btn3_clicked()
{
    if (waitingForOperand) {
        currentInput = "3";
        waitingForOperand = false;
    } else {
        if (currentInput == "0")
            currentInput = "3";
        else
            currentInput += "3";
    }
    displayInput();
}

void MainWindow::on_btn4_clicked()
{
    if (waitingForOperand) {
        currentInput = "4";
        waitingForOperand = false;
    } else {
        if (currentInput == "0")
            currentInput = "4";
        else
            currentInput += "4";
    }
    displayInput();
}

void MainWindow::on_btn5_clicked()
{
    if (waitingForOperand) {
        currentInput = "5";
        waitingForOperand = false;
    } else {
        if (currentInput == "0")
            currentInput = "5";
        else
            currentInput += "5";
    }
    displayInput();
}

void MainWindow::on_btn6_clicked()
{
    if (waitingForOperand) {
        currentInput = "6";
        waitingForOperand = false;
    } else {
        if (currentInput == "0")
            currentInput = "6";
        else
            currentInput += "6";
    }
    displayInput();
}

void MainWindow::on_btn7_clicked()
{
    if (waitingForOperand) {
        currentInput = "7";
        waitingForOperand = false;
    } else {
        if (currentInput == "0")
            currentInput = "7";
        else
            currentInput += "7";
    }
    displayInput();
}

void MainWindow::on_btn8_clicked()
{
    if (waitingForOperand) {
        currentInput = "8";
        waitingForOperand = false;
    } else {
        if (currentInput == "0")
            currentInput = "8";
        else
            currentInput += "8";
    }
    displayInput();
}

void MainWindow::on_btn9_clicked()
{
    if (waitingForOperand) {
        currentInput = "9";
        waitingForOperand = false;
    } else {
        if (currentInput == "0")
            currentInput = "9";
        else
            currentInput += "9";
    }
    displayInput();
}

// === ТОЧКА ===
void MainWindow::on_btnDot_clicked()
{
    if (waitingForOperand) {
        currentInput = "0.";
        waitingForOperand = false;
    } else if (!currentInput.contains('.')) {
        currentInput += '.';
    }
    displayInput();
}

// === ОЧИСТКА ===
void MainWindow::on_btnClear_clicked()
{
    operand1 = 0.0;
    pendingOperator = '\0';
    currentInput = "0";
    waitingForOperand = false;
    ui->display->setText("0");
}

// === ОПЕРАЦИИ ===
void MainWindow::on_btnPlus_clicked()
{
    if (pendingOperator != '\0' && !waitingForOperand) {
        on_btnEquals_clicked();
    }
    operand1 = currentInput.toDouble();
    pendingOperator = '+';
    waitingForOperand = true;
    displayValue(QString::number(operand1) + " +");
}

void MainWindow::on_btnMinus_clicked()
{
    if (pendingOperator != '\0' && !waitingForOperand) {
        on_btnEquals_clicked();
    }
    operand1 = currentInput.toDouble();
    pendingOperator = '-';
    waitingForOperand = true;
    displayValue(QString::number(operand1) + " -");
}

void MainWindow::on_btnMul_clicked()
{
    if (pendingOperator != '\0' && !waitingForOperand) {
        on_btnEquals_clicked();
    }
    operand1 = currentInput.toDouble();
    pendingOperator = '*';
    waitingForOperand = true;
    displayValue(QString::number(operand1) + " *");
}

void MainWindow::on_btnDiv_clicked()
{
    if (pendingOperator != '\0' && !waitingForOperand) {
        on_btnEquals_clicked();
    }
    operand1 = currentInput.toDouble();
    pendingOperator = '/';
    waitingForOperand = true;
    displayValue(QString::number(operand1) + " /");
}

// === РАВНО ===
void MainWindow::on_btnEquals_clicked()
{
    if (pendingOperator == '\0') return;

    double operand2 = currentInput.toDouble();
    double result = 0.0;

    switch (pendingOperator) {
    case '+': result = operand1 + operand2; break;
    case '-': result = operand1 - operand2; break;
    case '*': result = operand1 * operand2; break;
    case '/':
        if (operand2 == 0.0) {
            displayValue("Ошибка: деление на ноль");
            pendingOperator = '\0';
            waitingForOperand = true;
            return;
        }
        result = operand1 / operand2;
        break;
    }

    currentInput = QString::number(result, 'g', 15);
    displayValue(result);
    pendingOperator = '\0';
    waitingForOperand = true;
}

// === СПЕЦФУНКЦИИ ===

void MainWindow::on_btnPlusMinus_clicked()
{
    double val = currentInput.toDouble();
    val = -val;
    currentInput = QString::number(val, 'g', 15);
    displayValue(val);
}

void MainWindow::on_btnSin_clicked()
{
    double val = currentInput.toDouble();
    double res = sin(val);
    currentInput = QString::number(res, 'g', 15);
    displayValue(res);
    waitingForOperand = true;
}

void MainWindow::on_btnLog_clicked()
{
    bool ok;
    double x = currentInput.toDouble(&ok);
    if (!ok || x <= 0) {
        displayValue("Ошибка: x > 0");
        waitingForOperand = true;
        return;
    }

    double n = QInputDialog::getDouble(
        this, "Основание логарифма",
        "Введите основание n:", 10.0, 0.001, 1e6, 3, &ok
        );

    if (!ok || n <= 0 || n == 1) {
        displayValue("Ошибка: n > 0 и ≠ 1");
        waitingForOperand = true;
        return;
    }

    double res = log(x) / log(n);
    currentInput = QString::number(res, 'g', 15);
    displayValue(res);
    waitingForOperand = true;
}

void MainWindow::on_btnHarmonic_clicked()
{
    bool ok;
    int n = currentInput.toInt(&ok);
    if (!ok || n <= 0) {
        displayValue("Ошибка: n ≥ 1");
        waitingForOperand = true;
        return;
    }

    double h = 0.0;
    for (int i = 1; i <= n; ++i) {
        h += 1.0 / i;
    }

    currentInput = QString::number(h, 'g', 15);
    displayValue(h);
    waitingForOperand = true;
}
