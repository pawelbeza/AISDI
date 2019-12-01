#include <iostream>
#include <algorithm>

using namespace std;

template <typename IteratorType>
void bubbleSort(IteratorType first, IteratorType last){
    IteratorType pom1;
    IteratorType pom2;
    bool change = 1;
    for(int i = 0; i < last-first && change; ++i){
        change = 0;
        pom1 = first;
        pom2 = first+1;
        while(pom2 != last-i){
            if(*pom1 > *pom2){
                swap(*pom1, *pom2);
                change = 1;
            }
            ++pom1;
            ++pom2;
        }
    }
}