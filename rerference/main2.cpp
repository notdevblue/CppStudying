#include <stdio.h>

//void Swap(int i, int j)
//{
//	int t = i;
//	i = j;
//	j = t;
//}

void Swap(int* i, int* j)
// 이런 파라미터를 in out 파라미터라고 부름.
// in으로 무언가를 주고, out 으로 파라미터 값이 바뀌어서 넘어오기 때문
{
	int t = *i;
	*i = *j;
	*j = t;
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

	//Swap(i, j);
	// 위와 다르게 안 바뀜
	// 
	// i, j 를 전달할 때
	// i, j 값 말고
	// 주소값을 전달해서 저장
	// 그렇게 되면 원레 main 에 있는 i, j 값 바꿀 수 있음 

	Swap(&i, &j);


	printf("%i, %i\r\n", i, j);


	return(0);
}