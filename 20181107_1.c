#include <stdio.h>
#include <handy.h>
#define length 10
int main() {
  int i;
  int x = 100;
  int y = 100;
  char *p;
  char str[length] = "sample";
  char temp[2] = "";

  printf("%s\n",str);



  HgOpen(400.0, 400.0);


  for(i=0;i<length;i++){
    temp[0] = str[i];
    HgText(x,y,temp);
    x+=10;
    y+=10;
  }


  HgGetChar();
  HgClose();

return 0;
}
