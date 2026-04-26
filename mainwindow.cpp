#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    first_num = 0;
    userIsTypingSecondNumber = false;
    mathOperator = "";

    connect(ui->Zero_button,  &QPushButton::clicked, this, &MainWindow::digits_pressed);
    connect(ui->One_button,   &QPushButton::clicked, this, &MainWindow::digits_pressed);
    connect(ui->Two_button,   &QPushButton::clicked, this, &MainWindow::digits_pressed);
    connect(ui->Three_button, &QPushButton::clicked, this, &MainWindow::digits_pressed);
    connect(ui->Four_button,  &QPushButton::clicked, this, &MainWindow::digits_pressed);
    connect(ui->Five_button,  &QPushButton::clicked, this, &MainWindow::digits_pressed);
    connect(ui->Six_button,   &QPushButton::clicked, this, &MainWindow::digits_pressed);
    connect(ui->Seven_button, &QPushButton::clicked, this, &MainWindow::digits_pressed);
    connect(ui->Eight_button, &QPushButton::clicked, this, &MainWindow::digits_pressed);
    connect(ui->Nine_button,  &QPushButton::clicked, this, &MainWindow::digits_pressed);

    connect(ui->Point_button, &QPushButton::clicked,
            this, &MainWindow::on_Point_button_released);

    connect(ui->AC_button, &QPushButton::clicked,
            this, &MainWindow::clear_pressed);

    connect(ui->Plusminus_button, &QPushButton::clicked,
            this, &MainWindow::unary_operator);

    connect(ui->Percent_button, &QPushButton::clicked,
            this, &MainWindow::unary_operator);

    connect(ui->Plus_button, &QPushButton::clicked,
            this, &MainWindow::binary_operation_pressed);

    connect(ui->Minus_button, &QPushButton::clicked,
            this, &MainWindow::binary_operation_pressed);

    connect(ui->Multiplication_Button, &QPushButton::clicked,
            this, &MainWindow::binary_operation_pressed);

    connect(ui->Division_button, &QPushButton::clicked,
            this, &MainWindow::binary_operation_pressed);

    connect(ui->Equal_button, &QPushButton::clicked,
            this, &MainWindow::on_Equal_button_released);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::digits_pressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString value = button->text();
    QString current = ui->label->text();

    if (userIsTypingSecondNumber)
    {
        ui->label->setText(value);
        userIsTypingSecondNumber = false;
        return;
    }

    if (current == "0")
        ui->label->setText(value);
    else
        ui->label->setText(current + value);
}
void MainWindow::on_Point_button_released()
{
    QString current = ui->label->text();

    if (userIsTypingSecondNumber)
    {
        ui->label->setText("0.");
        userIsTypingSecondNumber = false;
        return;
    }

    if (!current.contains('.'))
        ui->label->setText(current + ".");
}
void MainWindow::unary_operator()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    double value = ui->label->text().toDouble();

    if (button->text() == "+/-")
        value *= -1;
    else if (button->text() == "%")
        value *= 0.01;

    ui->label->setText(QString::number(value, 'g', 15));
}
void MainWindow::binary_operation_pressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    first_num = ui->label->text().toDouble();
    mathOperator = button->text();
    userIsTypingSecondNumber = true;

    qDebug() << "Operator:" << mathOperator;
}
void MainWindow::on_Equal_button_released()
{
    double secondNum = ui->label->text().toDouble();
    double result = secondNum;   // fallback

    if (mathOperator == "+")
        result = first_num + secondNum;

    else if (mathOperator == "-")
        result = first_num - secondNum;

    else if (mathOperator == "x")
        result = first_num * secondNum;

    else if (mathOperator == "÷")
    {
        if (secondNum == 0)
        {
            ui->label->setText("Error");
            return;
        }

        result = first_num / secondNum;
    }

    ui->label->setText(QString::number(result, 'g', 15));

    first_num = result;
    userIsTypingSecondNumber = false;
    mathOperator = "";
}
void MainWindow::clear_pressed()
{
    ui->label->setText("0");
    first_num = 0;
    userIsTypingSecondNumber = false;
    mathOperator = "";
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    dragPos = event->globalPos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    move(pos() + event->globalPos() - dragPos);
    dragPos = event->globalPos();
}
