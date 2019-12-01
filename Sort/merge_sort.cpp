#include <iostream>
#include <fstream>
#include <vector>
#include <sys/times.h>
#include <algorithm>
#include <iomanip>
#include <chrono>

using namespace std;


template <typename IteratorType>
void mergeSort(IteratorType first, IteratorType last){
    if(distance(first, last) > 1)
    {
        IteratorType firstvery = first;
        IteratorType pom = first + (last-first)/2;
        mergeSort(first, pom);
        mergeSort(pom, last);
        vector<typename IteratorType::value_type> vec;
        IteratorType pom2 = pom;
        while(first!=pom2 && pom!=last)
        {
            if(*first<*pom){
                vec.push_back(*first);
                ++first;
            } else{
                vec.push_back(*pom);
                ++pom;
            }
        }
        while(first!=pom2){
            vec.push_back(*first);
            ++first;
        }
        while(pom!=last){
            vec.push_back(*pom);
            ++pom;
        }
        IteratorType vecbeg = vec.begin();
        pom = firstvery;
        while(vecbeg != vec.end()){
            *pom = *vecbeg;
            ++pom;
            ++vecbeg;
        }
    }

}