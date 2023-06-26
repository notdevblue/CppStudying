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

// People 과 관련된 구조체를 조작하는 함수는 두개가 있음
// PrintPeople 과 SetAge
// People 과 관련된 함수는 첫번째 파라미터로 People 을 받도록 만들어짐
// 이제 여기서 함수도 구조체 멤버로 둘 수 없을까?
// C++ 의 구조체에선 함수를 구조체 맴버로 선언할 수 있음
// 구조체 안에 함수가 들어갈 경우 이를 멤버 함수라고 부름
// 이제 더이상 함수가 아니게 됨. People 이라는 구조체의 맴버 함수가 되는 것
// 그래서 구조체를 통해서만 함수를 호출 할 수 있게 됨

// 멤버 함수인 경우 전달하지 않아도 멤버 함수를 호출한 객채의 시작 주소가 전달됨.
// 그리고 전달되는 포인터의 키워드는 this 라고 되어 있음
// 파라미터를 받지 않아도 자동으로 전달된 키워드를 사용하면 됨
// 이를 this call 이라고 함
// 
// C 와 C++ 은 함수가 다름
// 오버로딩 때문에 C++ 에선 함수 이름이 그대로 유지되지 않음 
// 컴파일러가 변경함. Name Mangling 이라고 함
// 마찬가지로 맴버 함수도 다름
// 첫번째 인자로 항상 자기 자신의 시작 주소가 전달됨
// 하지만 멤버 함수 안에서는 자기 자신의 맴버를 접근할 때에는
// 자기 자신인 경우에 this-> 를 생략해도 됨
// 자동으로 this-> 가 붙는 거임
// 보통 관례상 자기 자신의 맴버를 접근할 때에는 this-> 쓰지 않음
// 이것을 this 호출 관례
// 일반 함수는 C 호출 관례
// C++ 에서는 C++ 호출 관례를 따라 호출이 됨

// 구조체가 멤버 변수와 멤버 함수를 동시에 가질 때 이를 클레스 라고 부름
// 멤버를 함수로 가지는 구조체를 메모리에 할당할때는 new 를 사용함

// 생성자는 특별하게 정의된 멤버 함수
// 파괴자는 특별하게 정의된 멤버 함수

// Linked list 를 작성하기 위해서는 구조체 포인터를 자기 자신의 멤버로 사용해야함
// 구조체 멤버를 타입이 아니라 특정한 몇 비트만 차지하도록 비트 필드 구조체를 만들 수 있음
// 나중에 강의에서 설명하신데요 
// 
// 구조체는 멤버를 위해서 모두가 메모리 할당이 됨
// union 은 가장 큰 멤버를 위해서만 메모리 할당이 됨. 이것이 차이점
// 가끔 사용할 일이 있지만 이거도 다음에 설명하신데요.

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
	++a.age;
	// 함수가 종료될 시 메모리에서 pop 되기 때문에 원레의 값이 바뀌지 않음  
}

// 무언가 바꿀려고 하면 주소를 전달해야 함
void SetAge(People* a, int newAge)
{
	a->age = newAge;
	// a 가 구조체가 아니라
	// a 가 가리키는 내용이 구조체임
	// (*a).age = newAge;

}

int main()
{
	//People aa;
	//aa.age = 4;
	//strcpy(aa.name, "Hello");
	//char* cp = (char*)&aa;
	//// 구조체는 구조체 맴버들을 전부 다 할당하고 나서 
	//// 구조체 자신을 가리키는 맴버임
	//// cp + 5 하면 e 가 나올거임
	//printf("%c\r\n", cp[5]);




	//struct People c; // 이렇게 선언할 수 있음
	//c.age = 5;
	//strcpy(c.name, "World");

	//PrintPeople(b);

	//// setage 의 param 이 포인터이기 때문에 주소로 전달함
	//SetAge(&aa, aa.age + 1);


	People* d;
	// 구조체 (포인터) 를 사용하기 위해서는
	// 가리키는 곳에 꼭 메모리 할당을 해 줘야 함
	//d = (People*)malloc(sizeof(People));
	d = new People;
	// People 만큼의 메모리 공간을 할당해줌

	d->age = 4;
	strcpy(d->name, "Gentoo");

	PrintPeople(*d);
	delete d;
	return(0);
}