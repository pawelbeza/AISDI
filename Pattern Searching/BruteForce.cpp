#include <iostream>
#include <vector>

#include "BruteForce.hpp"

std::vector<int> bruteForceFind(std::string const & str, std::string const & text) {
    std::vector<int> pattern;
    for (std::string::size_type i = 0; i <= text.size() - str.size(); i++) {
        bool flag = 1;
        for (std::string::size_type j = 0; j < str.size(); j++) {
            if (text[i + j] != str[j]) {
                flag = 0;
                break;
            }
        }

        if (flag)   
            pattern.push_back(i);
    }
    return pattern;
}