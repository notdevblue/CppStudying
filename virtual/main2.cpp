#include <stdio.h>

class KBase
{
public:
	// 파괴자 바인딩도 런타임까지 늦춰야 하기 때문에
	// virtual 를 붙인다
	// 어떤 클레스가 다른 클레스의 
	// base class 로 사용된다면 virtual 을 붙혀주는 것이 관례
	// virtual 붙일 필요가 없다면 잘못 설계한 것
	virtual ~KBase() {
		printf("KBase::~KBase()\r\n");

		//Test2();
		// 생성될때는 KDerived 에 대한 정보가 없음
		// 그러므로 생성자에서 virtual 함수 호출 시
		// KBase 함수의 virtual 함수를 호출함
		// 이 성질을 똑같이 유지해주기 위해서 파괴자에서도 자기 자신의 함수를 호출함

		// 일반 함수에서 호출된 Test2() 는 virtual
		// 생성, 파괴자에선 자신의 Test2() 를 호출

		// 이러한 문제를 해결하기 위해선 생성자 또는 파괴자에서 virtual 함수를
		// 호출해주지 않아야 함. 아주 문제가 되는 사항이 생길 수 있음
		
		// Template Method Pattern 패턴을 사용 시
		// interface 를 구현한 다음 함수들을 late binding 함

		DoTest2();
		// 생성자와 파괴자에선 virtual 호출하면 안된다는걸 잘 알고 있는 사람이
		// 어떠한 필요에 의해 파괴자에서 DoTest2() 를 호출하려 함
		// virtual 이 아님
		// 호출함
		// virtual 이 아니라 문제가 없다고 판단
		// 실행하니까 파괴자 호출 시점에선 Base 의 Test2() 호출됨
		// 하지만 Test2() 는 pure virtual function
		// 빌드는 정상적이지만 실행 시 오류가 발생함
		// 직접 호출한 함수가 가상함수가 아니더라도
		// 호출한 함수 내부에서 가상함수가 호출한다면
		// 문제가 발생함
		// 이를 해결할 방법은 문법적으로 존재하지 않음
		// 클레스 설계시 의미있는 함수 호출을 하지 않도록 해야 함
		// 만약 객체가 생성된 이후에 어떤 의미있는 초기화가 필요하도록 하면
		// 별도의 interface 함수를 만드는 것이 바람직
		// 생성자에선 0 같은거 대입하고
		// 따로 함수 호출해서 의미있는 초기화를 함
	}

	void DoTest2() // Template method pattern 이라고 함
	{
		Test2();
	}

	void Test1() {
		printf("KBase::Test1()\r\n");

		Test2();
		// Test2() 는 virtual 함수
		// 만들어진 객체 타입이 KBase 라면 KBase::Test2()
		// KDerived 라면 KDerived::Test2()
		// 똑같은 호출로 보이지만 실행 시간에 따라 호출되는 함수가 달라짐
	}

	//virtual void Test2() {
	//	printf("KBase::Test2()\r\n");
	//}

	virtual void Test2() = 0;
	// interface 만 가지고
	// 구현은 derived class 에서 해야 하는 virtual function 을
	// pure virtual function, 순수 가상 함수 라고 함
};

class KDerived : public KBase
{
public:
	// 하위 클레스에서는 안 붙혀도 되지만 붙히는게 관례
	virtual ~KDerived() override {
		printf("KDerived::~KDerived()\r\n");
	}

	virtual void Test2() override {

		printf("KDerived::Test2()\r\n");
	}

	void Test3() {
		printf("KDerived::Test3()\r\n");
	}
};

void main()
{
	KBase* pb;
	pb = new KDerived();
	
	//pb->Test2();

	//pb->Test1(); // KDerived 타입이기 때문에 Test1() 에선 KDerived::Test2() 를 호출함

	pb->DoTest2();
	// 실제로 호출되는 함수는 만들어진 객체 타입에 따라 달라짐

	delete pb;
	// 파괴자 호출은 
	// KDerived -> KBase 순서로 호출됨
	// 실행이 끝나는 것은 KBase -> KDerived 임
	// KDerived 함수의 실행을 끝내기 전 KBase 의 파괴자를 호출하고
	// KBase 파괴자의 실행이 끝나면 KDerived 파괴자의 실행을 끝냄
}