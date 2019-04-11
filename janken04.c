/*
 じゃんけん判定
 */

#include <stdio.h>

int main() {
	int me, you;
	scanf("%d %d", &me, &you);
	
	switch ( (you - me + 3) % 3) {
		case 0: // あいこ
			printf("even\n");
			break;
		case 1: // 勝ち
			printf("win\n");
			break;
		default: //負けの場合、また、２しか出ない
			printf("lose\n");
			break;
	}
	return 0;
}
