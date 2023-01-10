#include <stdio.h>
#include <memory.h>

class KBase;

typedef void (KBase::* FP)();
// void 를 return 하고 void 를 parameter 로 받는 
// KBase 에 대한 시작 주소에 대한 타입
// 멤버 함수에 대한 시작 주소

class KBase
{
	int i, j, k;
public:
	KBase()
	{
		i = 1;
		j = 5;
		k = 3;
	}

	void A()
	{
		int* p = reinterpret_cast<int*>(this);

		printf("%d\n", p[1]); // x64 에선 1 출력 안됨
		printf("%d\n", p[2]); // x64 에선 1 출력됨

		void*** po = (void***)this;
		// this 포인터를 포인터의 포인터의 포인터로 간주
		void** pvtbl = (void**)(*po);
		// 간접 지정 연산자를 이용해 포인터의 포인터를 얻어냄
		// 포인터의 포인터가 virtual table 포인터임
		void* pfn = (void*)pvtbl[0];
		// virtual table 에서 첫번째 값을 얻어내서 pfn 에 대입
		// 즉 C 를 대입한거임

		FP fp;
		memcpy(&fp, &pfn, 4);
		// 그리고 pfn 에 들어있는 주소값을 fp 에 대입
		// 정상적인 방법으로는 값이 복사가 되지 않아서 memcpy 사용함 

		(this->*fp)(); // x64 에선 결과가 나오지 않음

		// x64 에선 메모리 크기가 sizeof(int) * 2 이기 때문
	}

	virtual void C()
	{
		printf("KBase::C()\r\n");
	}
	virtual void B()
	{
		printf("KBase::B()\r\n");
	}
};

class KDerived : public KBase
{
public:
	virtual void C() override
	{
		printf("KDerived::C()\r\n");
	}
	virtual void D()
	{
		printf("KDerived::D()\r\n");
	}
	void E()
	{
		printf("KDerived::E()\r\n");
	}
};

void main()
{
	KDerived a;
	a.A();
}

// 컴파일러는 virtual 함수들의 동적 바인딩을 위해서
// 각각의 데이터 타입에 대한 virtual 함수를 가진
// table 을 하나씩 만듬
// KBase 에 대해서 virtual 함수만을 가진 table 을 만들고
// KDerived 에 대해서도 하나 만듬