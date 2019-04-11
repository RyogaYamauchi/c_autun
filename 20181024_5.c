#include<stdio.h>
#define Times 1 //回す回数

//　グローバル変数
int data[3][3] = {{1,1,1},{0,1,0},{0,1,0}};
int result[3][3] = {};

//プロトタイプ宣言
int Rotate();
int draw();
int update();

int main(){
  int i,j;

  //初期値代入
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
       result[i][j] = data[i][j];
    }
  }

  printf("before\n");

  for(i=0;i<Times+1;i++){
    draw();
    Rotate();
    update();
    if(i<Times)printf("after\n");
  }
  return 0;
}

//　描画処理
int draw(){
  int i,j;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      if(result[i][j] == 0) printf("■ ");
      if(result[i][j] == 1) printf("□ ");
    }
    printf("\n");
  }
  return 0;
}

//回転処理
int Rotate(){
  int i,j;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      result[i][2-j] = data[j][i];
    }
  }
  return 0;
}

//更新処理
int update(){
  int i,j;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
       data[i][j]= result[i][j];
    }
  }
  return 0;
}
