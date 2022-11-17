#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct
{
	int age;
	char name[10];
} a;

// C 에서는 이렇게 테그 네임을 적을 수 있음 
struct People // 타입 정의
{
	int age;
	char name[10];
} b;
// 테그 네임이 들어가면 People 이라는 타입도 정의하는게 되고,
// b 라는 변수도 선언하는게 됨

struct People_ // 구조체로 타입을 정의할 때는 보통
{
	int age;
	char name[10];
}; // 변수는 선언하지 않음
// 이 문장은 오로지 People_ 이라는 타입을 정의한 것이 됨
// 가능은 하지만 그렇게 하면 한 문장에서 여러가지 의미가 포함되기 때문에 가독성이 떨어짐
// 전역 변수로 선언하고 싶으면
People_ p; // 이렇게 사용

void PrintPeople(People a)
{
	printf("%s : %i\r\n", a.name, a.age);
}

int main()
{
	a.age = 4;
	strcpy(b.name, "Hello");


	struct People c; // 이렇게 선언할 수 있음
	c.age = 5;
	strcpy(c.name, "World");

	PrintPeople(b);
	PrintPeople(c);

	return(0);
}