#include "task2view.h"

Task2View::Task2View(QWidget *parent) : AbstractView(parent)
{
    //Управление элементами формы -- размеры и текст
    this->setWindowTitle("Задача 2 — наименьшее число перемножений");

    inputSizes = new QLineEdit(this);
    inputSizes->setPlaceholderText("Введите размеры матриц");
    inputSizes->setGeometry(40, 40, 180, 40);

    //Сигналы и слоты
    connect(startAlg, SIGNAL(clicked(bool)), SLOT(startAlg_clicked()));
    connect(nextStep, SIGNAL(clicked(bool)), SLOT(nextStep_clicked()));
    connect(prevStep, SIGNAL(clicked(bool)), SLOT(prevStep_clicked()));
}

void Task2View::loadTable()
{
    //Управление форматом таблицы
    QStandardItemModel *model = new QStandardItemModel;
    //QStandardItem *item;
    Task2Matrix* matr = dynamic_cast<Task2Matrix*>(baseAlg);
    std::vector <int> vec = matr->getVecSizes();
    size_t width = vec.size();

    //Нужно для заголовков таблицы
    QStringList list_x;
    QStringList list_y;
    //list_x.append(QString("-"));
    for(size_t i = 0; i < width; ++i)
    {
        list_x.append(QString::number(vec[i]));
        list_y.append(QString::number(vec[i]));
    }

    model->setHorizontalHeaderLabels(list_x);
    model->setVerticalHeaderLabels(list_y);
    //Заполнение таблицы
    for(size_t i = 0; i < width; ++i)
    {
        table->setColumnWidth(i, table->width() / 6);
        for(size_t j = 0; j < width; ++j)
        {
            //qDebug() << baseAlg->getCounter();
            model->setItem(j, i, new QStandardItem(QString::number(baseAlg->peek().result_[i][j])));
        }
    }
    table->setModel(model);
}

void Task2View::startAlg_clicked()
{
    //Вызывается при начале демонстрации алгоритма
    //Здесь же -- валидация данных
    try
    {
        //Заполнение основной таблицы
        logVector.clear();
        baseAlg = new Task2Matrix(inputSizes->text().toUtf8().constData());
        dataLoaded = true;
        loadTable();
        logs->setText(updateLogs());
    }
    catch (InvalidArgsException e)
    {
        QMessageBox box;
        box.setWindowTitle(QString("Ошибка ввода"));
        box.setText( QString("Неверно введены данные -- слишком много чисел введено для матрицы"));
        box.exec();
    }
}
