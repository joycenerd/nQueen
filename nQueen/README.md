# nQueen Problem

- n*n的方格中，每個方格都有一個weight，皇后可以攻擊8個方位任意距離的格子，要在皇后不會互相攻擊的狀態之下
    1. 剛好放n個皇后
    2. 放皇后的方格weight總和最大和最小
- 無解只會出現在n<=3的情況
- 宣告一個紀錄n*n棋盤格的狀態的structure

```cpp
//記錄皇后狀態的棋盤格
typedef struct{
    int row;  //記錄目前做到哪個row了
    int cost;  //記錄每組解的weight總和
    int checkValid[GRID][GRID];   //不可放皇后0,可放皇后1,已放皇后2
}BOARD;
```

- 先specify無解的情況，這樣可以少做一些沒有必要的事情

```cpp
if(n<=3){
            printf("-1 -1\n");
            continue;
        }
```

- 在做運算之前，我們先做優化-->紀錄rowMax，先把每個row的最大weight找出來，rowMax是每個row以下其他row的最大weight總和-->再做運算時如果此時的解加上rowMax還小於目前的最佳解的話，就直接return，可以少做很多白工

```cpp
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        rowMax[i]=max(rowMax[i],weight[i][j]);  //先找每個row的最大weight
    }
}
//此row的基準值是下面各個row的最大weight總和
for(i=n-2;i>=0;i--) rowMax[i]+=rowMax[i+1];
```

```cpp
if(board.cost+rowMax[board.row]<=maxWeight) return;
```

- 初始我的checkValid[][]全為1-->可放皇后
- 每次呼叫副程式就先copy一份此時棋盤格struct-->用copy的那份來做運算，避免修改到原棋盤格，造成後面無法遞迴呼叫
- 每加一個queen進入棋盤格，就把剩下所有不可能的棋盤格標示為0

```cpp
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
```

- 做到最後一個row就把此時的解和我原來的最佳解取max

```cpp
if(board.row==n){
    maxWeight=max(maxWeight,board.cost);
    //minWeight=min(minWeight,board.cost);
    return;
}
```

- max的時候從main呼叫一次副程式，min的時侯所有初始條件都加個負號在呼叫一次，答案再加個負號回來還原即可
