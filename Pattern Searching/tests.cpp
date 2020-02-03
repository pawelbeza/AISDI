#include <iostream>
#include <vector>

#include "BruteForce.hpp"
#include "KMP.hpp"
#include "RabinKarp.hpp"

char randomChar () { return 'a' + rand () % 2; }

std::string generateString(int length) {
    std::string s = "";
    for (int i = 0; i < length; i++)
        s.push_back(randomChar());
    return s;
}

 int main() {
    srand (time (0));
    std::string pattern, text;
    for (int i = 0; i< 100; i++) {
        int n = rand() % 10 + 10;
        int patt = rand() % 10 + 1;

        std::string text = generateString(n);
        std::string pattern = generateString(patt);
        std::cout << text << " " << pattern << std::endl; 

        std::vector<int> v1 = KARP(pattern, text);
        std::vector<int> v2 = bruteForceFind(pattern, text);

        bool flag = (v1.size() == v2.size());
        for (int j = 0; j < v1.size() && flag; j++)
            if (v1[j] != v2[j]) {
                flag = 0;
                std::cout << v1[j] << " " << v2[j] << std::endl;
                break;
            }
        
        if (flag)   std::cout << "OK" << std::endl;
        else
        {
            std::cout << "WA for input: " << std::endl;
            for (auto x : v1)
                std::cout << x << " ";
            std::cout << std::endl;
            for (auto x : v2)
                std::cout << x << " ";
        }
        
    }
     
 }
