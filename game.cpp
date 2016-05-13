#include "game.h"
#include <QMessageBox>
using namespace std;

game::game(int lvl,int avtr)
{
    this->setFixedSize(810,640);
    this->setWindowIcon(QIcon(":/img/menu_icon.png"));
    this->setWindowTitle("New Game");
    level=lvl;

    //background
    QLabel *bg = new QLabel(this);
    bg->setGeometry(0,0,810,640);
    QPixmap *bgP = new QPixmap(":/img/game_bg.png");
    bg->setPixmap(*bgP);
    //initial the game square
    set_game(lvl,avtr);

    //Main Buttons
    hint_game = new QPushButton(this);
    hint_game->setGeometry(640,260,150,40);
    hint_game->setCursor(Qt::PointingHandCursor);
    hint_game->setIcon(QIcon(":/img/hint.png"));
    hint_game->setIconSize(QSize(150,40));
    hint_game->raise();
    QObject::connect(hint_game,SIGNAL(clicked(bool)),this,SLOT(hint_box()));

    solve_game = new QPushButton(this);
    solve_game->setGeometry(640,340,150,40);
    solve_game->setCursor(Qt::PointingHandCursor);
    solve_game->setIcon(QIcon(":/img/solve.png"));
    solve_game->setIconSize(QSize(150,40));
    solve_game->raise();
    QObject::connect(solve_game,SIGNAL(clicked(bool)),this,SLOT(solve()));

    exit_game = new QPushButton(this);
    exit_game->setGeometry(640,420,150,40);
    exit_game->setCursor(Qt::PointingHandCursor);
    exit_game->setIcon(QIcon(":/img/exit_new.png"));
    exit_game->setIconSize(QSize(150,40));
    exit_game->raise();
    QObject::connect(exit_game,SIGNAL(clicked(bool)),this,SLOT(exit_app()));

    QString text("TIMING");
    timing = new QLabel(text,this);
    timing->setGeometry(640,60,150,40);
    QPixmap *tim = new QPixmap(":/img/timing.png");
    timing->setPixmap(*tim);
    timing->raise();
}

void game::exit_app()
{
    int choix = QMessageBox::question(this,"Exit","You would like to go to the menu ?",QMessageBox::Yes | QMessageBox::No);
       if(choix == QMessageBox::Yes)
       {
           this->close();
           menu *m = new menu;
           m->show();
       }
       else if(choix == QMessageBox::No)
            qApp->quit();
}
void game::hint_box()
{
        QMessageBox::information(this,"Hind Box","You're in the right way (y)");
}

void game::solve()
{
    QMessageBox::critical(this,"Solve","Sorry it's under construction");
}

void game::set_game(int lvl, int avtr)
{
    switch(lvl)
    {
        case 0:{dim=10;maze = new SideWinder(dim,dim);break;}
        case 1:{dim=18;maze = new Prim(dim,dim);break;}
        case 2:{dim=25;maze = new growing_tree(dim,dim);break;}
    }

    //allocate to the cells
    square = new QLabel* [dim];
    for(int i=0;i<dim;i++)
        square[i] = new QLabel[dim];
    //we should apply layout only on the game place so we create a widget for that
    game_space = new QWidget(this);
    game_space->setGeometry(20,20,600,600);
    game_space->setStyleSheet("background-color: #e5e5e5");
    game_layout = new QGridLayout;
    game_layout->setContentsMargins(QMargins(0,0,0,0)); //layout margin
    game_layout->setSpacing(0); //space between the cells
    //add labels to the grid
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
        {
            game_layout->addWidget(&square[i][j],i,j);
            square[i][j].setFrameShape(QFrame::NoFrame);
            square[i][j].setAlignment(Qt::AlignCenter);
            //square[i][j].setStyleSheet("border: 1px solid black;");

        }
    }
    game_space->setLayout(game_layout);
    generate_maze();

    //set the avatar and the flag
    if(lvl==0 && avtr==0){
        avatar = new QPixmap(":/img/easy0.png");
        square[0][0].setPixmap(*avatar);
        flag = new QPixmap(":/img/flag0.png");
        square[dim-1][dim-1].setPixmap(*flag);
    }
    else if(lvl==1 && avtr==0){
        avatar = new QPixmap(":/img/medium0.png");
        square[0][0].setPixmap(*avatar);
        flag = new QPixmap(":/img/flag1.png");
        square[dim-1][dim-1].setPixmap(*flag);
    }
    else if(lvl==2 && avtr==0){
        avatar = new QPixmap(":/img/hard0.png");
        square[0][0].setPixmap(*avatar);
        flag = new QPixmap(":/img/flag2.png");
        square[dim-1][dim-1].setPixmap(*flag);
    }
    else if(lvl==0 && avtr==1){
        avatar = new QPixmap(":/img/easy1.png");
        square[0][0].setPixmap(*avatar);
        flag = new QPixmap(":/img/flag0.png");
        square[dim-1][dim-1].setPixmap(*flag);
    }
    else if(lvl==1 && avtr==1){
        avatar = new QPixmap(":/img/medium1.png");
        square[0][0].setPixmap(*avatar);
        flag = new QPixmap(":/img/flag1.png");
        square[dim-1][dim-1].setPixmap(*flag);
    }
    else if(lvl==2 && avtr==1){
        avatar = new QPixmap(":/img/hard1.png");
        square[0][0].setPixmap(*avatar);
        flag = new QPixmap(":/img/flag2.png");
        square[dim-1][dim-1].setPixmap(*flag);
    }
    else if(lvl==0 && avtr==2){
        avatar = new QPixmap(":/img/easy2.png");
        square[0][0].setPixmap(*avatar);
        flag = new QPixmap(":/img/flag0.png");
        square[dim-1][dim-1].setPixmap(*flag);
    }
    else if (lvl==1 && avtr==2){
        avatar = new QPixmap(":/img/medium2.png");
        square[0][0].setPixmap(*avatar);
        flag = new QPixmap(":/img/flag1.png");
        square[dim-1][dim-1].setPixmap(*flag);
    }
    else if(lvl==2 && avtr==2){
        avatar = new QPixmap(":/img/hard2.png");
        square[0][0].setPixmap(*avatar);
        flag = new QPixmap(":/img/flag2.png");
        square[dim-1][dim-1].setPixmap(*flag);
    }
}

