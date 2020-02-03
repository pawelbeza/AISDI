#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <limits.h>

#include "Djikstra.hpp"

using namespace std;

struct node {
    int dist, x, y;
};

bool isValid(int x, int y, int maxN, int maxM) {
    return (x >= 0 && y >= 0 && x < maxN && y < maxM);
}

void Djikstra(vector<string> &board) {
    const int boardSize = board.size();

    const int wiel = 100;
    int distance[wiel][wiel];
    pair<int, int> previous[wiel][wiel];
    bool path[wiel][wiel];

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            distance[i][j] = INT_MAX;
        }
    }

    priority_queue<pair<int, int>> q;
    
    q.push({0, boardSize - 1});
    distance[0][boardSize - 1] = 0;
    previous[0][boardSize - 1] = {0, boardSize - 1};

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    while (!q.empty()) {
        auto current = q.top();
        q.pop();
        int x = current.second % boardSize; // column
        int y = current.second / boardSize; // row


        if (x != 0 && y!= 0 && board[y][x] == '0')
            break;
        
        for (int i = 0; i < 4; i++) {
            int newx = x + dx[i];
            int newy = y + dy[i];
            int dist = abs(current.first);
            if (isValid(newx, newy, boardSize, boardSize) && dist + board[newy][newx] < distance[newy][newx]) {
                distance[newy][newx] = dist + board[newy][newx] - '0';
                previous[newy][newx] = {y, x};
                q.push({-distance[newy][newx], newy * boardSize + newx});
            }
        }
    }

    int newx = 0;
    int newy = boardSize - 1;
    
    while (newx != boardSize - 1 || newy != 0) {
        path[newy][newx] = 1;
        int firstVal = previous[newy][newx].first;
        int scndVal = previous[newy][newx].second;

        newx = scndVal;
        newy = firstVal;
    }
    path[newy][newx] = 1;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if(path[i][j])
                cout << board[i][j];
            else
                cout << " ";
            
        }
        cout << endl;
    }
}