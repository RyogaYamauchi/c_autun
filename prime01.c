/*
 prime01.c
 素数かどうかを判定する
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	int number;
	int i; // ループカウンタ
	bool primeFlag = false;

	scanf("%d", &number);

	for(i=2; i<number; i++) {
		if( number % i == 0 ) { // 割り切れた
			printf("%d is not prime\n", number);
      primeFlag = true;
		}
		if (primeFlag ==true) break;
	}
	// ループを回りきった
	if (primeFlag == false){
	  printf("%d is prime\n", number);
  }

	return 0;
}
