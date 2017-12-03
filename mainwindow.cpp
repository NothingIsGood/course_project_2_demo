#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(startSizes::width, startSizes::height);
    this->setWindowTitle("Демонстрация");
    label = new QLabel("<p style = 'text-align: center;'><h3> Выберите задачу из предложенных ниже </h3></p>", this);
    label->setGeometry(QRect(0, 0, startSizes::width, startSizes::height / 4));
    buttonTask1 = new QPushButton("Задача 1 — поиск наибольшей общей подстроки", this);
    buttonTask1->setGeometry(QRect(startSizes::width / 4, startSizes::height / 4, startSizes::width / 2, startSizes::height - 550));
    buttonTask2 = new QPushButton("Задача 2 — поиск наименьшего числа перемножений матриц", this);
    buttonTask2->setGeometry(QRect(startSizes::width / 4, startSizes::height / 4 + 60, startSizes::width / 2, startSizes::height - 550));
    buttonTask3 = new QPushButton("Задача 3 — задача о рюкзаке", this);
    buttonTask3->setGeometry(QRect(startSizes::width / 4, startSizes::height / 4 + 120, startSizes::width / 2, startSizes::height - 550));
    label->show();
    buttonTask1->show();
    buttonTask2->show();
    buttonTask3->show();
    connect(buttonTask1, SIGNAL(clicked(bool)), SLOT(action_Task1ButtonClicked()));
    connect(buttonTask2, SIGNAL(clicked(bool)), SLOT(action_Task2ButtonClicked()));
    connect(buttonTask3, SIGNAL(clicked(bool)), SLOT(action_Task3ButtonClicked()));
}

void MainWindow::action_Task1ButtonClicked()
{
    Task1View* t1 = new Task1View();
    t1->show();
}

void MainWindow::action_Task2ButtonClicked()
{
    Task2View* t2 = new Task2View();
    t2->show();
}

void MainWindow::action_Task3ButtonClicked()
{
    Task3View* t3 = new Task3View();
    t3->show();
}

MainWindow::~MainWindow()
{
    delete label;
    delete buttonTask1;
    delete buttonTask2;
    delete buttonTask3;
}
