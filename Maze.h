#ifndef MAZE_H
#define MAZE_H


class Maze
{
    protected:
        int height;
        int width;
        char** cell;
        enum direction{up,down,right,left,IN,FRONTR};
    public:
        int** solution;
        Maze(int,int);
        virtual ~Maze();
        void remove_wall(direction,int i,int j);
        void show();
        void test();
        bool find_path(int i,int j,direction d);
        bool is_safe(int i,int j,direction d);
        void show_solution();
    private:
};

#endif // MAZE_H
