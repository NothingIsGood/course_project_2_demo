#ifndef TASK1VIEW_H
#define TASK1VIEW_H

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
#include "task1lcs.h"
#include "mainwindow.h"

class Task1View : public QMainWindow
{
    Q_OBJECT

public:

    explicit Task1View(QWidget *parent = 0);
    void loadTable(); //Загрузка значений в таблицу
    QString updateLogs(); //Обновление логов для демонстрации
    void loadExample(QPair <QString, QString> example); //Загрузка примера в поле ввода
private:
    QLineEdit* inputStr1; //Ввод строки 1
    QLineEdit* inputStr2; //Ввод строки 2
    QPushButton* startAlg; //Старт алгоритма с начала
    QPushButton* nextStep; //Следующий шаг
    QPushButton* prevStep; //Предыдущий шаг
    QTextBrowser* logs; //Сообщения от алгоритма -- виджет для вывода логов
    QVector <QString> logVector; //Вектор строк -- логи
    QTableView* table; //Таблица для вывода матрицы
    Task1LCS* baseAlg; //Основной алгоритм
    bool dataLoaded = false; //Введены строки -- флаг переходит в true при первой демонстрации

    QList <QPair <QString, QString>> listExamples; //Примеры входных данных
    QList <QPushButton*> listButtonExamples; //И кнопки для них

private slots:
    void startAlg_clicked();
    void nextStep_clicked();
    void prevStep_clicked();
    void loadExample1(); //Загрузка конкретного примера в поле ввода
    void loadExample2();
    void loadExample3();
};

#endif // TASK1VIEW_H
