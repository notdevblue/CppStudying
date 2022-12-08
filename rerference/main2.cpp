#include <stdio.h>

void Swap(int i, int j)
{
	int t = i;
	i = j;
	j = t;
}


int main()
{
	// & 연산자는 모호함이 발생할 수 있음
	// bitwise and operator
	// address-of operator

	int i = 2;
	int j = 3;
	int t;
	// 이런 변수들이 메모리에 할당되는 공간을 stack 이라고 함

	// swap i, j
	//t = i;
	//i = j;
	//j = t;

	Swap(i, j);
	// 위와 다르게 안 바뀜
	// 


	printf("%i, %i\r\n", i, j);


	return(0);
}