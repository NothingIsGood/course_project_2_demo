#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QMainWindow>
#include <QObject>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <QComboBox>
#include <QFile>
#include <QCoreApplication>
#include <QDirIterator>
#include <QDebug>

#include "abstracttask.h"

/*
 * Абстрактная сущность для представления окон в демонстрации
 * В производных классах достаточно будет определить событие старта алгоритма (создание объекта заданного класса)
 * А также метод загрузки таблицы loadTable()
 * И обработчик для выбора примера (там же ввод из файла - примера)
 * */

enum winStartSizes {width = 800, height = 600}; //Размеры для дочерних окон

class AbstractView : public QMainWindow
{
    Q_OBJECT
public:
    explicit AbstractView(QWidget *parent = 0);
    virtual void loadTable() = 0; //Загрузка значений в таблицу
    QString updateLogs(); //Обновление логов для демонстрации
protected:
    void setFileList(); //Устанавливает список файлов по заданной директории
    QString getExampleDirPath() const noexcept {return QCoreApplication::applicationDirPath() + fileFolder;}
    QPushButton* startAlg; //Старт алгоритма с начала
    QPushButton* nextStep; //Следующий шаг
    QPushButton* prevStep; //Предыдущий шаг
    QTextBrowser* logs; //Сообщения от алгоритма -- виджет для вывода логов
    QVector <QString> logVector; //Вектор строк -- логи
    QTableView* table; //Таблица для вывода матрицы
    AbstractTask* baseAlg; //Основной алгоритм
    bool dataLoaded = false; //Введены данные -- флаг переходит в true при первой демонстрации
    //для работы с файлами-примерами -- список, расширение, папка, кнопка подтверждения
    QComboBox* box; //Список файлов
    QPushButton* confirmExample; //Кнопка для выбора примера
    QString fileExt = ""; //Маска типа ".fileextension"
    QString fileFolder = ""; //Поддиректория (для каждого задания своя)

private slots:
    virtual void startAlg_clicked() = 0; //Различные типы объектов
    void nextStep_clicked();
    void prevStep_clicked();
    virtual void loadExample_clicked() = 0;
};

#endif // ABSTRACTVIEW_H
