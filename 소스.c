#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void problem1()
{
	int a[10];
	
	for (int i = 0; i < 10; i++) {
		a[i] = rand();
	}

	printf("최댓값: %d\n최솟값: %d", maximum(a), minimum(a));
}

int maximum(int nums[10])
{
	int max = nums[0];
	
	for (int i = 1; i < 10; i++) {
		if (nums[i] > max) {
			max = nums[i];
		}
	}

	return max;
}

int minimum(int nums[10])
{
	int min = nums[0];

	for (int i = 1; i < 10; i++) {
		if (nums[i] < min) {
			min = nums[i];
		}
	}

	return min;
}


void problem2()
{
	int size;
	printf("입력할 숫자의 개수를 입력하시오.: ");
	scanf("%d", &size);

	int* a;
	a = (int*)malloc(size * sizeof(int));
	int* b;
	b = (int*)malloc(size * sizeof(int));

	printf("a: %d개의 정수를 입력하시오.: ", size);
	for (int i = 0; i < size; i++) {
		scanf("%d", &a[i]);
	}

	printf("b: %d개의 정수를 입력하시오.: ", size);
	for (int i = 0; i < size; i++) {
		scanf("%d", &b[i]);
	}

	if (array_equal(a, b, size) == 1) { printf("두 배열은 같음."); }
	else { printf("두 배열은 다름."); }
}

int array_equal(int a[], int b[], int size)
{
	int is_equal = 1;

	for (int i = 0; i < size; i++) {
		if(a[i]!=b[i]){
			is_equal = 0;
			break;
		}
	}

	return is_equal;
}


void problem3()
{
	int size;
	printf("입력할 숫자의 개수를 입력하시오.: ");
	scanf("%d", &size);

	int* x;
	x = (int*)malloc(size * sizeof(int));
	int* y;
	y = (int*)malloc(size * sizeof(int));

	printf("x: %d개의 정수를 입력하시오.: ", size);
	for (int i = 0; i < size; i++) {
		scanf("%d", &x[i]);
	}

	y = array_copy(x, y, size);

	printf("y: ");
	for (int i = 0; i < size; i++) {
		printf("%d ", y[i]);
	}
}

int array_copy(int x[], int y[], int size)
{
	for (int i = 0; i < size; i++) {
		y[i] = x[i];
	}

	return y;
}


void problem4()
{
	int random;
	int count = 0;

	for (int i = 0; i < 100; i++) {
		random = rand() % 10;
		
		if(i==99){ printf("가장 많이 나온 수: %d", most_count(count_num(random))); }
		else { count_num(random); }
	}
}

int count_num(int x)
{
	static int count_n[10];

	count_n[x] += 1;

	return count_n;
}

int most_count(int y[])
{
	int most = y[0];
	int most_num = 0;
	
	for (int i = 1; i < 10; i++) {
		if (y[i] > most) {
			most_num = i;
			most = y[i];
		}
	}

	return most_num;
}


int main()
{
	srand(time(NULL));

	problem3();

	return;
}