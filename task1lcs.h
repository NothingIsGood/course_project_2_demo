#ifndef TASK1LCS_H
#define TASK1LCS_H
#include "abstracttask.h"

#include <sstream>
#include "exceptions.h"

enum maxLength
{
    //Макс.размер строки
    value = 10,
};

class Task1LCS: public AbstractTask
{
    public:
        Task1LCS(std::string s1, std::string s2): first_{s1}, second_{s2}
        {
            if (s1.size() > (size_t)maxLength::value || s2.size() > (size_t)maxLength::value || s1.empty() || s2.empty())
                throw InvalidArgsException();
            fillSteps();
        }
        virtual void fillSteps() noexcept override; //сам алгоритм
        std::string getSubStr() const noexcept;
    private:
        std::string first_; //первая строка
        std::string second_; //вторая строка

};

#endif // TASK1LCS_H
