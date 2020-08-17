#include <stdio.h>
#include <string.h>
#include <cmath>

#define DEPTH 4
#define win_score 1000000000
#define max(a,b) ((a) > (b) ? (a) : (b))
#define f(x,y,i,j) if((x)+(i)>=0 && (x)+(i) <=14 && (y)+(j)>=0 && (y)+(j)<=14 && map[15*((x)+(i))+(y)+(j)]){return 1;}

int value[225];
int X[225];
int Y[225];
int rank[225];
int Ai,Human;

void Qsort(int *a,int *b,int low ,int high);
int evaluate(int* map,int me,int you);
int gen(int*map,int x,int y);
int sWin(int* map,int me);
void win(int* map,int& winner,int me);
int point(int* map,int me,int you,int x,int y);
int evaluate_point(int* map,int me,int you);
void minmax(int* map,int depth,int& alpha,int& beta,int&x,int&y);


void Qsort(int *a,int *b,int low ,int high) // a：待排序列，b： 待排序列元素对应序号
{
    if(low>=high)
        return ;
    int first = low ;
    int last  = high ;
    int key   = a[low] ;
    int key1  = b[low] ;
    while(first<last)
    {
        while(first<last && a[last]<=key)
            --last ;
        a[first] = a[last] ;
        b[first] = b[last] ;
        while(first<last && a[first]>=key)
            ++first ;
        a[last] = a[first] ;
        b[last] = b[first] ;
    }
    a[first] = key ;
    b[first] = key1;
    Qsort(a,b,low,first-1) ;
    Qsort(a,b,first+1,high);
}

