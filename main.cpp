#include <iostream>
#include "Maze.h"
#include "SideWinder.h"
#include "Prim.h"
using namespace std;

int main()
{
//      SideWinder SideMaze(5,5);
//      SideMaze.show();
//      SideMaze.test();
//      SideMaze.show_solution();
        Prim PrimMaze(5,5);
        PrimMaze.show();
        PrimMaze.test();
        PrimMaze.show_solution();

    return 0;
}
