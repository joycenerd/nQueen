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
#define INF 1000000
using namespace std;


typedef struct{
    int row;
    int cost;
    int checkValid[GRID][GRID];
}BOARD;

int maxWeight,n;
int weight[GRID][GRID];
int rowMax[GRID];

void calculateQueen(BOARD board){
    //printf("%d\n",board.row);
    if(board.row==n){
        maxWeight=max(maxWeight,board.cost);
        //minWeight=min(minWeight,board.cost);
        return;
    }
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
        calculateQueen(temp);
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
        for(i=0;i<n;i++) rowMax[i]=-INF;
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                rowMax[i]=max(rowMax[i],weight[i][j]);
            }
        }
        for(i=n-2;i>=0;i--) rowMax[i]+=rowMax[i+1];
        for(int i=0;i<GRID;i++) for(int j=0;j<GRID;j++) board.checkValid[i][j]=1;
        board.row=0;board.cost=0;
        maxWeight=0;
        calculateQueen(board);
        printf("The maximum weight of %d queens: %d\n",n,maxWeight);
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                weight[i][j]=-weight[i][j];
            }
        }
        for(int i=0;i<GRID;i++) for(int j=0;j<GRID;j++) board.checkValid[i][j]=1;
        board.row=0;board.cost=0;
        maxWeight=-GRID*GRID*10;
        calculateQueen(board);
        printf("The minimum weight of %d queens: %d\n",n,-maxWeight);
    }
    return 0;
}
