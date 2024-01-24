#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget); // 将opgl窗口替换centralwidget，减少内存
}

MainWindow::~MainWindow()
{
    delete ui;
}
