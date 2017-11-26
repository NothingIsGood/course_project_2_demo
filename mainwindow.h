#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "task1view.h"
#include "task2view.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum buttonCount {value = 3,}; //Число кнопок с примерами
    enum startSizes {width = 800, height = 600}; //Размеры
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void action_Task1ButtonClicked();
    void action_Task2ButtonClicked();
private:
    QLabel* label;
    QPushButton* buttonTask1;
    QPushButton* buttonTask2;
};

#endif // MAINWINDOW_H
