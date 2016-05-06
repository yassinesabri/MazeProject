#ifndef MAZE_H
#define MAZE_H
#include <bits/stdc++.h>
using namespace std;

class Maze
{
    protected:
        int height;
        int width;
        char** cell;
        enum direction{up,down,right,left,IN,FRONTR,BACKTRACK};
    public:
        int in=0x10; //16
        int front=0x20;//32
        int backt= 0x40; //64

        int** solution;
        stack<pair<int,int>> chemin;
        Maze(int,int);
        virtual ~Maze();
        void set_bit(direction,int i,int j);
        void show();
        //void test();
        void find_path(int i,int j);
        bool is_safe(int i,int j);
        void show_solution();
    private:
};

#endif // MAZE_H
