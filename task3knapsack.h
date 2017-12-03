#ifndef TASK3KNAPSACK_H
#define TASK3KNAPSACK_H

#include <vector>
#include <sstream>
#include <limits>

#include "abstracttask.h"
#include "exceptions.h"

/*
 * Задача 3 -- задача о рюкзаке
 * Дан набор предметов в количестве n (n не больше 5)
 * Веса предметов -- n целых чисел, больших 0 и <= 10
 * Стоимости предметов -- n целых чисел, больших 0 и <= 10
 * Максимальный вес -- целое число, не большее 15
 *
 * Результат алгоритма -- целое число -- максимальная стоимость
 * А также, входящее в последовательность элементы
 * */

class Task3Knapsack: public AbstractTask
{
public:
    enum Values {maxWeightKnapsack = 15, //Макс.вес
                 maxCount = 5, //Максимальное число элементов
                 maxCost = 10, //Максимальная стоимость для одного эл-та
                 maxWeightItem = 10 //Макс.вес для одного эл-та
                };

    Task3Knapsack(std::string weightsStr, std::string costsStr, std::string numberStr)
    {
        //weightsStr -- строка значений из поля ввода -- веса
        //costsStr -- строка значений из поля ввода -- стоимости
        //numberStr -- максимальный вес
        weights_ = getValuesVector(weightsStr, Values::maxWeightItem);
        costs_ = getValuesVector(costsStr, Values::maxCost);
        maxWeight_ = std::stoi(numberStr);
        if (maxWeight_ < 0 || maxWeight_ > Values::maxWeightKnapsack || (costs_.size() != weights_.size()) || costs_.size() > Values::maxCount || weights_.size() > Values::maxCount)
            throw InvalidArgsException();
        fillSteps();

    }

    std::vector<int> getValuesVector(std::string str, int compValue)
    {
        //Вспомогательная функция, которая переводит строку -- последовательность чисел в вектор чисел
        //Параметр compValue -- максимальное значение для вводимой посл-ти чисел
        std::vector <int> result;
        std::stringstream tmpStream(str);
        while (tmpStream.good() && !tmpStream.eof())
        {
            int tmpValue;
            tmpStream >> tmpValue;
            if (tmpValue <= 0 || tmpValue > compValue)
                throw InvalidArgsException();
            else
                result.push_back(tmpValue);
        }
        return result;
    }

    void fillSteps() override; //Сам алгоритм здесь
    size_t getMaxWeight() const noexcept {return (size_t) maxWeight_;}
    size_t getSizeListItems() const noexcept {return costs_.size();}
private:
    std::vector <int> weights_; //Веса элементов
    std::vector <int> costs_;   //Стоимости элементов
    int maxWeight_;             //Максимальный вес
};

#endif // TASK3KNAPSACK_H
