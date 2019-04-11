#include <stdio.h>
#include <handy.h>
int main(){
  char moji[100];
  char result[100];
  int y, x;
  int i=0;
  int a,length=0;

  printf("文字を書いてください\n");
  scanf("%s",moji);

  while(moji[i]!='\0'){
    printf("moji[i] : %c\n",moji[i]);
    result[i] = moji[i];
    printf("result[i] : %c , moji[0] : %s\n",result[i],moji);
    length++;
    i++;
  }

  printf("result : %s\n",&result);

  for(i=0;i<length;i++){
    printf("%c\n",moji[i]);//ちゃんとスキャンしたか
  }
  printf("%d\n",length );//作動しているか


  //これ以下で配列がおかしくなってabort trap6
  HgOpen(400.0, 400.0);
  HgSetWidth(1.0);
  HgSetColor(HG_BLACK);
  x=0;
  y=0;

  for(i=0;i<length;i++){
      HgSetFont(HG_M,40);
      HgText(x,y,);
      x+=50;
      y+=50;

  }

  HgGetChar();
  HgClose();
return 0;
}
