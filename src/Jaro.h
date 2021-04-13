#ifndef JARO_H
#define JARO_H
#include <iostream>

namespace jro 
{
    double Distance(const std::string& st1, const std::string& st2)
    {
        double t = 0.0;

        if (st1.length() == 0) return (st2.length() == 0) ? 1.0 : 0.0;

        bool* matchst1 = new bool[st1.length()]{ 0 };
        bool* matchst2 = new bool[st2.length()]{ 0 };

        int distance = std::max(st1.length(), st2.length()) / 2 - 1;
        int match = 0;

        for (int i = 0; i < (int)st1.length(); ++i)
        {
            const int end = std::min(i + distance + 1, (int)st2.length());
            for (int j = std::max(0, i - distance); j < end; j++)
            {
                if (!matchst2[j] && st1[i] == st2[j])
                {
                    matchst1[i] = true;
                    matchst2[j] = true;
                    match++;
                    break;
                }
            }
        }

        // if there's no match
        if (match == 0) return 0.0;

        int point = 0;

        for (int k = 0; k < (int)st1.length(); k++)
            if (matchst1[k])
            {
                while (!matchst2[point]) point++;

                if (st1[k] != st2[point]) t += 0.5;
                point++;
            }

        const float m = static_cast<float>(match);

        delete[] matchst1;
        delete[] matchst2;

        return (m / st1.length() + m / st2.length() + (m - t) / m) / 3.0;
    }

    double WinklerDistance(const std::string& st1, const std::string& st2)
    {
        float jaro = Distance(st1, st2);
        int commonPrefix = 0;
        const int maxCommonPrefix = 4;
        const float p = 0.1;
        const float limit = 0.7;

        // to define a treshold how similar is the two strings
        if (jaro > limit)
        {
            int minCondition = std::min(std::min((int)st1.length(),(int)st2.length()), maxCommonPrefix);
            for (int i = 0; i < minCondition; i++)
            {
                if (st1[i] == st2[i])
                {
                    ++commonPrefix;
                }
            }
            jaro += p * commonPrefix * (1.0 - jaro);
        }

        return jaro;
    }
}


#endif