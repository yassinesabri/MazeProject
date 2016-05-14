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
#include <QMediaPlayer>
#include <QKeyEvent>

using namespace std;

class game : public QWidget
{
    Q_OBJECT
public:
    int x_position=0,y_position=0;
    game(int lvl=0, int avtr=0);
    void set_game(int lvl,int avtr);
    void generate_maze();
    void keyPressEvent (QKeyEvent * event);
private:
    QPushButton *exit_game;
    QPushButton *solve_game;
    QPushButton *hint_game;
    QLabel *timing;
    QLabel *maze_grid;
    Maze * maze;
    int level=0,dim=0;
    QLabel **square;
    QWidget *game_space;
    QGridLayout *game_layout;
    QPixmap *avatar,*flag,*empty;
    int **solution;
    int hint_number=0;
    int gameMute=0,effectMute=0;
    QMediaPlayer *GameSound_control,*MoveSound,*ErrorSound,*winSound;
    QPushButton *GameSound,*SoundEffect;


signals:

public slots:
    void exit_app();
    void hint_box();
    void solve();
    void GameSound_button();
    void SoundEffect_button();
    void win();


};

#endif // GAME_H
