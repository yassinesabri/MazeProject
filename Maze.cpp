#include "Maze.h"
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

Maze::Maze(int h,int w)
{
    srand(time(0)); //to have a perfect random activity
    height = h;
    width = w;
    cell = new char*[h];
    for(int i=0;i<h;i++)
        cell[i] = new char[w];

    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
            cell[i][j]= 0;
}
void Maze::remove_wall(direction d, int i,int j)
{

    switch(d)
    {
        case up: cell[i][j] |= 1<<0;break; //pour 1
        case down: cell[i][j] |= 1<<1;break; //pour 2
        case right: cell[i][j] |= 1<<2;break; //pour 4
        case left: cell[i][j] |= 1<<3;break; //pour 8
    }


}
void Maze::show()
{
    for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                if(!((this->cell[i][j]&8)==8)) //8=L
                    cout<<"|";
                else cout<<" ";

                if ((!((this->cell[i][j]&2)==2))&&(!((this->cell[i][j]&1)==1))) cout<<"="; //2=D 1=U
                else if(!((this->cell[i][j]&1)==1))
                    cout<<"-";
                else if(!((this->cell[i][j]&2)==2))
                    cout<<"_";
                else
                    cout << " ";

                if(!((this->cell[i][j]&4)==4)) //4=R
                    cout<<"|";
                else cout<<" ";
            }
            cout<<endl;
        }
}
//void Maze::test()
//{
//    remove_wall(down,0,0);
//    remove_wall(right,0,0);
//    remove_wall(right,0,1);
//    remove_wall(left,0,1);
//    remove_wall(left,0,2);
//    remove_wall(up,1,0);
//    remove_wall(down,1,0);
//    remove_wall(right,1,0);
//    remove_wall(up,1,1);
//    remove_wall(down,1,1);
//    remove_wall(right,1,1);
//    remove_wall(up,1,2);
//    remove_wall(down,1,2);
//    remove_wall(left,1,2);
//    remove_wall(up,2,0);
//    remove_wall(right,2,0);
//    remove_wall(up,2,1);
//    remove_wall(left,2,1);
//    remove_wall(up,2,2);
//    remove_wall(left,2,2);
//        //Show cell's value
//        for(int i=0; i<height; i++)
//        {
//            for(int j=0; j<width; j++)
//            {
//                //cout << cell[i][j];
//                bitset<8> y(cell[i][j]);
//                printf("%d ",y);
//            }
//            cout<<endl;
//        }
//
//
//
//}
Maze::~Maze()
{
    delete [] cell;
}
