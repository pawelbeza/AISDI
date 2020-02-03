#ifndef DJIKSTRA_HPP
#define DJIKSTRA_HPP

#include <iostream>

struct node {
    int dist, x, y;
};

bool isValid(int x, int y, int maxN, int maxM);
void Djikstra(vector<string> &board);

#endif