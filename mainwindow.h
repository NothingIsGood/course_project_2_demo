#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "task1view.h"
#include "task2view.h"
#include "task3view.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum buttonCount {value = 3,}; //Число кнопок с примерами
    enum startSizes {width = 800, height = 600}; //Размеры главного окна
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void action_Task1ButtonClicked();
    void action_Task2ButtonClicked();
    void action_Task3ButtonClicked();
private:
    QLabel* label;
    QPushButton* buttonTask1;
    QPushButton* buttonTask2;
    QPushButton* buttonTask3;
};

#endif // MAINWINDOW_H
