#include "Board.h"
#include "ui_Board.h"
#include "ai.cpp"
#include <QPainter>
#include <QMouseEvent>
#include <windows.h>


Board::Board(QWidget *parent):
    QWidget(parent)
{/*
    button1 = new QPushButton("重新开始游戏（先手）",this);
    button1->setGeometry(850*2,200*2,250*2,100*2);
    connect(button1,SIGNAL(clicked()),this,SLOT(ClickButton()));
    button4 = new QPushButton("重新开始游戏（后手）",this);
    button4->setGeometry(850*2,325*2,250*2,100*2);
    connect(button4,SIGNAL(clicked()),this,SLOT(Start()));
    button2 = new QPushButton("悔棋(仅限撤销一步)",this);
    button2->setGeometry(850*2,450*2,250*2,100*2);
    connect(button2,SIGNAL(clicked()),this,SLOT(Back()));
    button3 = new QPushButton("AI上一步落子位置",this);
    button3->setGeometry(850*2,575*2,250*2,100*2);
    connect(button3,SIGNAL(clicked()),this,SLOT(Last()));*/
    // 高分辨率适用

    button1 = new QPushButton("重新开始游戏（先手）",this);
    button1->setGeometry(850,200,250,100);
    connect(button1,SIGNAL(clicked()),this,SLOT(ClickButton()));
    button4 = new QPushButton("重新开始游戏（后手）",this);
    button4->setGeometry(850,325,250,100);
    connect(button4,SIGNAL(clicked()),this,SLOT(Start()));
    button2 = new QPushButton("悔棋(仅限撤销一步)",this);
    button2->setGeometry(850,450,250,100);
    connect(button2,SIGNAL(clicked()),this,SLOT(Back()));
    button3 = new QPushButton("AI上一步落子位置",this);
    button3->setGeometry(850,575,250,100);
    connect(button3,SIGNAL(clicked()),this,SLOT(Last()));
}

void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int d = 2*_r;
    for(int i=1;i<=15;++i){
        painter.drawLine(QPoint(d,i*d),QPoint(15*d,i*d));
        painter.drawLine(QPoint(i*d,d),QPoint(i*d,15*d));
    }
    painter.setBrush(QBrush(QColor(175,230,230)));
    if(isThinking){
    painter.setBrush(QBrush(QColor(255,0,0)));}
    painter.drawRect(850,75,250,100);
    for(int i = 0;i<15;i++){
        for(int j=0;j<15;j++){
            if(map[i][j]){
            if(map[i][j]==1) painter.setBrush(QBrush(QColor(0,0,0)));//黑色
            if(map[i][j]==2) painter.setBrush(QBrush(QColor(255,255,255)));//白色
            if(map[i][j]==3) painter.setBrush(QBrush(QColor(131,175,155))); //某种蓝色，用于提示落子位置
            if(map[i][j]==4) painter.setBrush(QBrush(QColor(125,125,125))); //某种灰色，用于提示悔棋位置
            painter.drawEllipse(QPoint(d*i+d,d*j+d),_r,_r);
            }
        }
      }
    if(winner == human) {
    msgBox.setText("恭喜你赢了"
                  "(点击以确认)");    // 设置文本

    msgBox.exec();  // 执行
    winner = 0;
    game = 0;
    }
    if(winner == ai) {
    msgBox.setText("电脑赢了"
                  "(点击以确认)");    // 设置文本

   msgBox.exec();  // 执行
   winner = 0;
   game = 0;
   }
    }

void Board::mouseReleaseEvent(QMouseEvent *event){
    QPoint pt = event->pos();
    int row,col;
    bool bRet = getRowCol(pt,row,col);
    if(bRet == false || map[row-1][col-1])
    {return;}
    else
    {   game = 1;//人类下过了！
        map[row-1][col-1] = human;
        i = row-1;
        j = col-1;
        win((int*)map,winner,human);}
    repaint();
    if(game == 1){
    isThinking = 1;
    repaint();
    play((int*)map,x,y,ai,human); //x,y ：ai落子坐标
    map[x][y]=3;
    isThinking = 0;
    repaint();
    Sleep(144);
    map[x][y]=ai;}//渐变效果
    win((int*)map,winner,ai);
    repaint(); //原来两个update()会被压缩成一个，只能用repaint强制重绘了
}

bool Board::getRowCol(QPoint pt, int &row, int &col){
    row = (pt.x()+_r)/(2*_r);
    col = (pt.y()+_r)/(2*_r);
    if(row>15 || col >15 ||row <1 ||col <1)
        return false;
    return true;
}


void Board::ClickButton(){
    memset(map,0,225*sizeof(int));
    update();
    human = 1;
    ai = 2;
}

void Board::Back(){
    if(x<15 && x>=0 && y>=0 && y<15 && i<15 && i>=0 && j>=0 && j<15){
    map[i][j] = 4;
    map[x][y] = 4;
    repaint();
    Sleep(144);
    map[i][j] = 0;
    map[x][y] = 0;
    i=-1,j=-1,x=-1,y=-1;
    update();}
}

void Board::Last(){
    if(x<15 && x>=0 && y>=0 && y<15){
    map[x][y] = 3;
    repaint();
    Sleep(144);
    map[x][y] = ai;
    update();}
}
void Board::Start(){
    memset(map,0,sizeof(int)*225);
    x = 7;
    y = 7;
    human = 2;
    ai = 1;
    map[x][y]=ai;
    update();
  }

