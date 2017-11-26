#include "task2view.h"

Task2View::Task2View(QWidget *parent) : QMainWindow(parent)
{
    //Управление элементами формы -- размеры и текст
    this->setWindowTitle("Задача 2 — наименьшее число перемножений");
    this->resize(MainWindow::startSizes::width, MainWindow::startSizes::height);
    inputSizes = new QLineEdit(this);
    inputSizes->setPlaceholderText("Введите размеры матриц");
    inputSizes->setGeometry(40, 40, 180, 40);

    startAlg = new QPushButton("Старт/Перезапуск алгоритма", this);
    startAlg->setGeometry(40, 160, 180, 40);
    prevStep = new QPushButton("<<", this);
    prevStep->setGeometry(260, 40, 40, 40);
    nextStep = new QPushButton(">>", this);
    nextStep->setGeometry(300, 40, 40, 40);
    table = new QTableView(this);
    table->setGeometry(360, 40, 400, 400);
    logs = new QTextBrowser(this);
    logs->setGeometry(40, 200, 300, 400);
    dataLoaded = false;
    //Загрузка примеров -- вшиты в программу
    listExamples.append(QString("1 1 1 1"));
    listExamples.append(QString("10 100 5 50"));
    listExamples.append(QString("2 4 5"));
    for (size_t i = 0; i < (size_t)MainWindow::buttonCount::value; ++i)
    {
        listButtonExamples.append(new QPushButton("Пример " + QString::number(i + 1), this));
        listButtonExamples[i]->setGeometry(380 + i * 120, 440, 120, 50);
    }
    connect(listButtonExamples[0], SIGNAL(clicked(bool)), SLOT(loadExample1()));
    connect(listButtonExamples[1], SIGNAL(clicked(bool)), SLOT(loadExample2()));
    connect(listButtonExamples[2], SIGNAL(clicked(bool)), SLOT(loadExample3()));
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
    std::vector <int> vec = baseAlg->getVecSizes();
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

void Task2View::loadExample(QString example)
{
    //Загружает элементы структуры-пары в поля ввода
    //В структуре находятся 2 строки -- примеры для демонстрации
    inputSizes->setText(example);
}
//Судя по всему, архитектура фреймфорка не позволяет найти другое решение
//По крайней мере, без работы с мета-объектами Qt
//Передать параметр в connect() Qt не позволяет --
//Сигнатура сигнала и слота должна быть схожей (один возвращает -- другой принимает)
void Task2View::loadExample1() {loadExample(listExamples[0]);}
void Task2View::loadExample2() {loadExample(listExamples[1]);}
void Task2View::loadExample3() {loadExample(listExamples[2]);}

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

QString Task2View::updateLogs()
{
    //Перезапись логов для вывода в QTextBrowser
    QString res = "";
    for (auto &elem : logVector)
        res += elem;
    return res;
}

void Task2View::nextStep_clicked()
{
    //Переход на следующий шаг
    if (dataLoaded && baseAlg->hasNext())
    {
        baseAlg->next();
        loadTable();
        logVector.push_back(QString::fromUtf8(baseAlg->peek().logs_.c_str()));
        logs->setText(updateLogs());
        logs->moveCursor(QTextCursor::End);

    }
    //qDebug() << baseAlg->getCounter();
}

void Task2View::prevStep_clicked()
{
    //Переход на предыдущий шаг
    if (dataLoaded && baseAlg->hasPrev())
    {
        baseAlg->prev();
        loadTable();
        if (!logVector.empty())
            logVector.pop_back();
        logs->setText(updateLogs());
        logs->moveCursor(QTextCursor::End);
    }
    //qDebug() << baseAlg->getCounter();
}
