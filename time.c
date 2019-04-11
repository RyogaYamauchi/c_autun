#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

/* main */
int main(void) {
    clock_t passage;
    double sec;

    /* 経過時間を取得 */
    if ( (passage = clock()) == (clock_t)(-1) ) {
        fprintf(stderr,"経過時間の取得に失敗しました.\n");
        return EXIT_FAILURE;
    }
    sec = (double)passage / CLOCKS_PER_SEC;

    /* 経過時間を秒単位で表示 */
    printf("\nプログラム開始から%.2f秒経過しました．\n", sec);

    return EXIT_SUCCESS;
}
