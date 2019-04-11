#include <stdio.h>
#include <handy.h>
#define length 10
int main() {
  int i,j;
  int x = 100;
  int top = 200;
  int bottom = 100;
  char str[length] = "sample";
  char temp[2] = "";
  int position = 0;

  HgOpen(400.0, 400.0);


  while(1){

    for(i=top;i>bottom;i-=5){
      for(j=0;j<length;j++){
        temp[0] = str[j];
        if(position<j){  //上にいるときの処理
          HgText(x+(j*20),top,temp);
        }else if(position==j){  //落ちているときの処理
          HgText(x+(j*20),i,temp);
        }
        else{  //下にいるときの処理
          HgText(x+(j*20),bottom,temp);
        }
      }
      position++;
      HgSleep(0.2);
      HgClear();
    }


  }

return 0;
}
