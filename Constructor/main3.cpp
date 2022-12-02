#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



class KPeople
{
public:

	int m_age;
	char m_name[12];

	KPeople()
	{
		m_age = 0;
		m_name[0] = 0;
		printf("constructor()\r\n");
	}
	explicit KPeople(const char* _name)
	{
		m_age = 0;
		strcpy(m_name, _name);
		printf("constructor( const char* )\r\n");
	}

	KPeople(const KPeople& rhs) // copy constructor
	{
		m_age = rhs.m_age;
		strcpy(m_name, rhs.m_name);
		printf("constructor(const KPeople&)\r\n");
	}
	// 객체가 복사되는 문법을 표현해주기 위해서
	// 반드시 (const 자기 자신 타입의 레퍼런스) (계속해서 복사 연산이 일어나면 안 되기 때문에)
	// 그리고 적절하게 내부에서 복사 동작을 구현해 주어야 함

	~KPeople()
	{
		printf("destructor()\r\n");
	}
	void PrintPeople()
	{
		printf("%s : %i\r\n", m_name, m_age);
	}

	void SetAge(int _age)
	{
		m_age = _age;
	}

	void SetName(const char* _name)
	{
		strcpy(m_name, _name);
	}
};

void Test(KPeople p)
{
	p.PrintPeople();
}
// Test(KPeople("an");
// 이렇게 파라미터를 전달한 경우,
// 컴파일러가 최적화를 함
// 그래서 복사 생성자가 호출되지 않을수 있어요.
// p 생성자에 바로 "Juan" 을 넘김 
// KPeople 이 만들어지고 복사되는 코드가 아닌
// 바로 p 에 생성자 호출

int main()
{
	//KPeople p("Han");
	//
	//KPeople temp = KPeople("Jan");
	// temp 의 생성자의 param 으로 jan 을 전달한다는 의미
	// 객체를 생성해서 대입한다는 의미가 아님

	//Test(KPeople("Juan"));
	// rvalue 로 전달된 것이 아닌 이렇게 단독으로 쓰여진 것은
	// 객체의 파라미터로 Juan 을 전달하고 잠시 스텍에 만들어지는
	// 임시 객체를 만든다는 것
	// KPeople 타입의 Juan 을 파라미터로 받는 객체 를 생성한다는 문장
	// Test 에 Juan 을 전달했을때 객체 p 가 생성되야 하므로
	// 이 코드는 객체를 두번 만듬
	// 그러니 생성자 2번 파괴자 2번 호출됨
	// 하지만 이 코드를 돌리면 생성자는 1번 호출되고, 파괴자는 2번 호출됨
	
	// 이 상황이 지금은 문제가 없는데 문제가 될 수 있음
	// 생성자와 파괴자의 쌍이 안 맞기 때문에
	// 생성자에서 동적으로 메모리 할당을 하고 파괴자에서
	// 동적으로 할당한 메모리를 파괴하는 경우
	// 쌍이 안 맞아서 메모리 leak 이 발생할 수 있음
	// 이런 경우를 막으려면 생성자를 정의할 때 객체가 복사되는 경우의
	// 특별한 생성자를 정의해 주어야 함

	KPeople temp = KPeople("Jan");
	Test(temp);

	return(0);
}