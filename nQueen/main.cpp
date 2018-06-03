//
//  main.cpp
//  nQueen
//
//  Created by Joyce Chin on 2018/6/3.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <cstdio>
#include <algorithm>  //max
#define GRID 30
#define INF 1000000
using namespace std;


int maxWeight,n;  //maxWeight最大weight總和
int weight[GRID][GRID];  //每格棋盤格的weight
int rowMax[GRID];  //判斷最佳解的基準值

//記錄皇后狀態的棋盤格
typedef struct{
    int row;  //記錄目前做到哪個row了
    int cost;  //記錄每組姐的weight總和
    int checkValid[GRID][GRID];   //不可放皇后0,可放皇后1,已放皇后2
}BOARD;

//遞迴找放n個queen的最佳解
void calculateQueen(BOARD board){
    //如果以做到最後一個row，就比較此次總weight和目前最佳解誰比較大
    if(board.row==n){
        maxWeight=max(maxWeight,board.cost);
        //minWeight=min(minWeight,board.cost);
        return;
    }
    //如果目前累積的cost＋下面剩下每個row的最大值還小於目前的最佳解的話那此解就算算的出來也不會是最佳解，所以直接return，節省時間
    if(board.cost+rowMax[board.row]<=maxWeight) return;
    int i;
    int x,y;
    BOARD temp;
    for(i=0;i<n;i++){
        if(board.checkValid[board.row][i]==1){
            temp=board;
            temp.checkValid[temp.row][i]=2;
            temp.cost+=weight[temp.row][i];
            temp.row++;
            //把所有不可能放皇后的地方標示為0
        for(x=temp.row;x<n;x++) temp.checkValid[x][i]=0;
        x=temp.row; y=i+1;
        while(x<n && y<n){
            temp.checkValid[x][y]=0;
            x++; y++;
        }
        x=temp.row; y=i-1;
        while(x<n && y>=0){
            temp.checkValid[x][y]=0;
            x++;y--;
        }
        calculateQueen(temp);  //要一直遞迴到row=n,或是無法放n個皇后為止
        }
    }
}

int main()
{
    int i,j;
    BOARD board;
    while(1){
        printf("enter n*n board's n: ");
        scanf("%d",&n);
        if(n==0) break;
        printf("enter the weight of each cell in the board:\n");
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                scanf("%d",&weight[i][j]);
            }
        }
        //先算最大值
        for(i=0;i<n;i++) rowMax[i]=-INF;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                rowMax[i]=max(rowMax[i],weight[i][j]);  //先找每個row的最大weight
            }
        }
        //此row的基準值是下面各個row的最大weight總和
        for(i=n-2;i>=0;i--) rowMax[i]+=rowMax[i+1];
        //初始整個棋盤都是可放皇后
        for(int i=0;i<GRID;i++) for(int j=0;j<GRID;j++) board.checkValid[i][j]=1;
        board.row=0;board.cost=0;
        maxWeight=0;
        calculateQueen(board);
        printf("The maximum weight of %d queens: %d\n",n,maxWeight);
        //在算最小值-->全部都加個負號就對了
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                weight[i][j]=-weight[i][j];
            }
        }
        for(i=0;i<n;i++) rowMax[i]=-INF;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                rowMax[i]=max(rowMax[i],weight[i][j]);
            }
        }
        for(i=n-2;i>=0;i--) rowMax[i]+=rowMax[i+1];
        for(int i=0;i<GRID;i++) for(int j=0;j<GRID;j++) board.checkValid[i][j]=1;
        board.row=0;board.cost=0;
        maxWeight=-GRID*GRID*10;
        calculateQueen(board);
        //最後就是把答案再加個負號還原最小值-->負的最大值是正的最小值
        printf("The minimum weight of %d queens: %d\n",n,-maxWeight);
    }
    return 0;
}
