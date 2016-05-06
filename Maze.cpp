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

    solution = new int*[h];
    for(int i=0;i<h;i++)
        solution[i] = new int[w];

    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
            {cell[i][j]= 0;solution[i][j]=0;}
}
void Maze::remove_wall(direction d, int i,int j)
{

    switch(d)
    {
        case up: cell[i][j] |= 1<<0;break; //pour 1
        case down: cell[i][j] |= 1<<1;break; //pour 2
        case right: cell[i][j] |= 1<<2;break; //pour 4
        case left: cell[i][j] |= 1<<3;break; //pour 8
        case IN: cell[i][j] |= 1<<4;break; //16
        case FRONTR: cell[i][j] |= 1<<5;break; //32
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
bool Maze::is_safe(int i,int j,direction d)
{
    if(i==0 && j==0)
        return true; //marque la cellule 0,0 dans le chemin sans condition
    if(i>=0 && j>=0 && i<height && j<width)
    {
        if(d==down && cell[i][j]&1) //we check if going down to cell[i][j] is legal by checking if it has the up wall or not
            return true;
        if(d==right && cell[i][j]&8)
            return true;
        if(d==up && cell[i][j]&2)
            return true;
        if(d==left && cell[i-1][j]&4)
            return true;
    }
    return false;
}
//Backtracking
bool Maze::find_path(int i,int j,direction d)
{
    if(i==height-1 && j==width-1)
    {
        if(is_safe(i,j,d))
        {
            solution[i][j]=1;
            return true;
        }

        return false;
    }
    if(is_safe(i,j,d))
    {
        //marquer la cellule dans le chemin
        solution[i][j]=1;

        if(d!=left && find_path(i,j+1,right)) //check right
            return true;
        if(d!=up && find_path(i+1,j,down)) //check down
            return true;
        if(d!=down && find_path(i-1,j,up)) //check up
          return true;
        if(d!=right && find_path(i,j-1,left)) //check left
          return true;

        solution[i][j]=0; //demarquer la cellule car le chemin est bloqué
        return false;
    }
    return false;
}
void Maze::test()
{
        cout<<endl;
        //Show cell's value
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                //cout << cell[i][j];
                bitset<8> y(cell[i][j]);
                printf("%d ",y);
            }
            cout<<endl;
        }



}
void Maze::show_solution()
{
    find_path(0,0,right);
    cout <<endl;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(solution[i][j] == 1)
                cout <<"# ";
            else
                cout<<"- ";
        }
        cout <<endl;
    }

}
Maze::~Maze()
{
    delete [] cell;
}
