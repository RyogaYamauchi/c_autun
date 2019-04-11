#include<stdio.h>
int main(){
  int result[8]={};
  int num[3][3]={};
  int i,j,flag=0;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      scanf("%d",&num[i][j]);
    }
  }
  for(j=0;j<3;j++){  //横
      result[j]=num[j][0]+num[j][1]+num[j][2];
  }
  for(j=0;j<3;j++){  //縦
      result[j+3]=num[0][j]+num[1][j]+num[2][j];
  }
  result[6]=num[0][0]+num[1][1]+num[2][2];  //斜め
  result[7]=num[2][0]+num[1][1]+num[0][2];  //斜め

  for(i=0;i<7;i++){
    if(result[i]==result[i+1]) flag+=1;
  }

  if(flag==7){
    printf("魔法陣やで\n");
  }
  else{
    printf("魔法陣ちゃうで\n");
  }
}
