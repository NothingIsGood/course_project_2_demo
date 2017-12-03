#ifndef TASK3VIEW_H
#define TASK3VIEW_H

#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>

#include "abstractview.h"
#include "exceptions.h"
#include "task3knapsack.h"

/*
 * Интерфейс для задания 2
 * Используется наследование от базового окна
 * */

class Task3View: public AbstractView
{
    Q_OBJECT
public:
    explicit Task3View(QWidget *parent = 0);
    void loadTable() override; //Загрузка значений в таблицу
    QLineEdit* inputWeights;
    QLineEdit* inputCosts;
    QLineEdit* inputMaxWeight;
private:

private slots:
    void startAlg_clicked() override;
    void loadExample_clicked() override; //Выбор решения
};

#endif // TASK3VIEW_H
