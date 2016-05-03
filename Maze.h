#ifndef MAZE_H
#define MAZE_H


class Maze
{
    protected:
        int height;
        int width;
        char** cell;
        enum direction{up,down,right,left};
    public:
        Maze(int,int);
        virtual ~Maze();
        void remove_wall(direction,int i,int j);
        void show();
        void test();
    private:
};

#endif // MAZE_H
