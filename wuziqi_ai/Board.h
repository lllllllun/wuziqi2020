#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QtGui/QTextLine>


QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

class Board : public QWidget

{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);


    int _r=25;//棋子半径

    bool getRowCol(QPoint pt,int& row,int &col);

    void paintEvent(QPaintEvent *);

    void mouseReleaseEvent(QMouseEvent *event);


    QPushButton* button0;
    QPushButton* button1;
    QPushButton* button2;
    QPushButton* button3;
    QPushButton* button4;

    QMessageBox msgBox;   // 对局提示



    int map[15][15]={0};  //棋子数组，棋盘和棋子数组是转置矩阵
    int times = 1;
    int i,j;//上次下棋的位置
    int x,y;//ai落子位置
    int winner = 0; //表示赢家是谁
    int game = 0; //表示游戏是否开始
    int human = 1;
    int ai = 2;  //表示该下什么颜色的棋,1表示白棋，2表示黑棋
    int isThinking = 0; //1表示AI在计算
signals:

private slots:
     void ClickButton();
     void Back();
     void Last();
     void Start();

};
#endif // BOARD_H
