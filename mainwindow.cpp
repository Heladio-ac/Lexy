#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "token.h"
#include "error.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lexer = new Lexer();

    TokensModel = new QStandardItemModel(ui->TokensTable);
    ErrorsModel = new QStandardItemModel(ui->ErrorsTable);
    ui->TokensTable->setModel(TokensModel);
    ui->ErrorsTable->setModel(ErrorsModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoadButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open eyement file"),
                                            "/home", tr("eye Files (*.eye)"));
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Non existant file");
    } else {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)){
            code = file.readAll();
            ui->CodeText->setPlainText(code);
        }
    }
}

void MainWindow::on_CodeText_textChanged()
{
    code = ui->CodeText->toPlainText();
}

void MainWindow::on_AnalyzeButton_clicked()
{
    lexer->transduce(code.toStdString() + " ");
    TokensModel->clear();
    QList<QStandardItem *> row;
    for (Token token: lexer->tokens) {
        row.clear();
        row.append(new QStandardItem(QString::fromStdString(token.getGrammeme())));
        row.append(new QStandardItem(QString::fromStdString(token.lexeme)));
        TokensModel->appendRow(row);
    }
    for (Error error: lexer->errors) {
        row.clear();
        row.append(new QStandardItem(QString::fromStdString(error.getError())));
        row.append(new QStandardItem(QString::fromStdString(error.lexeme)));
        ErrorsModel->appendRow(row);
    }
}

void MainWindow::on_SaveButton_clicked()
{
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream out(&file);
        out << code;
    }
}
