#include <bits/stdc++.h>
#include "Maze.h"
#include "SideWinder.h"
#include "Prim.h"
#include "growing_tree.h"

using namespace std;

int main()
{
    SideWinder SideMaze(5,5);
    SideMaze.show();
    SideMaze.show_solution();
    Prim PrimMaze(10,10);
    PrimMaze.show();
    PrimMaze.show_solution();
    growing_tree TreeMaze(10,10);
    TreeMaze.show();
    TreeMaze.show_solution();


    return 0;
}
