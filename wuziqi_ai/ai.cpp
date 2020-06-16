#include <stdio.h>
#include <string.h>
#include <cmath>

#define DEPTH 4



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
                    if(con == 5) score+=1000000000;
                }   //遇到没子的地方，结算分数，开合状态=1
                flag = 1;
                con = 0;
            }else if(map[15*i+j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=1000000000;
                }
                flag = 0;
                con = 0; //遇到对面的子，结算分数，开合状态=0
            }else if(map[15*i+j] == me){
                con++;
            }
            if ( j == 14 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=1000000000;
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
                    if(con == 5) score+=1000000000;
                }
                flag = 1;
                con = 0;
            }else if(map[15*i+j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=1000000000;
                }
                flag = 0;
                con = 0;
            }else if(map[15*i+j] == me){
                con++;

            }
            if ( i == 14 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=1000000000;
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
                    if(con == 5) score+=1000000000;
                }
                flag = 1;
                con = 0;
            }else if(map[15*i+j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=1000000000;
                }
                flag = 0;
                con  = 0;
            }else if(map[15*i+j] == me){
                con++;
            }
            if ( i+j == 14 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=1000000000;
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
                    if(con == 5) score+=1000000000;
                }
                flag = 1;
                con = 0;
            }else if(map[15*j+i+j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=1000000000;
                }
                flag = 0;
                con = 0;
            }else if(map[15*j+i+j] == me){
                con++;

            }
            if ( i+j == 14 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=1000000000;
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
                    if(con == 5) score+=1000000000;
                }
                flag = 1;
                con = 0;
            }else if(map[15*j+i-j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=1000000000;
                }
                flag = 0;
                con = 0;
            }else if(map[15*j+i-j] == me){
                con++;

            }
            if ( i-j == 0 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=1000000000;
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
                    if(con == 5) score+=1000000000;
                }
                flag = 1;
                con = 0;
            }else if(map[15*(i+j)+14-j] == you){
                if (con > 0) {
                    score += pow(10, con + flag - 2);
                    if(con == 5) score+=1000000000;
                }
                flag = 0;
                con = 0;
            }else if(map[15*(i+j)+14-j] == me){
                con++;

            }
            if ( i+j == 14 ){
                score += pow(10, con+flag-2);
                if(con == 5) score+=1000000000;
                flag = 0;
                con = 0;
            }
        }
    }
    return score;
}

int Score(int* map){
    return evaluate(map,2,1)-evaluate(map,1,2);
}

int win(int score,int& winner){
    if(score>100000000){
        return winner=2;
       }
    if(score<-100000000){
        return winner=1;
    }
    return 0;
} //为什么这么粗糙，因为成5后会加10000000000分，根据数学运算可知这么判断一定正确

int gen(int*map,int x,int y){
    for(int i=-2;i<=2;i++){
        for(int j=-2;j<=2;j++){
            if(x+i>=0 && x+i <=14 && y+j>=0 && y+j<=14 && map[15*(x+i)+y+j]){
                return 1;
            }
        }
    }
    return 0;
}

void minmax(int* map,int depth,int& alpha,int& beta,int&x,int&y) {
    int alpha1,beta1;//李代桃僵，把α和β传递给下一级
    if (depth == 0) {
        alpha = Score(map);
    } else {
        if( !(depth%2)){//偶数层
            for (int i = 14; i >= 0; --i) {
                for (int j = 0; j < 15; ++j) {
                    if (!map[15 * i + j] && gen(map,i,j)) {
                       int Map[15][15];
                       memmove(Map, map, sizeof(int) * 225);
                       Map[i][j] =  2;
                       alpha1 = alpha;
                       beta1 = beta;
                       minmax((int*)Map,depth-1,alpha1,beta1,x,y);
                       if( alpha < beta1 ){
                           alpha = beta1;
                           if(depth == DEPTH){
                           x=i;
                           y=j;}
                       }
                       if(alpha > beta){
                           return; //剪枝
                       }

        }
       }
      }

     }else{//奇数层

                        for (int i = 14; i >= 0; --i) {
                            for (int j = 0; j < 15; ++j) {
                                 if (!map[15 * i + j] && gen(map,i,j)) {
                                    int Map[15][15];
                                    memmove(Map, map, sizeof(int) * 225);
                                    Map[i][j] =  1;
                                    alpha1 = alpha;
                                    beta1 = beta;
                                    minmax((int*)Map,depth-1,alpha1,beta1,x,y);
                                    if( alpha1 < beta ){
                                        beta = alpha1;
                                    }
                                    if(alpha > beta){
                                        return;
                                    }
                                 }


                    }
                    }
                 }
}
}


void Qsort(int *a,int *b,int low ,int high) // a：待排序列，b： 待排序列元素对应序号
{
    if(low>=high)
        return ;
    printf("start:%d  end:%d\n",low,high);
    int first = low ;
    int last  = high ;
    int key   = a[low] ;
    int key1  = b[low] ;
    while(first<last)
    {
        while(first<last && a[last]>=key)
            --last ;
        a[first] = a[last] ;
        b[first] = b[last] ;
        while(first<last && a[first]<=key)
            ++first ;
        a[last] = a[first] ;
        b[last] = b[first] ;
    }
    a[first] = key ;
    b[first] = key1;
    Qsort(a,b,low,first-1) ;
    Qsort(a,b,first+1,high);
}



void play(int* map,int& x,int& y){
    int alpha=INT_MIN,beta=INT_MAX;
    minmax(map,DEPTH,alpha,beta,x,y);
 }
