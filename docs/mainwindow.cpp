#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация базы данных
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("documents.db");

    if (!m_db.open()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть базу данных");
        return;
    }

    // Создание таблицы, если не существует
    createDatabase();

    // Настройка модели
    model = new QSqlTableModel(this, m_db);
    model->setTable("Documents");
    model->select();

    // Привязка модели к таблице
    ui->tableView->setModel(model);

    // Установка заголовков с заглавных букв
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Название документа");
    model->setHeaderData(2, Qt::Horizontal, "Автор");
    model->setHeaderData(3, Qt::Horizontal, "Отдел");
    model->setHeaderData(4, Qt::Horizontal, "Размер (МБ)");

    // Опционально: скрыть ID (раскомментируйте, если не нужен)
    // ui->tableView->hideColumn(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createDatabase()
{
    QSqlQuery query(m_db);
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS Documents ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "author TEXT NOT NULL, "
        "department TEXT NOT NULL, "
        "size_mb REAL NOT NULL)"
        );

    if (!success) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать таблицу: " + query.lastError().text());
    }
}

void MainWindow::on_pushButtonAdd_clicked()
{
    QString name = ui->lineEditName->text().trimmed();
    QString author = ui->lineEditAuthor->text().trimmed();
    QString department = ui->lineEditDepartment->text().trimmed();
    bool ok;
    double size_mb = ui->lineEditSize->text().toDouble(&ok);

    if (name.isEmpty() || author.isEmpty() || department.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все обязательные поля!");
        return;
    }

    if (!ok || size_mb <= 0) {
        QMessageBox::warning(this, "Ошибка", "Размер должен быть положительным числом!");
        return;
    }

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO Documents (name, author, department, size_mb) VALUES (?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(author);
    query.addBindValue(department);
    query.addBindValue(size_mb);

    if (!query.exec()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить запись: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Успех", "Запись успешно добавлена!");
        model->select(); // Обновить таблицу
    }
}

void MainWindow::on_pushButtonRem_clicked()
{
    bool ok;
    int id = ui->lineEditID->text().toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный ID для удаления!");
        return;
    }

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM Documents WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить запись: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Успех", "Запись успешно удалена!");
        model->select(); // Обновить таблицу
    }
}

void MainWindow::on_allDataViewButton_clicked()
{
    model->setFilter("");
    model->select();
}

void MainWindow::on_filterDataButton_clicked()
{
    QString department = "Техподдержка";
    model->setFilter(QString("department = '%1'").arg(department));
    model->select();
}

void MainWindow::on_filterData2Button_clicked()
{
    double minSize = 10.0;
    model->setFilter(QString("size_mb > %1").arg(minSize));
    model->select();
}
