#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList searchOptions = {"Название", "Автор", "Жанр", "Год выхода"};
    ui->comboBox1->addItems(searchOptions);

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("library");
    db.setUserName("postgres");
    db.setHostName("localhost");
    db.setPassword("123456");
    if (!db.open()){
        qDebug() << db.lastError().text();
    }
    else {
        qDebug() << "Success!";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton1_clicked()
{
    QString bookTitle = ui->lineEdit1->text();
    int yearOfPublication = ui->lineEdit2->text().toInt();
    QString authorFirstName = ui->lineEdit3->text();
    QString authorLastName = ui->lineEdit4->text();
    int yearOfBirth = ui->lineEdit5->text().toInt();
    QString country = ui->lineEdit6->text();
    QString publisherName = ui->lineEdit7->text();
    QString publisherAddress = ui->lineEdit8->text();
    QString genre = ui->lineEdit9->text();

    QString queryText = QString("DO $$ "
                                "BEGIN "
                                "CALL add_new_book("
                                "    '%1', %2, "
                                "    '%3', '%4', %5, "
                                "    '%6', '%7', "
                                "    '%8', '%9' "
                                "); "
                                "END $$;")
                           .arg(bookTitle)
                           .arg(yearOfPublication)
                           .arg(authorFirstName)
                           .arg(authorLastName)
                           .arg(yearOfBirth)
                           .arg(country)
                           .arg(publisherName)
                           .arg(publisherAddress)
                           .arg(genre);

    QSqlQuery query;
    query.exec(queryText);

    if (query.lastError().isValid()) {
        ui->textEdit1->append("Ошибка выполнения запроса!\n-------------------\n");
    } else {
        ui->textEdit1->append("Книга успешно добавлена!\n-------------------\n");
    }
}

void MainWindow::on_pushButton2_clicked()
{
    QString searchParameter = ui->comboBox1->currentText();

    QString searchValue = ui->lineEdit10->text();

    QString queryText;

    if (searchParameter == "Название") {
        queryText = "SELECT b.title, a.first_name, a.last_name, b.year_of_publication, p.name "
                    "FROM books b "
                    "JOIN authors a ON b.author_id = a.id_author "
                    "JOIN publishers p ON b.publisher_id = p.id_publisher "
                    "WHERE b.title = :value";
    } else if (searchParameter == "Автор") {
        queryText = "SELECT b.title, a.first_name, a.last_name, b.year_of_publication, p.name "
                    "FROM books b "
                    "JOIN authors a ON b.author_id = a.id_author "
                    "JOIN publishers p ON b.publisher_id = p.id_publisher "
                    "WHERE a.first_name = :value OR a.last_name = :value";
    } else if (searchParameter == "Жанр") {
        queryText = "SELECT b.title, a.first_name, a.last_name, b.year_of_publication, p.name "
                    "FROM books b "
                    "JOIN authors a ON b.author_id = a.id_author "
                    "JOIN publishers p ON b.publisher_id = p.id_publisher "
                    "JOIN genres g ON b.genre_id = g.id_genre "
                    "WHERE g.name = :value";
    } else if (searchParameter == "Год выхода") {
        queryText = "SELECT b.title, a.first_name, a.last_name, b.year_of_publication, p.name "
                    "FROM books b "
                    "JOIN authors a ON b.author_id = a.id_author "
                    "JOIN publishers p ON b.publisher_id = p.id_publisher "
                    "WHERE b.year_of_publication = :value";
    }

    QSqlQuery query;
    query.prepare(queryText);
    query.bindValue(":value", searchValue);

    if (query.exec()) {
        ui->textEdit1->clear();

        while (query.next()) {
            QString resultString = QString("Название: %1\nАвтор: %2 %3\nГод выхода: %4\nИздательство: %5\n-------------------\n")
                                          .arg(query.value("title").toString())
                                          .arg(query.value("first_name").toString())
                                          .arg(query.value("last_name").toString())
                                          .arg(query.value("year_of_publication").toString())
                                          .arg(query.value("name").toString());

            ui->textEdit1->append(resultString);
            }
    } else {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    }
}