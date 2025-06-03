#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "domain/InsertCommand.h"
#include "domain/DeleteCommand.h"
#include <QMessageBox>
#include <QTextCursor>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , document(std::make_unique<Document>())
{
    ui->setupUi(this);

    // Отключаем прямое редактирование текста
    ui->textEdit->setReadOnly(true);

    // Подключаем кнопки к слотам
    connect(ui->insertButton, &QPushButton::clicked, this, &MainWindow::onInsertClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    connect(ui->undoButton, &QPushButton::clicked, this, &MainWindow::onUndoClicked);

    // Устанавливаем пустой текст
    updateTextDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInsertClicked()
{
    bool ok;
    int position = ui->positionEdit->text().toInt(&ok);
    QString text = ui->inputEdit->text();


    auto cmd = std::make_unique<InsertCommand>(*document, position, text.toStdString());
    undoManager.executeCommand(std::move(cmd));
    updateTextDisplay();
    ui->inputEdit->clear();
}


void MainWindow::onDeleteClicked()
{
    bool ok;
    int position = ui->positionEdit->text().toInt(&ok);
    int length = ui->inputEdit->text().toInt(&ok);



    auto cmd = std::make_unique<DeleteCommand>(*document, position, length);
    undoManager.executeCommand(std::move(cmd));
    updateTextDisplay();
    ui->inputEdit->clear();
}

void MainWindow::onUndoClicked()
{
    undoManager.undoLast();
    updateTextDisplay();
}

void MainWindow::updateTextDisplay()
{
    ui->textEdit->setPlainText(QString::fromStdString(document->getContent()));
}
