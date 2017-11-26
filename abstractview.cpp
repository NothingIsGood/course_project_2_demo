#include "abstractview.h"

AbstractView::AbstractView(QWidget *parent) : QMainWindow(parent)
{
    this->resize(winStartSizes::width, winStartSizes::height);
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
}

QString AbstractView::updateLogs()
{
    QString res = "";
    for (auto &elem : logVector)
        res += elem;
    return res;
}

void AbstractView::nextStep_clicked()
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
}

void AbstractView::prevStep_clicked()
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
}
