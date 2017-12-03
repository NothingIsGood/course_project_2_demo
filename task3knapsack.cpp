#include "task3knapsack.h"
#include <QDebug>

void Task3Knapsack::fillSteps()
{
    //Вся логика алгоритма -- здесь
    allSteps_.clear();

    size_t n = weights_.size();
    std::vector<std::vector<int>> matrix (maxWeight_ + 1, std::vector<int>(n + 1, 0));

    TaskStep step;
    step.result_ = matrix;
    step.logs_ = "Начало алгоритма, инициализируем пустую матрицу";
    allSteps_.push_back(step);

    for (size_t j = 1; j <= n; ++j)
    {
        for (int w = 1; w <= maxWeight_; ++w)
        {
            std::string stepLog = "Шаг алгоритма " + std::to_string(j) + " ; " + std::to_string(w) + "\n";
            stepLog += "Вес текущего элемента равен " + std::to_string(weights_[j - 1]) + "\n";
            stepLog += "Вес рюкзака равен " + std::to_string(w) + "\n";
            if (weights_[j - 1] <= w)
            {
                stepLog += "Вес текущего элемента меньше или равен размеру рюкзака, выбираем максимум из предыдущего элемента до нового размера рюкзака\n";
                matrix[w][j] = std::max(matrix[w][j - 1], matrix[w - weights_[j - 1]][j - 1] + costs_[j - 1]);
            }
            else
            {
                matrix[w][j] = matrix[w][j - 1];
            }
            stepLog += "Новое значение элемента по столбцу и строке с номером k " + std::to_string(w + 1) + " ; " + std::to_string(j) + " равно " + std::to_string(matrix[w][j]) + "\n";
            step.logs_ = stepLog;
            step.result_ = matrix;
            allSteps_.push_back(step);
        }
    }
}
