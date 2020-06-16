#include "Board.h"
#include "ui_Board.h"
#include "ai.cpp"
#include <QPainter>
#include <QMouseEvent>
#include <windows.h>


Board::Board(QWidget *parent):
    QWidget(parent)
{
    button1 = new QPushButton("重新开始游戏",this);
    button1->setGeometry(850,200,250,100);
    connect(button1,SIGNAL(clicked()),this,SLOT(ClickButton()));
    button2 = new QPushButton("悔棋(仅限撤销一步)",this);
    button2->setGeometry(850,325,250,100);
    connect(button2,SIGNAL(clicked()),this,SLOT(Back()));
    if(winner == 2) {
    msgBox.setText("恭喜你赢了"
                  "(点击以确认)");    // 设置文本

   msgBox.exec();  // 执行
   winner = 0;
   }
   if(winner == 1) {
   msgBox.setText("电脑赢了"
                  "(点击以确认)");    // 设置文本

   msgBox.exec();  // 执行
   winner = 0;
   }
}

void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int d = 50;

    for(int i=1;i<=15;++i){
        painter.drawLine(QPoint(d,i*d),QPoint(15*d,i*d));
        painter.drawLine(QPoint(i*d,d),QPoint(i*d,15*d));
    }

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
    }

void Board::mouseReleaseEvent(QMouseEvent *event){
    QPoint pt = event->pos();
    int row,col;
    bool bRet = getRowCol(pt,row,col);
    if(bRet == false || map[row-1][col-1])
    {return;}
    else
    {   map[row-1][col-1] = 1;
        i = row-1;
        j = col-1;}//:
    repaint();
    //thinking.setText("AI正在思考中...");
    //thinking.exec();
    play((int*)map,x,y); //x,y ：ai落子坐标

    map[x][y]=3;
    repaint();
    Sleep(144);
    map[x][y]=2; //渐变效果
    repaint(); //原来两个update()会被压缩成一个，只能用repaint强制重绘了
}

bool Board::getRowCol(QPoint pt, int &row, int &col){
    row = (pt.x()+_r)/50;
    col = (pt.y()+_r)/50;
    if(row>15 || col >15 ||row <1 ||col <1)
        return false;
    return true;
}


void Board::ClickButton(){
    memset(map,0,225*sizeof(int));
    update();
}

void Board::Back(){
    map[i][j] = 4;
    map[x][y] = 4;
    repaint();
    Sleep(144);
    map[i][j] = 0;
    map[x][y] = 0;
    update();
}



