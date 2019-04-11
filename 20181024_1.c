#include<stdio.h>

int main(){
  int num[5] = {22,80,57,60,50};
  int i,j,temp;

  for(i=0;i<5;i++){
    for(j=i+1;j<5;j++){
      if(num[j]<num[i]) {
        temp = num[i];
        num[i] = num[j];
        num[j] = temp;
      }
    }
  }

  printf("%d,%d,%d,%d,%d\n",num[0],num[1],num[2],num[3],num[4]);


  return 0;
}
