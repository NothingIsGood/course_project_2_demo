#include "task3view.h"

Task3View::Task3View(QWidget *parent) : AbstractView(parent)
{
    //Управление элементами формы -- размеры и текст
    this->setWindowTitle("Задача 3 — задача о ранце");
    //Вспомогательные поля (поля ввода)

    //Маска и поддиректория
    fileExt = "*.task3";
    fileFolder = "/task3ex/";

    //Сигналы и слоты
    connect(startAlg, SIGNAL(clicked(bool)), SLOT(startAlg_clicked()));
    connect(nextStep, SIGNAL(clicked(bool)), SLOT(nextStep_clicked()));
    connect(prevStep, SIGNAL(clicked(bool)), SLOT(prevStep_clicked()));
    connect(confirmExample, SIGNAL(clicked(bool)), SLOT(loadExample_clicked()));

    inputWeights = new QLineEdit(this);
    inputWeights->setPlaceholderText("Введите весы предметов");
    inputWeights->setGeometry(40, 40, 160, 40);
    inputCosts = new QLineEdit(this);
    inputCosts->setPlaceholderText("Введите ст-ти предметов");
    inputCosts->setGeometry(40, 100, 160, 40);
    inputMaxWeight = new QLineEdit(this);
    inputMaxWeight->setPlaceholderText("Макс.вес");
    inputMaxWeight->setGeometry(220, 100, 100, 40);

    setFileList();
}

void Task3View::loadTable()
{
    //Управление форматом таблицы
    QStandardItemModel *model = new QStandardItemModel;
    //QStandardItem *item;
    Task3Knapsack* alg = dynamic_cast<Task3Knapsack*>(baseAlg);
    size_t width = alg->getMaxWeight(); //по ширине
    size_t height = alg->getSizeListItems(); //по высоте

    //Нужно для заголовков таблицы
    QStringList list_x;
    QStringList list_y;

    for(size_t i = 0; i < width; ++i)
    {
        list_x.append(QString::number(i + 1));
    }
    for (size_t j = 0; j <= height; ++j)
    {
        list_y.append("k = " + QString::number(j));
    }

    model->setHorizontalHeaderLabels(list_x);
    model->setVerticalHeaderLabels(list_y);

    //Заполнение таблицы
    for(size_t i = 0; i <= height; ++i)
    {
        for(size_t j = 0; j < width; ++j)
        {
            table->setColumnWidth(j, table->width() / (width + 1));
            //qDebug() << baseAlg->getCounter();
            model->setItem(i, j, new QStandardItem(QString::number(baseAlg->peek().result_[j][i])));
        }
    }
    table->setModel(model);
}

void Task3View::startAlg_clicked()
{
    //Вызывается при начале демонстрации алгоритма
    //Здесь же -- валидация данных
    try
    {
        //Заполнение основной таблицы
        logVector.clear();
        baseAlg = new Task3Knapsack(inputWeights->text().toUtf8().constData(), inputCosts->text().toUtf8().constData(), inputMaxWeight->text().toUtf8().constData());
        dataLoaded = true;
        loadTable();
        logs->setText(updateLogs());
    }
    catch (InvalidArgsException e)
    {
        QMessageBox box;
        box.setWindowTitle(QString("Ошибка ввода"));
        box.setText( QString("Данные введены неверно. Возможные проблемы -- \n <ul><li>Не совпадает число стоимостей и весов</li><li>Есть элементы не входящие в допустимый диапазон значений</li><li>Стоимостей и/или весов больше заданного количества</li></ul>"));
        box.exec();
    }
}

void Task3View::loadExample_clicked()
{
    //Загрузка примера из файла
    QString pathToFile = getExampleDirPath() + box->currentText();
    QFile file (pathToFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    inputWeights->setText(in.readLine()); //Сначала ввод весов
    inputCosts->setText(in.readLine()); //Затем стоимостей
    inputMaxWeight->setText(in.readLine()); //В конце -- макс.вес
    file.close();
}
