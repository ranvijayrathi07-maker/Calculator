#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digits_pressed();

    void on_Point_button_released();

    void unary_operator();

    void binary_operation_pressed();

    void clear_pressed();

    void on_Equal_button_released();

private:
    Ui::MainWindow *ui;
    QPoint dragPos;
    double first_num = 0;
    bool userIsTypingSecondNumber = false;
    QString mathOperator;
};

#endif // MAINWINDOW_H
