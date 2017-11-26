#include "mainwindow.h"
#include <QApplication>

/*
 * Стартовый модуль
 * Демонстрация для УДП "Динамическое программирование"
 *
 * */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
