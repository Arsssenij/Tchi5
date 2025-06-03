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

    if (!ok || position < 0) {
        QMessageBox::warning(this, "Ошибка", "Некорректная позиция");
        return;
    }

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Текст для вставки не может быть пустым");
        return;
    }

    int currentLength = static_cast<int>(document->getContent().length());

    // ✅ допускаем вставку только в пределах [0, длина]
    if (position > currentLength) {
        QMessageBox::warning(this, "Ошибка", QString("Позиция %1 превышает длину текста (%2)").arg(position).arg(currentLength));
        return;
    }

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

    if (!ok || position < 0 || length <= 0) {
        QMessageBox::warning(this, "Ошибка", "Некорректные параметры удаления");
        return;
    }

    if (position + length > static_cast<int>(document->getContent().length())) {
        QMessageBox::warning(this, "Ошибка", "Удаление выходит за границы текста");
        return;
    }

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
