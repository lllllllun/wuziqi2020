#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

class Board : public QWidget

{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0);


    int _r=50;//棋子半径

    bool getRowCol(QPoint pt,int& row,int &col);

    void paintEvent(QPaintEvent *);

    void mouseReleaseEvent(QMouseEvent *event);



    QPushButton* button1;
    QPushButton* button2;


    int map[15][15]={0};  //棋子数组
    int times = 1;
    int i,j;//上次下棋的位置
signals:

private slots:
     void ClickButton();
     void Back();
};
#endif // BOARD_H
