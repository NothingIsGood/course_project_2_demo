#include "task2matrix.h"

void Task2Matrix::fillSteps()
{
    //Вся логика алгоритма -- здесь
    //Как и в первой задаче, упаковывается в вектор структур -- матрица и логи для неё
    allSteps_.clear();
    int maxInt = std::numeric_limits<int>().max();
    int length = sizes_.size() - 1;

    std::vector <std::vector <int>> matrix(length + 1);
    for (auto &elem: matrix)
        elem.resize(length + 1);

    for (int i = 1; i <= length; i++)
    {
        matrix[i][i] = 0;
    }
    TaskStep tmpStep;
    tmpStep.result_ = matrix;
    tmpStep.logs_ = "Начало алгоритма, переменные l и j -- счетчики цикла\n";
    allSteps_.push_back(tmpStep);
    for (int l = 2; l <= length; l++)
    {
        for (int i = 1; i <= length - l + 1; i++)
        {
            std::ostringstream os;
            os << "Шаг алгоритма -- " << l << ", " << i << '\n';
            int j = i + l - 1;
            os << "Присвоили j значение " << j << '\n';
            matrix[i][j] = maxInt;
            os << "Проходим от k = " << i << " до " << j - 1 << "в поисках минимально возможного числа перемножений" << '\n';
            for (int k = i; k <= j - 1; k++)
            {
                matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k + 1][j] + sizes_[i - 1] * sizes_[k] * sizes_[j]);
            }
            //Запись промежуточных
            TaskStep tmp;
            tmp.result_ = matrix;
            os << "Итерация пройдена \n Текущий результат -- " << (matrix[1][length]) << '\n';
            tmp.logs_ = os.str();

            allSteps_.push_back(tmp);
        }
    }

}
