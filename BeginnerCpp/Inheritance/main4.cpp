#include <stdio.h>

class KCar
{
public:
	KCar() {
		printf("KCar::KCar()\r\n");
	}

	~KCar() {
		printf("KCar::~KCar()\r\n");
	}

	void Move() {
		printf("KCar::Move()\r\n");
	}
};

class KSportCar : public KCar
{
public:
	KSportCar() {
		printf("KSportCar::KSportCar()\r\n");
	}

	~KSportCar() {
		printf("KSportCar::~KSportCar()\r\n");
	}

	void Move() {
		printf("KSportCar::Move()\r\n");
	}
};
// KSportCar 는 KCar 의 기능들을 이용하기 때문에
// 객채가 생성될 때
// KCar 의 생성자가 실행이 되고, 그 다음의 KSportCar 의 생성자가 실행이 됨
// KCar 타입의 객채를 초기화 하고 나서, 그 다음에 KSportCar 타입의 객채를 초기화
// 실행 순서는 base -> derived

// 하지만 호출은 derived -> base
// derived 생성자를 호출하고
// derived 의 생성자 초기화 리스트에서 base 생성자를 호출하고
// base 생성자를 실행한 다음 derived 생성자를 실행함

// 파괴자는 반대의 순서
// derived -> base 로 실행

void main()
{
	//KSportCar car;
	//car.Move();

	//KCar car2;
	//car2.Move();
	// 예는 자기꺼만 호출
	// 정상임

	//KSportCar* pCar = new KSportCar();
	//pCar->Move();
	//delete pCar;
	// 예도 잘 호출됨

	KCar* pCar2 = new KSportCar;
	// 일반적으로 객채들을 관리할때 컨테이너에 같은 타입을 관리해야 하기 때문에
	// 비록 생성된 것은 KSportCar 타입의 객채라도
	// 포인터가 Base class 의 포인터로 관리될 때가 많음
	pCar2->Move();
	delete pCar2;

	// KSportCar 를 생성한 것이기 때문에 생성자는 잘 호출
	// 하지만 KSportCar 의 파괴자는 호출되지 않음
	// 왜냐하면
	// delete pCar2 가 메모리를 해제하기 전에 pCar2 의 파괴자를 호출함
	// 컴파일러는 pCar2 의 데이터 타입을 KCar 로 확인하고,
	// 이 객채는 KCar 의 데이터 타입이라고 판단
	// 그래서 pCar2 에 대해선 KCar 의 파괴자만 호출함
	// 엄청 문제가 심각해지는 상황
	// 다음 강의에 설명...
}