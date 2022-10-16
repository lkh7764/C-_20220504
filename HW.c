#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maximum(int[]);
int minimum(int[]);

void problem1()		//p.460 #2
{
	//배열 자체에 배열 끝을 나타내는 요소(널문자 등)가 있으면 크기를 넘길 필요 없음.
	int numbers[10];

	for (int i = 0; i < 10; i++) {
		numbers[i] = rand();
	}

	//배열에 숫자가 잘 들어갔는지 확인하는 코드.
	/*for (int i = 0; i < 10; i++) {
		printf("%d\n", numbers[i]);
	}*/

	printf("최댓값: %d\n", maximum(numbers));
	printf("최솟값: %d\n", minimum(numbers));

	printf("\n\n\n");
}

int maximum(int numbers[10])
{
	int max_num = numbers[0];
	for (int i = 0; i < 10; i++) {
		if (numbers[i] >= max_num) { max_num = numbers[i]; }
	}
	return max_num;
}

int minimum(int numbers[10])
{
	int min_num = numbers[0];
	for (int i = 0; i < 10; i++) {
		if (numbers[i] <= min_num) { min_num = numbers[i]; }
	}
	return min_num;
}



void problem2()		//p.460 #3
{

}

int input()
{
	int num;
}


void problem3()		//p.460 #4
{

}


void problem4()		//p.461 #5
{

}


int main()
{
	srand(time(NULL));
	problem1();

	return 0;
}
