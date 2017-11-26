#include "task1view.h"

Task1View::Task1View(QWidget *parent) : QMainWindow(parent)
{
    //Управление элементами формы -- размеры и текст
    this->setWindowTitle("Задача 1 — наибольшая общая подстрока");
    this->resize(MainWindow::startSizes::width, MainWindow::startSizes::height);
    inputStr1 = new QLineEdit(this);
    inputStr1->setPlaceholderText("Введите первую строку");
    inputStr1->setGeometry(40, 40, 180, 40);
    inputStr2 = new QLineEdit(this);
    inputStr2->setPlaceholderText("Введите вторую строку");
    inputStr2->setGeometry(40, 100, 180, 40);
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
    listExamples.append(QPair<QString, QString> ("Hello", "Hello"));
    listExamples.append(QPair<QString, QString> ("for", "foreach"));
    listExamples.append(QPair<QString, QString> ("program", "bin"));
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

void Task1View::loadTable()
{
    //Управление форматом таблицы
    QStandardItemModel *model = new QStandardItemModel;
    //QStandardItem *item;
    QString str1 = inputStr1->text();
    QString str2 = inputStr2->text();
    size_t width = str1.size();
    size_t height = str2.size();

    //Нужно для заголовков таблицы
    QStringList list_x;
    QStringList list_y;
    list_x.append(QString("-"));
    for(size_t i = 0; i < width; ++i)
    {
        list_x.append(QString(str1[i]));
    }

    list_y.append(QString("-"));
    for(size_t i = 0; i < height; ++i)
    {
        list_y.append(QString(str2[i]));
    }
    model->setHorizontalHeaderLabels(list_x);
    model->setVerticalHeaderLabels(list_y);
    //Заполнение таблицы
    for(size_t i = 0; i < width + 1; ++i)
    {
        table->setColumnWidth(i, table->width() / 11);
        for(size_t j = 0; j < height + 1; ++j)
        {
            //qDebug() << baseAlg->getCounter();
            model->setItem(j, i, new QStandardItem(QString::number(baseAlg->peek().result_[i][j])));
        }
    }
    table->setModel(model);
}

void Task1View::loadExample(QPair <QString, QString> example)
{
    //Загружает элементы структуры-пары в поля ввода
    //В структуре находятся 2 строки -- примеры для демонстрации
    inputStr1->setText(example.first);
    inputStr2->setText(example.second);
}
//Судя по всему, архитектура фреймфорка не позволяет найти другое решение
//По крайней мере, без работы с мета-объектами Qt
//Передать параметр в connect() Qt не позволяет --
//Сигнатура сигнала и слота должна быть схожей (один возвращает -- другой принимает)
void Task1View::loadExample1() {loadExample(listExamples[0]);}
void Task1View::loadExample2() {loadExample(listExamples[1]);}
void Task1View::loadExample3() {loadExample(listExamples[2]);}

void Task1View::startAlg_clicked()
{
    //Вызывается при начале демонстрации алгоритма
    //Здесь же -- валидация данных
    try
    {
        //Заполнение основной таблицы
        logVector.clear();
        baseAlg = new Task1LCS(inputStr1->text().toUtf8().constData(), inputStr2->text().toUtf8().constData());
        dataLoaded = true;
        loadTable();
        logs->setText(updateLogs());
    }
    catch (InvalidArgsException e)
    {
        QMessageBox box;
        box.setWindowTitle(QString("Ошибка ввода"));
        box.setText( QString("Неверно введены данные -- одна из строк пуста или больше 10 символов"));
        box.exec();
    }
}



QString Task1View::updateLogs()
{
    //Перезапись логов для вывода в QTextBrowser
    QString res = "";
    for (auto &elem : logVector)
        res += elem;
    return res;
}

void Task1View::nextStep_clicked()
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

void Task1View::prevStep_clicked()
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
