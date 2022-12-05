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

//private:
	KPeople(const KPeople& rhs) // copy constructor
	{
		m_age = rhs.m_age;
		strcpy(m_name, rhs.m_name);
		printf("constructor(const KPeople&)\r\n");
	}
	// 함수를 정의할 때 이 함수를 객채가 만들어졌을 때
	// 멤버 엑세스 오퍼레이터 를 이용해서 (. ->) 를 통해 접근하지 못하도록 막을 수 있음
	// public: 으로 선언된건 접근 가능
	// private: 으로 하면 호출을 막을 수 있음.
	// Access Operator 이후에 선언된 것은 모두 영향을 받음
	// 외부에서 접근할 수 없는 상태 (호출을 못함) 가 됨
	// 그래서 복사 생성자를 막고 싶다면 복사 생성자만 private: 에 두면 됨
	// 이러면 복사 생성하는 코드를 막을 수 있음
public:

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

//KPeople GetPeople()
//{
//	KPeople t;
//	return t;
//}
// 객채를 만드는 용도로 사용하는 함수들을
// 팩토리 함수라고 함

KPeople GetPeople2()
{
	return KPeople("Han");
}

int main()
{
	//KPeople t;
	//t = GetPeople();
	// 이론상
	// KPeople t; 해서 한번 생성
	// GetPeople(); 안에서 KPeople t; 해서 한번 생성
	// GetPeople 이 return 하면 t 에 객체에 대입되기 전에 메모리 어딘가에 저장되야 해서
	// (일반적으로 정수같은건 레지스터에 저장됨, 레지스터값이 변수에 복사되는 코드 생김)
	// (하지만 크기가 크면 메모리 어딘가에 저장이 되고, 저장이 된다는 건 생성이 된다는 것)
	// 생성된 객채가 t 에 복사될 때 복사 생성자 호출
	// 그래서 생성자 3번, 복사생성자 1번 해서 4번 호출되길 기대

	// 하지만 실제로는 생성자 2번, 복사생성자 1번 호출됨
	// Getpeople의 리턴형이 레퍼런스 타입이 아니기 때문에 GetPeople 이 반환될 때
	// 내부에서 생성한 t 를 인자로 받는 복사 생성자가 호출이 되고,
	// 이를 main 의 t 에 대입함.

	KPeople t;
	t = GetPeople2();
	// 생성자가 두번 호출됨
	// 컴파일러가 리턴되자마자 대입되야한다는 것을 알고 있기 때문에
	// GetPeople2 에서 KPeople("Han") 을 생성하고 바로 main 의 t 에 대입 연산을 함
	// 이렇게 컴파일러가 반환값을 최적화 하는 것을
	// Return Value Optimization
	// RVO 라고 알려짐

	// 이 함수는 KPeople 의 복사 생성자가 private 이라면 컴파일 에러가 발생함
	// 복사 생성자를 호출하려고 시도하지만 private 이라 불가능 하기 때문임
	// 원레 코드는 return 할때 복사 생성자를 호출하는 코드가 맞음
	// 하지만 컴파일러가 최적화 과정에서 RVO 를 적용해서 복사 생성자 호출 없이
	// t 에 바로 대입되게 코드를 생성하기 때문에 이렇게 되는 것
	// 원레 코드 생성상 복사 생성자가 호출되어야 하기 때문에 컴파일 에러가 나는 것
	// 그래서 public: 으로 설정을 하면 복사 생성자가 호출 될 것이라고 생각할 수 있지만,
	// 결과적으로는 호출되지 않음
	// 코드를 생성할 시에는 복사 생성자가 있어야 해서 검사를 했지만
	// 실제로 생성한 코드에선 복사 생성자가 필요하지 않도록 RVO 를 적용해서 실제 복사 생성자는 호출되지 않음
	


	return(0);
}