#ifndef TASK2MATRIX_H
#define TASK2MATRIX_H
#include <vector>
#include <sstream>
#include <limits>

#include "abstracttask.h"
#include "exceptions.h"

/*
 * Задание 2 --
 * Задача о перемножении матриц
 * Находит минимальное количество операций умножения для перемножения заданных матриц
 *
 * Вывод строки с расставленными скобками -- отдельная задача динамического программирования
 *
 * Ограничение на матрицы -- количество не более 5
 * Подаются на вход в виде A B C D E F -- целые числа
 * Представляют размеры матриц вида AxB, BxC, CxD, DxE, ExF
 *
 * */


class Task2Matrix: public AbstractTask
{
public:
    enum matrix_limit {value = 6, }; //6 значений -- для указания размеров 5 матриц -- см. выше
    Task2Matrix(std::vector<int> sizes) :sizes_{sizes}
    {
        if (sizes_.size() > matrix_limit::value)
            throw InvalidArgsException();
        for (auto &elem: sizes)
        {
            if (elem <= 0)
                throw InvalidArgsException();
            fillSteps();
        }
    }
    Task2Matrix(const std::string& str) //чтение строки (понадобится для ввода через поля ввода в Qt)
    {
        std::istringstream os (str);
        std::vector <int> resVector;
        while (os.good() && !os.eof())
        {
            int tmp;
            os >> tmp;
            resVector.push_back(tmp);
        }

        *this = Task2Matrix(resVector);
    }

    void fillSteps() override;
    std::vector <int> getVecSizes() const noexcept {return sizes_;}
private:
    std::vector <int> sizes_; //Размеры матриц
};

#endif // TASK2MATRIX_H
