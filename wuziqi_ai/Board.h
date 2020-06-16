#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>


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



    QPushButton* button1;
    QPushButton* button2;


    QMessageBox msgBox;   // 对局提示
    QMessageBox thinking;



    int map[15][15]={0};  //棋子数组，棋盘和棋子数组是转置矩阵
    int times = 1;
    int i,j;//上次下棋的位置
    int x,y;//ai落子位置
    int winner = 0; //1表示人赢，2表示ai赢，否则为0；
signals:

private slots:
     void ClickButton();
     void Back();

};
#endif // BOARD_H
