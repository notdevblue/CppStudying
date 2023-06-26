#if false

#include <stdio.h>

class KTire
{
public:
	float radius;
};


class KCar
{
public:
	void Move() {
		printf("KCar::Move()\r\n");
	}

private:
	KTire tire[4];
};

class KWing
{
public:
};

class KDriver
{
};

class KSportCar : public KCar
{
public:
	KSportCar() : wing(nullptr), driver(nullptr)
	{
	}
	~KSportCar()
	{
		delete wing;
	}

	//void Move(int i) {
	// 이러면 기존의 Move 를 오버로딩한것처럼 보임
	// 하지만 컴파일하면 그렇게 되지 않음
	// 파라미터가 다르더라도 Move() 호출은 기존의 base 클레스의 Move 를 재정의한 것 이 됨
	// 오버라이딩 되게 됨
	// 하지만 일반적으로는 base 클레스와 똑같은 파라미터를 사용함
	// 만약 오버라이딩 하는데 base 클레스와 다른 파라미터를 사용해야 한다면
	// 이것도 클레스를 잘못 설계했을 확률이 높음
	// 코드를 해깔리게 만들기 때문에 사용하지 않는 것이 좋음
	void Move() { // override

		// 관례적으로는
		// 이미 정의된 KCar 의 Move 의 기능을 확장하기 때문에
		// 일반적으로 KCar::Move() 호출함
		//Move(); 이러면 재귀 호출, 무한루프가 됨
		KCar::Move();
		// BaseClass::Function(); 으로 호출 가능

		// 만약 이렇게 설계할 필요가 없다면 교수님 피셜
		// 클레스 잘못 설계했을 확률이 높음

		printf("KSportCar::Move()\r\n");
	}
	// 이렇게 함수 이름을 똑같이 해서 정의할 수 있음
	// 이것은 KCar 에 정의된 Move 를 사용하지 않고 나만의 Move 를 사용하겠다 라는 의미

	void Turbo() { }

	void SetDriver(KDriver* pDriver)
	{
		driver = pDriver;
	}

	void CreateAccessories()
	{
		wing = new KWing;
	}

private:
	KWing* wing;
	KDriver* driver;
};


void main()
{
	//KSportCar car;
	//car.Move();
	// 현재 구현에서는 KCar 에만 Move 가 정의되어있고,
	// KSportCar 에는 Move 가 정의되어 있지 않음.
	// 하지만 Base class 에서 정의된 Move 를
	// KSportCar 에서 같은 시그니처 (함수 파라미터 갯수와 타입을 같이 해서)
	// 함수를 정의할 수 있음
	// 그러면 Base class 에서 정의된 함수가 무시되게 됨. 이를 오버라이딩이라 함
	
	// 오버라이딩과 오버로딩은 다름
	// 오버로딩은 함수의 이름이 같더라도 파라미터의 갯수나 타입이 다르다면
	// 같은 이름의 함수를 사용할 수 있는 것

	// 오버라이딩은 상속에서의 Base class 에서 정의된 멤버 함수를 재정의 하는 것


	//car.KCar::Move();
	// 이렇게 하면 KCar 에서 정의된 Move 를 호출하게 됨
	// 이것이 가능하더라도 이렇게 사용하는것은 좋지 못함
	// Move 를 오버라이딩한 이유는, KSportCar 에 정의된
	// Move 를 호출하라는 의도
	// 만약 객채를 만들고 이렇게 호출해야 하는 일이 있다면
	// 이는 클레스를 잘못 설계한 것
	// 하지만 문법적으로는 가능


	//KCar car2;
	//car2.Move();
	// car2 는 KCar 타입이기 때문에 KCar::Move 를 호출함

	// 하지만 객채를 동적으로 만든다면 문제가 생기는 상황이 생길 수 있음
	//KSportCar* pCar = new KSportCar();
	//pCar->Move();
	//delete pCar;
	// pCar 의 데이터 타입이 KSportCar 이므로 KSportCar::Move 가 호출

	// 하지만 이러면 어떻게 될까?
	KCar* pCar2 = new KSportCar();
	pCar2->Move();
	// 왜이렇게 받지 할수있지만 대부분 이렇게 받는데요
	// 이렇게 사용하는 이유는 나중에 설명한데요
	// 컴파일러가 코드 생성 결정 과정을 보면
	// 생각해보면 만들어진 객채 타입이 KSportCar 이므로
	// 이 Move 는 KSportCar 의 Move 를 호출하는 것이 바람직함
	// 하지만 컴파일러는 Move 호출을 결정하기 위해서 pCar2 의 데이터 타입을 봄
	// pCar2 의 데이터타입이 KCar 이므로 KCar::Move 가 호출됨

	// 바람직하지 않는 상황이 일어남
	// 비록 KCar 타입의 포인터이지만 만들어진 객채가 KSportCar 이므로
	// KSportCar 의 Move 를 호출하는 것이 바람직함
	// 그것이 virtual 임
	// 이 키워드 설명하는 곳에서 별도로 설명한데요...

	delete pCar2;
}

#endif