int evaluate(int* map,int me,int you){  //感觉活一重复计分在前期是个大坑
    int score = 0;
    int flag = 0; //两端开合状态
    int con = 0;  //连子数
   for(int i=0 ;i<=14;i++) {  //行计分
        for (int j = 0; j <= 14; j++) {
            if(!map[15*i+j]) {
                if (con > 0) {
                    flag++;
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }   //遇到没子的地方，结算分数，开合状态=1
                flag = 1;
                con = 0;
            }else if(map[15*i+j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 0;
                con = 0; //遇到对面的子，结算分数，开合状态=0
            }else if(map[15*i+j] == me){
                con++;
            }
            if ( j == 14 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=win_score;
                flag = 0;
                con = 0; //遇到自己的子，连子数+1，如果到该行结尾，直接结算分数
            }
        }
    }
    for(int j=0 ;j<=14;j++) {  //列计分
        for (int i = 0; i <= 14; i++) {
            if(!map[15*i+j]) {
                if (con > 0) {
                    flag++;
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 1;
                con = 0;
            }else if(map[15*i+j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 0;
                con = 0;
            }else if(map[15*i+j] == me){
                con++;

            }
            if ( i == 14 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=win_score;
                flag = 0;
                con = 0;
            }
        }
    }
   for(int i=1 ;i<=14;i++) {//主对角线左侧计分
        for (int j = 0; j <= 14; j++) {
            if(!map[15*(i+j)+j]) {
                if (con > 0) {
                    flag++;
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 1;
                con = 0;
            }else if(map[15*(i+j)+j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 0;
                con  = 0;
            }else if(map[15*(i+j)+j] == me){
                con++;
            }
            if ( i+j == 14 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=win_score;
                flag = 0;
                con  = 0;
                break;
            }
        }
    }
    for(int i=0 ;i<=14;i++) {//主对角线上侧计分
        for (int j = 0; j <= 14; j++) {
            if(!map[15*j+i+j]) {
                if (con > 0) {
                    flag++;
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 1;
                con = 0;
            }else if(map[15*j+i+j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 0;
                con = 0;
            }else if(map[15*j+i+j] == me){
                con++;

            }
            if ( i+j == 14 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=win_score;
                flag = 0;
                con = 0;
                break;
            }
        }
    }
   for(int i=0 ;i<=14;i++) {//副对角线上侧计分
        for (int j = 0; j <= 14; j++) {
            if(i-j<0) {
                break;}
            if(!map[15*j+i-j]) {
                if (con > 0) {
                    flag++;
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 1;
                con = 0;
            }else if(map[15*j+i-j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 0;
                con = 0;
            }else if(map[15*j+i-j] == me){
                con++;

            }
            if ( i-j == 0 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=win_score;
                flag = 0;
                con = 0;
            }
        }
    }
    for(int i=1 ;i<=14;i++) {//副对角线右侧计分
        for (int j = 0; j <= 14; j++) {
            if(i+j>14) {
                break;}
            if(!map[15*(i+j)+14-j]) {
                if (con > 0) {
                    flag++;
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 1;
                con = 0;
            }else if(map[15*(i+j)+14-j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=win_score;
                }
                flag = 0;
                con = 0;
            }else if(map[15*(i+j)+14-j] == me){
                con++;

            }
            if ( i+j == 14 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=win_score;
                flag = 0;
                con = 0;
            }
        }
    }
    return score;
}

int Score(int* map){
    return evaluate(map,Ai,Human)-evaluate(map,Human,Ai);
}

void win(int* map,int& winner,int me){
    if(sWin(map,me)){
        winner = me;
    }
  //获取对局中胜负状态
}


int sWin(int* map,int me){  //单纯判断搜索过程中赢没赢
    int con = 0;  //连子数
    for(int i=0 ;i<=14;i++) {  //行计分
        for (int j = 0; j <= 14; j++) {
            if(map[15*i+j]==me){
                con++;
                if(con==5){
                    return 1;
                }
            }else{
                con = 0;
            }
        }
        con=0;
    }
    for(int j=0 ;j<=14;j++) {  //列计分
        for (int i = 0; i <= 14; i++) {
            if(map[15*i+j]==me){
                con++;
                if(con==5){
                    return 1;
                }
            }else{
                con = 0;
            }
        }
        con=0;
    }
    for(int i=1 ;i<=14;i++) {//主对角线左侧计分
        for (int j = 0; j <= 14; j++) {
                if(map[15*(i+j)+j]==me){
                    con++;
                    if(con==5){
                        return 1;
                    }
                }else{
                    con = 0;
                }
                if ( i+j == 14 ){
                    con  = 0;
                    break;}
        }}
    for(int i=0 ;i<=14;i++) {//主对角线上侧计分
        for (int j = 0; j <= 14; j++) {
            if(map[15*j+i+j]==me){
                con++;
                if(con==5){
                    return 1;
                }
            }else{
                con = 0;
            }
                if ( i+j == 14 ){
                    con = 0;
                    break;
                }
        }
    }
    for(int i=0 ;i<=14;i++) {//副对角线上侧计分
        for (int j = 0; j <= 14; j++) {
            if(map[15*j+i-j]==me){
                con++;
                if(con==5){
                    return 1;
                }
            }else{
                con = 0;
            }
            if ( i-j == 0 ){
                con = 0;
                break;
            }
        }
    }
    for(int i=1 ;i<=14;i++) {//副对角线右侧计分
        for (int j = 0; j <= 14; j++) {
            if(map[15*(i+j)+14-j]==me){
                con++;
                if(con==5){
                    return 1;
                }
            }else{
                con = 0;
            }
                if ( i+j == 14 ){
                    con = 0;
                    break;
                }
            }
        }
    return 0;
}

int gen(int*map,int x,int y){ //判断向某个方向，两格内是否有邻居
    for(int i=-2;i<=2;i++){
        f(x,y,0,i);
        f(x,y,i,0);
        f(x,y,i,i);
        f(x,y,i,-i);
    }
    return 0;
}

void minmax(int* map,int depth,int& alpha,int& beta,int&x,int&y) {
    int alpha1,beta1;//李代桃僵，把α和β传递给下一级
    if (depth == 0) {
        alpha = Score(map);
    } else {
        if( !(depth%2)){//偶数层
           for (int i = 0; i < 15; ++i) {
                for (int j = 0; j < 15; ++j) {
                    int t =rank[15*i+j];
                    int u = X[t];
                    int v = Y[t];
                    if (gen(map,u,v) && !map[15*u+v]) {
                       int Map[15][15];
                       memmove(Map, map, sizeof(int) * 225);
                       Map[u][v] =  Ai;
                       if(!sWin((int*)Map,Ai)){ //没赢，正常执行
                       alpha1 = alpha;
                       beta1 = beta;
                       minmax((int*)Map,depth-1,alpha1,beta1,x,y);
                       if( alpha < beta1 ){
                           alpha = beta1;
                           if(depth == DEPTH){
                           x=u;
                           y=v;}
                       }
                       if(alpha >= beta){
                           return; //剪枝
                       }}else{
                           alpha = INT_MAX;
                           if(depth == DEPTH){
                           x=u;
                           y=v;}
                       }   //如果赢了，这个节点不用向下搜索


        }
       }
      }

     }else{//奇数层
            for (int i = 0; i <15 ; ++i) {
                            for (int j = 0; j < 15; ++j) {
                                int t = rank[15*i+j];
                                int u = X[t];
                                int v = Y[t];
                                if (gen(map,u,v) && !map[15*u+v]) {
                                    int Map[15][15];
                                    memmove(Map, map, sizeof(int) * 225);
                                    Map[u][v] =  Human;
                                    alpha1 = alpha;
                                    beta1 = beta;
                                    if(!sWin((int*)Map,Human)){
                                    minmax((int*)Map,depth-1,alpha1,beta1,x,y);
                                    if( alpha1 < beta ){
                                        beta = alpha1;
                                    }
                                    if(alpha > beta){
                                        return;
                                    }
                                 }else{
                                        beta = INT_MIN;
                                    }


                    }
                    }
                 }
}
}}

int point(int* map,int me,int you,int x,int y){ //评估棋盘上某一个点
    int con[5],flag[5]; //con：连子数 flag1：开合状态
    for(int i=1;i<5;i++){
        con[i]=1,flag[i]=2;
    }
    int u=1,v=1;      //(u,v)决定方向，这里是主对角线方向
    int up=1,down=1;  //向两个方向探索，作为是否继续探索的标志
    for(int i=1;i<5;i++){
        if(x+u<0 && x+u >14 && y+v<0 && y+v>14)
            up = 0;
        if(x-u<0 && x-u >14 && y-v<0 && y-v>14)
            down = 0;      //判断有没有到边界
        if(up){
            if(map[15*(x+u)+y+v]==me){
                con[1]++;
            }else{
                up=0;
                if(map[15*(x+u)+y+v]==you){
                    flag[1]--;}
            }}
        if(down){
            if(map[15*(x-u)+y-v]==me){
                con[1]++;
            }else{
                down=0;
                if(map[15*(x-u)+y-v]==you){
                    flag[1]--;}
            }}
        u=u*(i+1)/i;
        v=v*(i+1)/i;
    }
    u=1,v=-1;      //(u,v)决定方向，这里是副对角线方向
    up=1,down=1;  //向两个方向探索，作为是否继续探索的标志
    for(int i=1;i<5;i++){
        if(x+u<0 && x+u >14 && y+v<0 && y+v>14)
            up = 0;
        if(x-u<0 && x-u >14 && y-v<0 && y-v>14)
            down = 0;      //判断有没有到边界
        if(up){
            if(map[15*(x+u)+y+v]==me){
                con[2]++;
            }else{
                up=0;
                if(map[15*(x+u)+y+v]==you){
                    flag[2]--;}
            }}
        if(down){
            if(map[15*(x-u)+y-v]==me){
                con[2]++;
            }else{
                down=0;
                if(map[15*(x-u)+y-v]==you){
                    flag[2]--;}
            }}
        u=u*(i+1)/i;
        v=v*(i+1)/i;
    }
    u=1,v=0;      //(u,v)决定方向，这里是水平方向
    up=1,down=1;  //向两个方向探索，作为是否继续探索的标志
    for(int i=1;i<5;i++){
        if(x+u<0 && x+u >14 && y+v<0 && y+v>14)
            up = 0;
        if(x-u<0 && x-u >14 && y-v<0 && y-v>14)
            down = 0;      //判断有没有到边界
        if(up){
            if(map[15*(x+u)+y+v]==me){
                con[3]++;
            }else{
                up=0;
                if(map[15*(x+u)+y+v]==you){
                    flag[3]--;}
            }}
        if(down){
            if(map[15*(x-u)+y-v]==me){
                con[3]++;
            }else{
                down=0;
                if(map[15*(x-u)+y-v]==you){
                    flag[3]--;}
            }}
        u=u*(i+1)/i;
        v=v*(i+1)/i;
    }
    u=0,v=1;      //(u,v)决定方向，这里是竖直方向
    up=1,down=1;  //向两个方向探索，作为是否继续探索的标志
    for(int i=1;i<5;i++){
        if(x+u<0 && x+u >14 && y+v<0 && y+v>14)
            up = 0;
        if(x-u<0 && x-u >14 && y-v<0 && y-v>14)
            down = 0;      //判断有没有到边界
        if(up){
            if(map[15*(x+u)+y+v]==me){
                con[4]++;
            }else{
                up=0;
                if(map[15*(x+u)+y+v]==you){
                    flag[4]--;}
            }}
        if(down){
            if(map[15*(x-u)+y-v]==me){
                con[4]++;
            }else{
                down=0;
                if(map[15*(x-u)+y-v]==you){
                    flag[4]--;}
            }}
        u=u*(i+1)/i;
        v=v*(i+1)/i;
    }
    if(con[1] == 5||con[2] == 5||con[3] == 5 ||con[4] == 5){return 5;}//成五
    if((con[1] == 4&& flag[1]==2)||
       (con[2] == 4&& flag[2]==2)||
       (con[3] == 4&& flag[3]==2)||
       (con[4] == 4&& flag[4]==2)
        ){return 4;}//活四
    int cnt=0;
    for(int i=1;i<5;i++){
       if(con[i]==3 && flag[i]==2)
           cnt++;
    }
    if(cnt>=2)
        return 3; //双三
    if(cnt==1)
        return 2; //活三
    if((con[1] == 2&& flag[1]==2)||
       (con[2] == 2&& flag[2]==2)||
       (con[3] == 2&& flag[3]==2)||
       (con[4] == 2&& flag[4]==2)
        ){return 1;}//活二
    return 0;     //其他
}

int evaluate_point(int* map,int me,int you){   //获取棋盘每个点的分数
    int score=6;
    int p=0;
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            X[15*i+j]=i;
            Y[15*i+j]=j;
            rank[15*i+j]=15*i+j;
            if (gen(map,i,j) && !map[15*i+j]){
                value[15*i+j] = max(2*point(map,me,you,i,j)+1,2*point(map,you,me,i,j)); //同等权重下，进攻优于防守
                if(value[15*i+j]>=score){  //找到必胜棋或不堵必败棋,记下刻不容缓的那个位置
                    score=value[15*i+j];
                    p=15*i+j;
                }
            }
        }
    }
    Qsort((int*)value,(int*)rank,0,224);
    return p;
}


void play(int* map,int& x,int& y,int ai,int human){
    Ai=ai;
    Human = human;
    memset(value,-1,sizeof(int)*225);
    int flag=evaluate_point(map,Ai,Human);
    if(flag){     //返回非0值,有必胜棋或必堵棋
        x=flag/15;
        y=flag%15;
        return;
    }
    int alpha=INT_MIN,beta=INT_MAX;
    minmax(map,DEPTH,alpha,beta,x,y);
}
