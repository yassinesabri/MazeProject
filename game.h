#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QObject>
#include <QWidget>
#include "prim.h"
#include "growing_tree.h"
#include "sidewinder.h"
#include "bits/stdc++.h"
#include <QPushButton>
#include <QLabel>
#include "menu.h"
#include <QLayout>
#include <QGridLayout>

using namespace std;

class game : public QWidget
{
    Q_OBJECT
public:
    game(int lvl=0, int avtr=0);
    void set_game(int lvl,int avtr);
    void generate_maze();
private:
    QPushButton *exit_game;
    QPushButton *solve_game;
    QPushButton *hint_game;
    QLabel *timing;
    QLabel *maze_grid;
    Maze * maze;
    int level=0,dim=0;
    int x_position=0,y_position=0;
    QLabel **square;
    QWidget *game_space;
    QGridLayout *game_layout;
    QPixmap *avatar,*flag;


signals:

public slots:
    void exit_app();
    void hint_box();
    void solve();


};

#endif // GAME_H
