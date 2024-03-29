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

void MainWindow::on_actDrawRect_triggered()
{
    ui->openGLWidget->drawShape(OpenGlWidget::Rect);
}


void MainWindow::on_actClear_triggered()
{
    ui->openGLWidget->drawShape(OpenGlWidget::None);
}


void MainWindow::on_actWireFrame_triggered()
{
    ui->openGLWidget->setWireFrame(ui->actWireFrame->isChecked());

}

