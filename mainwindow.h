#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "domain/Document.h"
#include "domain/UndoManager.h"

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
    void onInsertClicked();
    void onDeleteClicked();
    void onUndoClicked();

private:
    void updateTextDisplay();

    Ui::MainWindow *ui;
    std::unique_ptr<Document> document;
    UndoManager undoManager;
};

#endif // MAINWINDOW_H
