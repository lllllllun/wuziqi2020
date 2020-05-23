#include "Board.h"
#include "ui_Board.h"
#include "ai.cpp"
#include <QPainter>
#include <QMouseEvent>

Board::Board(QWidget *parent):
    QWidget(parent)
{
    button1 = new QPushButton("重新开始游戏",this);
    button1->setGeometry(1700,400,500,200);
    connect(button1,SIGNAL(clicked()),this,SLOT(ClickButton()));
    button2 = new QPushButton("悔棋(仅限撤销一步)",this);
    button2->setGeometry(1700,650,500,200);
    connect(button2,SIGNAL(clicked()),this,SLOT(Back()));

}

void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int d = 100;

    for(int i=1;i<=15;++i){
        painter.drawLine(QPoint(d,i*d),QPoint(15*d,i*d));
        painter.drawLine(QPoint(i*d,d),QPoint(i*d,15*d));
    }

    for(int i = 0;i<15;i++){
        for(int j=0;j<15;j++){
            if(map[i][j]){
            if(map[i][j]==1) painter.setBrush(QBrush(QColor(0,0,0)));//黑色
            if(map[i][j]==2) painter.setBrush(QBrush(QColor(255,255,255)));//白色
            painter.drawEllipse(QPoint(d*i+d,d*j+d),_r,_r);
            }
        }
      }
    }

void Board::mouseReleaseEvent(QMouseEvent *event){
    QPoint pt = event->pos();
    int row,col;
    bool bRet = getRowCol(pt,row,col);
    i = row-1;
    j = col-1;
    if(bRet == false || map[row-1][col-1])
    {return;}
    else
    {map[row-1][col-1] = 2-(times++)%2;}
    update();
    //play();
    update();
}

bool Board::getRowCol(QPoint pt, int &row, int &col){
    row = (pt.x()+_r)/100;
    col = (pt.y()+_r)/100;
    if(row>15 || col >15 ||row <1 ||col <1)
        return false;
    return true;
}


void Board::ClickButton(){
    memset(map,0,225*sizeof(int));
    update();
}

void Board::Back(){
    map[i][j] = 0;
    times--;
    update();
}
