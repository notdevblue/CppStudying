#include <stdio.h>

class KTire
{
public:
	float radius;
};


class KCar
{
public:
	void Move() {}
	// 객채가 만들어진곳과 상속받은곳에서 호출할 수 있어야 함

private:
	KTire tire[4];
	// KCar 는 KTire 를 composition 멤버로 가짐
	// 일반적으로 데이터 멤버는 Private 영역에 두고
	// interface 를 노출함

	// KCar 는 KTire 를 반드시 가져야 하고
	// KTire 가 없이 KCar 는 존재할 수 없음
	// 이런 것은 일반적으로 멤버 데이터로 구현
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
		// 포인터는 꼭 생성시 null 로 초기화
		// 일반 변수든 포인터는 0 이나 null 로
	}
	~KSportCar()
	{
		delete wing;
		// 이렇게 작성하면 안됨, 아주 위험한 코드임
	}

	void Turbo() { Move(); }
	// Turbo 내부에서 Move 호출 가능

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
	// aggregation 관계
	// KWing 의 lifetime 는 관리하지만 없어도 되는 경우
	// 이런것들은 일반적으로 포인터로 구현함

	// 내부에서 필요하다면 KWing 을 생성하는 코드가 있을 것이고
	// 만약 필요하지 않다면 delete 하는 코드도 있을 것
	// + 대부분 그렇다는 것이지 그렇지 않을수도 있음

	// aggregation 으로 관리한다는 것의 의미는
	// 객채의 lifetime 을 KSportCar 가 관리한다는 의미

	// 그것이 포인터로 관리되든 포인터로 관리되지 않든
	// KSportCar 와 생명을 같이 한다는 의미
	// KSportCar 가 없어지면 KWing 은 존재할 수 없음


	KDriver* driver;
	// association 관계
	// 내부에서 생성하지 않음
	// 외부에서 생성되있는 KDriver 를 
	// KSportCar 가 필요한 경우 외부에서 세팅함
	// association 으로 세팅된 멤버가 포함된 경우에는
	// 인터페이스로 SetDriver 와 같은 함수가 존재하게 된다.

	// KSportCar 가 없어진다고 해서 KDriver 가 없어지는건 아님
};


// 어떤 사람들은 composition 과 aggregation 을 구분할 때
// composition 은 포인터가 아닌 객채로 만드는 것이고
// aggregation 은 포인터로 만드는 것이다
// 고로 포인터로 선언되면 aggregation 또는 association 이고
// 객채 타입으로 만들어지면 composition 이라고 알고 있음
// 대부분의 경우에 맞지만 반드시 그런건 아님
// 예를 들어 composition 이라도 포인터로 생성될 수 있음
// 그러면 객채의 생성자나 혹은 어딘가에서 무조건 객채 타입의 오브젝트들을 생성할 것
// 포인터로 관리된다고 해서 무조건 composition 이 아닌 것이 아닌
// 그 포인터가 항상 생성이 되어서 어떤 value 나 object 를 가리킨다면 그것은 composition
// 즉 포인터를 가지도록 구현했든 객채를 가지도록 구현했든
// 이는 composition 과 aggregation 을 구분하는 것이 아님
// 클레스 구현에 상관 없이 개념에 관련된 것
// 반드시 가져야 하면 composition, 없어도 되면 aggregation

void main()
{
	KDriver* pDriver = new KDriver();
	KSportCar car;
	
	car.SetDriver(pDriver);
	// 필요한 경우 호출해서 전달

	car.Move();
	car.Turbo();


	delete pDriver;
}