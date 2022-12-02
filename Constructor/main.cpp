#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef BUILD

// 구조체는 은 모든 데이터 멤버가 public 인 클레스와 거의 유사함

// 이런 구조체를 클레스 라고 함
//struct KPeople
class KPeople
{
public: // 기본적으로는 private 임

	int m_age;
	char m_name[12];
	// 변수인 멤버를 Data member

	//void Initialize()
	//{
	//	m_age = 0;
	//	m_name[0] = 0;
	//}
	//void Finalize()
	//{
	//	m_age = 0;
	//	// 메모리 삭제 또는 파일 닫기...
	//}
	//// 객채가 생성되자마자 Init(); 파괴되기 전에는 Fin();
	// 하지만 클레스를 설계한 사람들이 특별한 함수 두개를 만듬
	// 그것을 생성자, 소멸자 라고 함

	KPeople() // 보통 초기화 하는 일을 담당
	{
		m_age = 0;
		m_name[0] = 0;
		printf("constructor()\r\n");
	}
	// 객채를 만들자 마자 자동으로 호출되기 때문에 함수 이름을 명시할 방법이 없음
	~KPeople() // 
	{
		printf("destructor()\r\n");
	}
	// 소멸자도 명시할 방법이 없음
	// 그래서 특별한 이름을 가져야 하는 것

	// 메모리를 할당하고 생성자를 호출
	// 파괴자를 먼저 호출하고 끝나면 메모리 해제
	// 메모리 해제되기 바로 전에 호출되는 함수

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
	// 함수인 멤버를 Member function
};

int main1()
{
	//KPeople a;
	////a.Initialize(); // 생성자가 대신 해줌
	//a.SetAge(19);
	//a.SetName("Han");
	//a.PrintPeople();
	////a.Finalize(); // 파괴자 (소멸자) 가 대신 해줌

	//KPeople* p;
	//p = (KPeople*)malloc(sizeof(KPeople));
	////p->KPeople(); // 클레스 이름과 모호함이 발생함
	//p->KPeople::KPeople(); // 이렇게 해야 함
	//// 메모리 할당을 하고 p 가 가리키고 있지만
	//// 생성자와 소멸자가 호출되지 않음
	//// malloc 으로 하면 생성자를 호출해주는 코드를 직접 작성해야 함
	////p->SetAge(19);
	////p->SetName("Han");
	//p->PrintPeople();
	//p->~KPeople(); // 파괴자 함수 앞엔 ~ 가 붙었기 때문에 모호함이 발생하지 않음
	//// p 가 가리키는 곳의 KPeople 의 파괴자를 호출한다는 의미
	//free(p);

	// C++ 에선 메모리를 동적으로 할당할 때 malloc 대신 new 를 사용함
	// new 는 연산자 함수
	KPeople* p;
	//p = (KPeople* )operator new(sizeof(KPeople)); // new function
	//// operator new 는 연산자임
	//// void * 리턴하기 때문에 캐스팅 해야 함
	//// 연산자 오버로딩을 통해 오버로딩될수 있기 때문에 명시적으로 operator new 라고 적어주는 것
	//// 이건 C++ 의 특별한 전역 함수라고 생각하면 됨 헤더 필요 없음
	//p->KPeople::KPeople();
	//// 하지만 이레도 생성자를 호출해줘야 함
	
	p = new KPeople; // new expression
	// 동적으로 KPeople 만큼의 메모리를 할당하고 생성자를 자동으로 호출
	// new expression 은 내부적으로 new function 을 호출하고
	// 생성자를 호출함
	// delete expression 도 같음
	// 그래서 new function, delete function 만 오버로딩이 가능함
	// 메모리를 할당하는 부분만 가로첼 수 있는 것
	// 메모리를 할당하고 생성자를 호출하는 부분은 컨트롤 할 수 없음

	p->PrintPeople();
	//p->~KPeople();
	//operator delete(p);
	delete p; // new 와 같이 메모리 p 를 해제하기 전에 파괴자를 호출함


	return(0);
}

#endif