#if false

#include <stdio.h>

class KBase
{
public:
	~KBase() {
		printf("KBase::~KBase()\r\n");
	}

	void Test1() {
		printf("KBase::Test1()\r\n");
	}

	virtual void Test2() {
		// Test2 함수의 호출이 있다면 이 함수의 바인딩을 실행 시간까지 늦추어라 라는 의미
		// 어떤 함수가 virtual 이 되면, 하위 클레스에서 특별하게 virtual 키워드를 붙혀주지 않아도
		// virtual 함수가 됨
		// 관례상 상위 클레스와 똑같은 함수를 오버라이딩 했다면 붙혀주는게 맞음
		printf("KBase::Test2()\r\n");
	}
};

class KDerived : public KBase
{
public:
	~KDerived() {
		printf("KDerived::~KDerived()\r\n");
	}

	virtual void Test2() override {
		// virtual 뺴줘도 문제 없음
	// virtual void Test2(int a) {
		// Test2 는 오버로딩 된 상태
		// KDerived::Test2(); 를 호출하면 KBase::Test2 가 호출되기 때문에
		// 에러가 발생하지 않음
		// 아주 바람직하지 않은 상태임
		// c++14 에선 위와같은 잘못된 virtual 함수 사용을 막는
		// override 라는 키워드가 추가됨
		// 상위 클레스의 함수를 오버라이드 했을때 이 함수는 오버라이드 됬다고 명시
		// override 로 정의된 어떤 가상함수의 상위 클레스와 다른 시그니처를 써서 
		// 오버라이딩 하려고 하면 컴파일 에러가 발생함

		printf("KDerived::Test2()\r\n");
	}

	void Test3() {
		printf("KDerived::Test3()\r\n");
	}
};

void main()
{
	//KBase*		pa;
	KBase*		pb;
	//pa = new KBase();
	pb = new KDerived();
	// 이것을 subtype principle 이라고 함
	// 원레 타입이 와야 하는 자리에 서브 타입 (KBase 를 상속받은 타입) 이 올수 있다는 걸
	// 서브타입 원리라고 함
	//KDerived* pc = new KBase(); // unsafe down casting
	// 다운케스팅은 안전하지 않기 때문에 컴파일 안됨
	// 하지만 케스팅 연산자 사용하면 가능함

	// drived 클레스의 포인터를 base 로 대입하는건 가능
	// 업케스팅 이라고 함 (안전함)

	// base -> derived 는 위험하기 때문에 되지 않음
	// 다운케스팅 이라고 함
	//pa->Test2();
	pb->Test2();
	// 함수 호출 결정을 컴파일 시간이 아닌 실행 시간으로 늦추는 걸 late binding 이라고 함
	// 실행 시간에 함수의 주소가 바인드 된다는 의미
	// 그렇게 해주는 키워드가 virtual

	//delete pa;
	delete pb;
}

#endif 