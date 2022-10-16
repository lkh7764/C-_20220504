#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void problem1()
{
	int x = 20;
	int y = 10;

	printf("두 수의 합: %d \n", x + y);
	printf("두 수의 차: %d \n", x - y);
	printf("두 수의 곱: %d \n", x * y);
	printf("두 수의 몫: %d \n", x / y);
	
	printf("\n\n\n");
}

void problem2()
{
	float num1;
	float num2;

	printf("첫번째 숫자를 입력하세요.: ");
	scanf("%f", &num1);
	printf("두번째 숫자를 입력하세요.: ");
	scanf("%f", &num2);

	float sum = num1 + num2;

	printf("두 수의 합: %f", sum);

	printf("\n\n\n");
}

void problem3()
{
	float radius;

	printf("반지름을 입력하세요.: ");
	scanf("%f", &radius);

	float area = radius * radius * 3.141592;

	printf("원의 면적: %f", area);

	printf("\n\n\n");
}

void problem4()
{
	double width;
	double height;

	printf("사각형의 너비를 입력하세요.: ");
	scanf("%lf", &width);
	printf("사각형의 높이를 입력하세요.: ");
	scanf("%lf", &height);

	double area = width * height;
	double perimeter = 2 * (width + height);

	printf("사각형의 면적: %lf", area);
	printf("사각형의 둘레: %lf", perimeter);

	printf("\n\n\n");
}

void problem5() 
{
	float fahrenheit;

	printf("화씨온도를 입력하세요.: ");
	scanf("%f", &fahrenheit);

	float celsius = ((float)5 / (float)9) * (fahrenheit - 32);

	printf("섭씨온도: %f", celsius);

	printf("\n\n\n");
}

int main()
{
	problem1();
	problem2();
	problem3();
	problem4();
	problem5();

	return 0;
}