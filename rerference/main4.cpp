#include <stdio.h>

int g_age = 154;

class KTest
{
public:
	KTest() : age(g_age), hp(0.0f) // member initializer list
	{
		//age = g_age;
		// 이것은 대입문이기때문에 불가능
		// 위위처럼 멤버 이니셜라이저로 초기화해줘야함

		//hp = 0.0f; // 일반 변수는 이거도 가능
		// 하지만 c++ 표준은 member initializer 를 사용하는 것을 권장하고 있음
	}

	KTest& Print(int i)
	{
		printf("%i\r\n", i);
		return *this;
	}

	KTest& Print(float f)
	{
		printf("%g\r\n", f);
		return *this;
	}

	KTest& Print(const char* msg)
	{
		printf("%s\r\n", msg);
		return *this;
	}
private:
	int& age;
	// 클레스 내부에서 age 값을 레퍼런스로 선언하고 싶음.
	// 그리고 외부에 이미 존재하는 값으로 age 를 선언하고 싶음
	//int& age = g_age;
	// c++ 14 전에는 이것 불가능했음
	// 하지만 멤버 변수로 선언할 때는 초기화 하지 않아도 됨.
	int& age;
	// 하지만 레퍼런스는 선언되면서 초기화되야됨
	// 문재가 발생함.
	// 생성자에서 이 레퍼런스 멤버 변수를 반드시 초기화해줘야함
	// 클레스에 선언된 레퍼런스 멤버는 생성자에서 초기화한다면 가능함

	float hp;
};

//void Test(int& i)
//{
//	i += 1;
//	// 만약 3 이라는 상수가 전달되었을 경우,
//	// 3 이라는 상수값을 1 증가시키려고 시도한다는 의미
//	// 상수 표현식은 레퍼런스로 받을 수 없음
//}
void Test(const int& i)
// 컴파일러는 i 가 읽기 전용으로 전달된 레퍼런스라는 것을 암
// 내부에서 i 값 바꾸려는 시도를 하는 경우 컴파일 에러가 발생
// 
{
	//i += 1;
}

int main()
{
	int i = 1;

	int& j = i;
	// 변수를 선언할 때 레퍼런스로 선언할 수 있음
	//int& j = i;
	// 레퍼런스 선언의 특징 때문에 레퍼런스를 선언할 때 변수를 초기화하지 않고 쓰는건
	// 불가능함
	//j = i;
	// 선언되고나서 대입 또한 불가능함

	j += 1;
	// j 는 i 에 대한 레퍼런스이므로 j 는 i 값을 1 증가시킴


	KTest t;
	t.Print(i).Print(1.54f).Print("Hello");

	int k = 3;
	Test(k);
	//Test(3);
	// 3 이라는 상수 표현식은 주소를 구할 수 없음
	// Test 함수가 int 의 레퍼런스를 구하려고 하는데
	// 내부적으로는 매개변수의 주소를 구할 수 있어야 함
	// 하지만 3 은 상수 표현이므로 주소를 구할 수 없는 표현식


	Test(3);
	// 만약 const reference 인 경우 값이 변경되지 않는다는 보장이 되기 때문에
	// 이 3 이 내부에서 변경이 되지 않을 것이므로 비록 주소가 없는 상수 표현식이지만
	// const reference 로 전달하는 것이 가능함.
	// 실질적으로 컴파일러는 이런 표현식을 메모리 어딘가에 할당하고,
	// 시작 주소를 리턴하는 식으로 구현되있을 것
	// 일반적으로 readonly 목적으로 변수를 받는다면 const type& 으로 받도록 설계
	// 


	return(0);
}