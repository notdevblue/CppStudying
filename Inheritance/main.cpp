#if false

#include <stdio.h>

// KTest 타입의 객채를 만들었을 때,
// A 함수는 호출할 수 있지만,
// B 와 C 함수는 호출하지 않도록 하고 싶음
// 그때 쓰는 것이 Access Modifier

// C 는 Label 말고 Section 문법을 가짐
// Label
// public void D() { }
// Section
// public:
//     void D() { }

class KTest
{
public: // access modifier. private, protected, and public
// public 섹션의 시작.
// 그다음 Access Modifier 를 만나기 전까지
// 모든 것들을 해당하는 섹션의 엑세스 레벨로 처리함
	void A() { }


	void SetAge(int _age) { // writer helper function
		age = _age;
	}
	int GetAge() { // reader helper function
		return age;
	}
	// 일반적으로 경우의 멤버 변수가 private 영역에 선언되면 
	// 멤버 변수에 접근하는 헬퍼 함수들이 존재함

private:
	void B() { }
	void C() { }

	// B 하고 C 는 객채가 만들어졌을 때 호출하지 않도록 하고 싶음
	// 그럴때 private: 으로 선언

	// 클레스를 설계할 때 클레스 내부에서만 사용될 함수들은 private 영역에 두고
	// 객채가 만들어지고 외부에서 호출할 수 있는 함수들은 public 영역에 두는 것
	// 여기서 주의할 점은 외부에서 호출할 수 없는 함수들은 private 영역에 둠
	// 그래도 A 함수 내부에서 B 함수를 호출할 수 있음
	// 왜냐하면 클레스 내부에서는 자기 자신이기 때문에
	// 모든 것들을 Access modifier 와 관련 없이 호출이 가능함
	// B 에서 역시 A, C 를 호출할 수 있음
	
	// 일반적로 클레스 내부에서 사용되는 함수들은 private 영역에 두고

private:
	int age;
	// 데이터 멤버는 private 에 둠
	// 바로 접근해서 변경하는걸 막기 위함

	// private 나 public 을 써서 interface 나 변수를 보호하는 것을
	// Encapsulation 이라고 함
	// 이를 구현하는 대표적인 방법이 Access modifier 를 사용하는 것

	// + private 에 정의된 것들은 KTest 에서만 사용이 가능함
	// 상속받더라도 접근할 수 없음
	// 이렇게 객채를 보호할 수 있음

protected:
	int P() { }
	// 상속 받은 클레스에선 접근해도 되지만, 객체에선 접근할 수 없다 라는 의미로
	// 선언을 하고 싶을 때 protected 를 사용
	// KTest 를 상속받은 곳에서는 P 를 호출할 수 있음
	// 하지만 객체에선 호출할 수 없다는 의미
};

// 클레스를 설계하다 보니
// 이미 존재하는 클레스의 모든 interface 를 사용하면서
// 새로운 클레스를 설계해야 한다고 가정
// 예를 들면 이미 존재하는 KTest 라는 class 가 있는데,
// 새로운 KTest2 를 만들어야 하는데
// KTest2 는 KTest 의 기능을 모두 포함해야 하는 것
// 이런 public 함수들과 private 함수들과 age 를 포함해야 하는 것
// 그런 경우에 상속을 쓸 수 있음

class KTest2 : public KTest // 상위 클레스, KTest 를 Base class 라고 함
// 콜론 적고 엑세스 모디파이어를 적은 다음 베이스 클레스를 적음
// 이러면 상속을 구현할 수 있음
// 이제 KTest2 클레스는 KTest 에 정의된 모든 함수들을 자체적으로 정의하게 됨
// 그리고 추가적으로 함수나 변수 선언을 가질 수 있음
// KTest2 에 선언된 멤버 함수의 겟수는 A, SetAge, GetAge, B, C, 그리고 D 총 6개,
// 멤버 변수는 age 와 hp

// 이렇게 클레스를 정의할 때 기존에 정의된 모든 클레스의 기능을 가져오면서
// 클레스의 기능을 확장하는 것을 상속이라고 함
// 상속을 하기 위해선 Base class 를 상속받아야 함
// KTest2 는 KTest 를 상속받는다 라고 말함
// 이때 KTest 를 base class
// 상속받은 KTest2 를 derived class 라고 함
// 
// base class 를 상속받을 때 public 이 의미하는 바는
// KTest 의 Access modifier 성질을 그대로 유지하겠다는 의미
// KTest2 입장에서 기존의 public 함수들은 public, private 은 private 으로 상속받음
// 하지만 KTest2 에서 KTest A, SetAge, GetAge 같은 public 의 함수들을 내부에서 사용하지만, 외부에서는 사용하고 싶지 않을 때,
// private 으로 상속받게 되면 이렇게 적용됨
// class KTest2 : private KTest 로 쓰면
// 클레스 내부에서는 사용하겠지만
// 클레스가 만들어지고 나선 아무도 KTest interface 는 아무도 보지 못한다는 의미
{
public:
	void D() { P(); /*B(); 는 private 이기 때문에 접근 불가능*/ } // P 는 protected 이므로 접근할 수 있음
private:
	int hp;
};
// 이렇게 private, protected, public 을 통해 Encapsulation 을 구현함

void main()
{
	KTest t;
	t.A();
	// 이렇게 외부에서 호출하기 위해선 public section 안에 있어야 함

	//t.B();
	// private 멤버 함수이기 때문에 외부에서 호출할 수 없음.
	//t.C();

	//t.age; // private 멤버이기 때문에 접근하기 위해선
	t.SetAge(154);
	t.GetAge();
	// 를 통해 접근, 이를 Helper function 이라고 함


	KTest2 t2;
	t2.A();
	t2.SetAge(155);
	t2.GetAge();
	// Base class (KTest) 에 정의된 함수 를 접근할 수 있음
	// 만약 private 으로 상속받은 경우 접근 불가능함
	t2.D();
	// KTest2 에만 정의된 함수에도 접근할 수 있음
	
	//t2.P();
	// protected 이므로 접근 불가능
}

#endif