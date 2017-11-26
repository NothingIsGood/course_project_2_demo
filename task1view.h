#ifndef TASK1VIEW_H
#define TASK1VIEW_H

#include "exceptions.h"
#include "task1lcs.h"
#include "abstractview.h"
#include <QStandardItemModel>
#include <QMessageBox>

/*
 * Интерфейс для задания 1
 * Переопределены только поля ввода и необходимые методы
 *
 * */

class Task1View : public AbstractView
{
    Q_OBJECT

public:
    explicit Task1View(QWidget *parent = 0);
    void loadTable() override; //Загрузка значений в таблицу

private:
    QLineEdit* inputStr1; //Ввод строки 1
    QLineEdit* inputStr2; //Ввод строки 2

private slots:
    void startAlg_clicked() override; //Старт алгоритма
    void loadExample_clicked() override; //Выбор решения
};

#endif // TASK1VIEW_H
