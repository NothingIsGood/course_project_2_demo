#include "task1view.h"

Task1View::Task1View(QWidget *parent) : AbstractView(parent)
{
    //Управление элементами формы -- размеры и текст
    this->setWindowTitle("Задача 1 — наибольшая общая подстрока");
    //Маска и поддиректория
    fileExt = "*.task1";
    fileFolder = "/task1ex/";
    //Вспомогательные поля (поля ввода)
    inputStr1 = new QLineEdit(this);
    inputStr1->setPlaceholderText("Введите первую строку");
    inputStr1->setGeometry(40, 40, 180, 40);
    inputStr2 = new QLineEdit(this);
    inputStr2->setPlaceholderText("Введите вторую строку");
    inputStr2->setGeometry(40, 100, 180, 40);

    //Сигналы и слоты
    connect(startAlg, SIGNAL(clicked(bool)), SLOT(startAlg_clicked()));
    connect(nextStep, SIGNAL(clicked(bool)), SLOT(nextStep_clicked()));
    connect(prevStep, SIGNAL(clicked(bool)), SLOT(prevStep_clicked()));
    connect(confirmExample, SIGNAL(clicked(bool)), SLOT(loadExample_clicked()));

    setFileList();
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

void Task1View::loadExample_clicked()
{
    //Загрузка примера
    QString pathToFile = getExampleDirPath() + box->currentText();
    QFile file (pathToFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    inputStr1->setText(in.readLine());
    inputStr2->setText(in.readLine());
    file.close();
}