void game::generate_maze()
{
    //check the open walls for each cell
    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
        {
            if((maze->cell[i][j]&1)==1)
                square[i][j].setStyleSheet("border-top: 1px dashed #e5e5e5;\n""border-bottom: 1px dashed black;\n""border-left: 1px dashed black;\n""border-right: 1px dashed black;\n");
            if((maze->cell[i][j]&2)==2)
                square[i][j].setStyleSheet("border-top: 1px dashed black;\n""border-bottom: 1px dashed #e5e5e5;\n""border-left: 1px dashed black;\n""border-right: 1px dashed black;\n");
            if((maze->cell[i][j]&3)==3)
                square[i][j].setStyleSheet("border-top: 1px dashed #e5e5e5;\n""border-bottom: 1px dashed #e5e5e5;\n""border-left: 1px dashed black;\n""border-right: 1px dashed black;\n");
            if((maze->cell[i][j]&4)==4)
                square[i][j].setStyleSheet("border-top: 1px dashed black;\n""border-bottom: 1px dashed black;\n""border-left: 1px dashed black;\n""border-right: 1px dashed #e5e5e5;\n");
            if((maze->cell[i][j]&5)==5)
                square[i][j].setStyleSheet("border-top: 1px dashed #e5e5e5;\n""border-bottom: 1px dashed black;\n""border-left: 1px dashed black;\n""border-right: 1px dashed #e5e5e5;\n");
            if((maze->cell[i][j]&6)==6)
                square[i][j].setStyleSheet("border-top: 1px dashed black;\n""border-bottom: 1px dashed #e5e5e5;\n""border-left: 1px dashed black;\n""border-right: 1px dashed #e5e5e5;\n");
            if((maze->cell[i][j]&7)==7)
                square[i][j].setStyleSheet("border-top: 1px dashed #e5e5e5;\n""border-bottom: 1px dashed #e5e5e5;\n""border-left: 1px dashed black;\n""border-right: 1px dashed #e5e5e5;\n");
            if((maze->cell[i][j]&8)==8)
                square[i][j].setStyleSheet("border-top: 1px dashed black;\n""border-bottom: 1px dashed black;\n""border-left: 1px dashed #e5e5e5;\n""border-right: 1px dashed black;\n");
            if((maze->cell[i][j]&9)==9)
                square[i][j].setStyleSheet("border-top: 1px dashed #e5e5e5;\n""border-bottom: 1px dashed black;\n""border-left: 1px dashed #e5e5e5;\n""border-right: 1px dashed black;\n");
            if((maze->cell[i][j]&10)==10)
                square[i][j].setStyleSheet("border-top: 1px dashed black;\n""border-bottom: 1px dashed #e5e5e5;\n""border-left: 1px dashed #e5e5e5;\n""border-right: 1px dashed black;\n");
            if((maze->cell[i][j]&11)==11)
                square[i][j].setStyleSheet("border-top: 1px dashed #e5e5e5;\n""border-bottom: 1px dashed #e5e5e5;\n""border-left: 1px dashed #e5e5e5;\n""border-right: 1px dashed black;\n");
            if((maze->cell[i][j]&12)==12)
                square[i][j].setStyleSheet("border-top: 1px dashed black;\n""border-bottom: 1px dashed black;\n""border-left: 1px dashed #e5e5e5;\n""border-right: 1px dashed #e5e5e5;\n");
            if((maze->cell[i][j]&13)==13)
                square[i][j].setStyleSheet("border-top: 1px dashed #e5e5e5;\n""border-bottom: 1px dashed black;\n""border-left: 1px dashed #e5e5e5;\n""border-right: 1px dashed #e5e5e5;\n");
            if((maze->cell[i][j]&14)==14)
                square[i][j].setStyleSheet("border-top: 1px dashed black;\n""border-bottom: 1px dashed #e5e5e5;\n""border-left: 1px dashed #e5e5e5;\n""border-right: 1px dashed #e5e5e5;\n");
            if((maze->cell[i][j]&15)==15)
                square[i][j].setStyleSheet("border: 1px dashed #e5e5e5;");
        }
    }

}
