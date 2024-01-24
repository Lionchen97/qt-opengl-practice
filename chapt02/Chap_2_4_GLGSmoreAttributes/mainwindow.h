#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actDrawRect_triggered();

    void on_actClear_triggered();

    void on_actWireFrame_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
