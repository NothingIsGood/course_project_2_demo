#ifndef TASK2VIEW_H
#define TASK2VIEW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QTextBrowser>
#include <QVector>
#include <QString>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>

#include "exceptions.h"
#include "task2matrix.h"
#include "mainwindow.h"

/*
 * Интерфейс для задания 2
 * Схож с заданием 1
 * Однако наследование окон в Qt сделано очень костыльно
 * (особенно если оборачивать в шаблонный класс, так как тип задач различен)
 * Причем в нашем случае приходилось бы в любом случае переопределять большинство методов
 * Поэтому наследование окон на данный момент не реализовано
 * А нужно ли оно? -_-
 * Сигнатура методов в основном схожа с заданием 1
 * Реализация различна
 * */

class Task2View: public QMainWindow
{
    Q_OBJECT
public:
    explicit Task2View(QWidget *parent = 0);void loadTable(); //Загрузка значений в таблицу
    QString updateLogs(); //Обновление логов для демонстрации
    void loadExample(QString example); //Загрузка примера в поле ввода
private:
    QLineEdit* inputSizes; //Размеры матриц
    QPushButton* startAlg; //Старт алгоритма с начала
    QPushButton* nextStep; //Следующий шаг
    QPushButton* prevStep; //Предыдущий шаг
    QTextBrowser* logs; //Сообщения от алгоритма -- виджет для вывода логов
    QVector <QString> logVector; //Вектор строк -- логи
    QTableView* table; //Таблица для вывода матрицы
    Task2Matrix* baseAlg; //Основной алгоритм
    bool dataLoaded = false; //Введены строки -- флаг переходит в true при первой демонстрации

    QList <QString> listExamples; //Примеры входных данных
    QList <QPushButton*> listButtonExamples; //И кнопки для них

private slots:
    void startAlg_clicked();
    void nextStep_clicked();
    void prevStep_clicked();
    void loadExample1(); //Загрузка конкретного примера в поле ввода
    void loadExample2();
    void loadExample3();
};

#endif // TASK2VIEW_H
