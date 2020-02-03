#include <iostream>
#include <vector>

#include "KMP.hpp"

std::vector<int> KMP(std::string const & str, std::string const & text) {
    std::vector<int> pattern;
    std::string prefSufStr = " " + str + "#" + text;
    int *prefSufTab = new int[prefSufStr.size()];
    prefSufTab[0] = -1;
    int t = -1;
    for (std::string::size_type j = 1; j < prefSufStr.size(); j++) {
        while (t >= 0 && prefSufStr[t + 1] != prefSufStr[j])
            t = prefSufTab[t];
        t++;
        prefSufTab[j] = t;
        if (t == (int) str.size())
            pattern.push_back(j - str.size() - 1 - t);
    }
    return pattern;
}