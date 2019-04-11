#include<stdio.h>
#include<handy.h>

int main(){
  int i=0;
  char str[10] = "asdfg";
  char temp[2] = "";

  HgOpen(600,600);

  for(i=0;i<10;i++){
    temp[0] = str[0];
    HgText(200,200,str);
  }

  HgGetChar();

  return 0;
}
