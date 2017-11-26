#include "task1lcs.h"

void Task1LCS::fillSteps() noexcept //сам алгоритм
{
    allSteps_.clear();
    std::vector <std::vector <int>> a(first_.length() + 1);
    for (auto &elem: a)
        elem.resize(second_.length() + 1);

    size_t u = 0, v = 0;
    size_t len1 = first_.length();
    size_t len2 = second_.length();
    TaskStep step;
    step.result_ = a;
    allSteps_.push_back(step);
    //первый шаг -- шаги пустые

    for (size_t i = 0; i < len1; ++i)
    {
        for (size_t j = 0; j < len2; ++j)
        {
            std::ostringstream os;
            os << "Шаг -- " << i << "; " << j << " -- Берем заданные символы из горизонтальной и вертикальной строки == " << first_[i] << " и " << second_[j] << std::endl;
            if (first_[i] == second_[j])
            {
                os << "str1[" << i << "] == str2[" << j << "] => " << first_[i] << " == " << second_[j] << " , делаем инкремент по диагонали (matrix[" << i+1 << "][" << j+1<< "])\n";
                a[i + 1][j + 1] = a[i][j] + 1;
                if (a[i + 1][j + 1] > a[u][v])
                {
                    os << "Найденная подстрока больше максимальной найденной на прошлых шагах" << std::endl;
                    u = i + 1;
                    v = j + 1;
                    os << "Новое значение u и v -- " << u << " и " << v << std::endl;
                    os << "А подстрока в нашем случае равна -- " << first_.substr(u - a[u][v], a[u][v]) << std::endl;
                }
            }
            //Запись результатов в вектор структур
            step.logs_ = os.str();
            step.result_ = a;
            allSteps_.push_back(step);
        }
    }
    allSteps_.back().logs_ += "\n Алгоритм завершил работу. Искомый результат -- " + first_.substr(u - a[u][v], a[u][v]);
    //return s1.substr(u - a[u][v], a[u][v]);
}

