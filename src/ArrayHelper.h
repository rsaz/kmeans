#ifndef ARRAY_HELPER_H
#define EXCEPTION_HELPER_H
#include <iostream>
#include <vector>

class RectangularVectors
{
public:
    static std::vector<std::vector<double>> RectangularDoubleVector(int size1, int size2)
    {
        std::vector<std::vector<double>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<double>(size2);
        }

        return newVector;
    }

    static std::vector<std::vector<std::string>> RectangularStdWstringVector(int size1, int size2)
    {
        std::vector<std::vector<std::string>> newVector(size1);
        for (int vector1 = 0; vector1 < size1; vector1++)
        {
            newVector[vector1] = std::vector<std::string>(size2);
        }

        return newVector;
    }
};

#endif