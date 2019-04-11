#include<stdio.h>
int main(){

  int i,j,k;
  int card[3][3];
  int count = 0;
  int num[9] = {};
  int result[5] = {};
  int verticalBingo = 0;
  int horizontalBingo = 0;
  int diagonalRightBingo = 0;
  int diagonalLeftbingo = 0;

  for(i=0;i<9;i++){          //カードの列を入力
    scanf("%d",&num[i]);
  }
  for(i=0;i<5;i++){          //言われた番号を入力
    scanf("%d",&result[i]);
  }

  //入力された値をカードに配列する
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      card[i][j] = num[count];
      for(k=0;k<5;k++){
        if(card[i][j] == result[k]) card[i][j] = 0;
      }
      count++;
    }
  }

  //計算ごのカードを出力
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      printf("%d ",card[i][j]);
    }
    printf("\n");
  }
  printf("-- -- --\n");

  //判定
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      if(card[i][j]==0) verticalBingo++;     //縦の判定
      if(card[j][i]==0) horizontalBingo++;   //横の判定
    }
    if(card[i][i]==0) diagonalLeftbingo++;   //左上から始まる斜めの判定
    if(card[i][2-i] == 0)diagonalRightBingo++;  //右上から始まる斜めの判定

    if(verticalBingo == 3){    //横がビンゴ
      printf("bingo!\n");
      break;
    }
    if(horizontalBingo == 3){  //縦がビンゴ
      printf("bingo!!\n");
      break;
    }
  }

  if(diagonalLeftbingo == 3 || diagonalRightBingo == 3){  //どちらかの斜めがビンゴ
    printf("bingo!!!\n");
  }

  return 0;
}
