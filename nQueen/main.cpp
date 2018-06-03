//
//  main.cpp
//  nQueen
//
//  Created by Joyce Chin on 2018/6/3.
//  Copyright © 2018年 Joyce Chin. All rights reserved.
//

#include <cstdio>
#include <algorithm>
#define GRID 30
using namespace std;


typedef struct{
    int row;
    int cost;
    int checkValid[GRID][GRID];
}BOARD;

int maxWeight,minWeight,queenTotal;
int weight[GRID][GRID];

void calculateQueen(BOARD board,int n){
    printf("%d\n",board.row);
    if(board.row==n){
        queenTotal++;
        maxWeight=max(maxWeight,board.cost);
        minWeight=min(minWeight,board.cost);
        return;
    }
    int i;
    int x,y;
    BOARD temp;
    for(i=0;i<n;i++){
        if(board.checkValid[board.row][i]==1){
            temp=board;
            temp.checkValid[temp.row][i]=2;
            temp.cost+=weight[temp.row][i];
            temp.row++;
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
        calculateQueen(temp,n);
        }
    }
}

int main()
{
    int n,i,j;
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
        maxWeight=0; minWeight=GRID*GRID*10; queenTotal=0;
        for(int i=0;i<GRID;i++) for(int j=0;j<GRID;j++) board.checkValid[i][j]=1;
        board.row=0;board.cost=0;
        calculateQueen(board,n);
        printf("The maximum weight of %d queens: %d\n",n,maxWeight);
        printf("The minimum weight of %d queens: %d\n",n,minWeight);
    }
    return 0;
}
