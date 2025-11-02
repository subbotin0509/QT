#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql> // Подключаем модуль SQL

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonRem_clicked();
    void on_allDataViewButton_clicked();
    void on_filterDataButton_clicked();
    void on_filterData2Button_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase m_db;     // Объект базы данных
    QSqlQuery* query;      // Указатель на запрос
    QSqlTableModel* model; // Модель для таблицы

    void createDatabase(); // Метод для создания БД и таблицы
};

#endif // MAINWINDOW_H
