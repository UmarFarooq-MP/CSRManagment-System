#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::addToRecord);
    connect(ui->findbutton,&QPushButton::clicked,this,&MainWindow::findDeliveryCost);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToRecord() {
    if (ui->lineEdit_2->text() != "" && ui->lineEdit_3->text() != "") {
       m_dbManager.addToDatabase(ui->lineEdit_2->text(),ui->lineEdit_3->text());
    }
}

void MainWindow::findDeliveryCost() {
    if (ui->findedit->text() != "") {
        QString value = m_dbManager.findCharges(ui->findedit->text());
        if (value == "-1") {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","We Don't Deliver There");
            messageBox.setFixedSize(500,200);

        }else {
            ui->findresult->setText(value);
        }
    }
}

