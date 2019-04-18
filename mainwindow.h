#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QStandardItemModel>
#include <QStandardItem>
#include "lexer.h"

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

    void on_LoadButton_clicked();

    void on_CodeText_textChanged();

    void on_AnalyzeButton_clicked();

    void on_SaveButton_clicked();

private:
    Ui::MainWindow *ui;

    Lexer *lexer;

    QString fileName;
    QString code;

    QStandardItemModel *TokensModel;
    QStandardItemModel *ErrorsModel;
};

#endif // MAINWINDOW_H
