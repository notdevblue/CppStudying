#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class KPeople
{
public:

	int m_age;
	char m_name[12];

	KPeople() // 기본 생성자
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
	// C++ 에선 함수 이름이 같더라도 매개변수가 다르다면
	// 함수 이름을 중복되게 정의할 수 있음 (오버로딩)

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

int main()
{
	//KPeople* p;
	//p = new KPeople; // 파라미터가 없기 때문에 가능
	// 파라미터가 있다면 명시해 줄 수 있음
	//p = new KPeople(); // 이렇게 가능

	//p = new KPeople[3];
	// KPeople 을 위해서 메모리를 연속적으로 3개 할당하고
	// 각각의 element 를 위해 생성자를 호출하라는 의미
	// p[0].PrintPeople();
	// p[1].PrintPeople();
	// p[2].PrintPeople();
	//delete[] p; // 만약 [] 하면 delete 도 []

	// 만약 bracket 을 사용해서 생성했는데
	// bracket 을 빠뜨리면 어떻게 되는가?
	// 요즘 컴파일러는 에러를 발생시킴
	// but 예전 컴파일러에선 이상없이 실행이 됨 (vsc 2010 이전)
	// 메모리를 3개만큼 할당했지만 첫번째 객채만 파괴자 호출
	// 메모리 헤제는 잘 되지만 파괴자가 한번만 호출됨

	//p->PrintPeople();
	//delete p;


	//KPeople* p;
	//p = new KPeople[3]; // 매개변수를 전달 안 함. 첫번째 생성자 호출
	//delete[] p;

	//KPeople p("Hello"); // p 객채 생성자 중 char 받는게 있으면 호출 (객체는 스텍에 들어가요 new 안해서)
	//KPeople p(154); // p 생성자 중 정수를 받는게 없어서 컴파일 에러를 냄

	//KPeople pe = "Han"; // implicit constructor call
	// pe 라는 객체를 만들고 생성자에 "Han" 을 전달한다는 의미
	// 암시적 생성자 호출
	
	KPeople pe("Han");

	Test(pe); // 문제가 없음.
	//Test("Mike"); // 하지만 만약에 이렇게 전달하게 된다면?
	// 객체를 매개변수로 받는다면 객체에 생성자 중
	// 이 표현식을 받는 생성자가 있는지 확인 함
	// KPeople 은 const char* 를 받는 생성자가 있기 때문에
	// 이 문장은 암시적으로 생성자를 호출해서 문제없이 Test 함수가 실행됨.
	// 이 문제를 막기 위해 생성자에 explicit 이라는 키워드를 사용
	// 명시적인 생성자 호출만 받겠다는 의미
	// 생성자 문법을 사용했을 때만 호출이 가능하게 됨

	Test(KPeople("Mike")); // temporary object


	return(0);
}