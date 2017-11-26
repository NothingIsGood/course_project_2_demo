#ifndef TASK2VIEW_H
#define TASK2VIEW_H

#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>

#include "abstractview.h"
#include "exceptions.h"
#include "task2matrix.h"

/*
 * Интерфейс для задания 2
 * Используется наследование от базового окна
 * */

class Task2View: public AbstractView
{
    Q_OBJECT
public:
    explicit Task2View(QWidget *parent = 0);
    void loadTable() override; //Загрузка значений в таблицу

private:
    QLineEdit* inputSizes; //Размеры матриц

private slots:
    void startAlg_clicked() override;
};

#endif // TASK2VIEW_H
