#ifndef ABSTRACTTASK_H
#define ABSTRACTTASK_H

#include <vector>
#include <string>

struct TaskStep
{
    std::string logs_ = ""; //список добавленных сообщений для каждого шага (не все сообщения -- а только для этого шага)
    std::vector <std::vector<int>> result_; //список результирующей матрицы для каждого шага
    //Прочая дополнительная информация передаётся в логах!
};

class AbstractTask
{
public:
    virtual void fillSteps() = 0; //получаем шаги алгоритма -- вектор структур (различны для каждого задания)
    bool hasPrev() const noexcept {return stepCounter_ > 0;} //Есть ещё предыдущие шаги
    void next() noexcept {if (hasNext()) ++stepCounter_;} //переход на следующий шаг
    void prev() noexcept {if (hasPrev()) --stepCounter_;} //переход на предыдущий шаг
    int getCounter() const noexcept {return stepCounter_;}
    bool hasNext() const noexcept {return stepCounter_ < (int) allSteps_.size() - 1;} //Есть ещё следующие шаги
    TaskStep peek() const noexcept {return allSteps_[stepCounter_];}
protected:
    std::vector <TaskStep> allSteps_; //Все шаги работы алгоритма
    int stepCounter_ = 0;

};

#endif // ABSTRACTTASK_H
