#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
bool judge(long);

int main(void){
  clock_t passage;
  double sec;
  long number;
  printf("number : ");
  scanf("%ld",&number);

  if(judge(number)==true) printf("素数やで\n");
  if(judge(number)==false) printf("素数ちゃうで\n");

  /* 経過時間を取得 */
  if ( (passage = clock()) == (clock_t)(-1) ) {
      fprintf(stderr,"経過時間の取得に失敗しました.\n");
      return EXIT_FAILURE;
  }
  sec = (double)passage / CLOCKS_PER_SEC;

  /* 経過時間を秒単位で表示 */
  printf("\nプログラム開始から%.2f秒経過しました．\n", sec);

  return 0;

}

bool judge(long number){
  int i;
  for(i=2;i<=number;i++){
    if(number%i==0) {
      if(i==number){
        return true;
      }
      else{
        return false;
      }
    }
  }
  return false;
}
