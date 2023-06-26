#include <stdio.h>

#if false

void Test(const char* msg)
{
	//msg[0] = 'S'; // const 넣으면 에러 떠요
	// 이렇게 바꾸려고 해도 에러가 발생하지 않음
	// + 읽기 힘들게 만듬
	// 그래서 Test 함수를 정의할 때 msg 는 출력 전용이므로 건들이지 마라 라고 명시하는것이 필요
	// 그게 const 임
	// 그래야 프로그램에서 이것은 읽기 전용 코드이구나 라고 문서화가 되는 것이고
	// 혹시나 실수로 값 접근하려고하면 컴파일 에러가 나서 미연에 막을 수 있음
	// 그래서 const 를 사용함
	printf("%s\r\n", msg);

}
// 이 코드를 읽는 프로그래머 입장에서 보면,
// 메세지를 포인터로 전달함
// 그러면 포인터 값으로 전달하니 메세지 값을 바꾸는 것이 가능
// 그러면 이 값을 바꿀려고 전달을 했는지, 출력하는 목적으로 전달했는지 알 수 없게 됨


class KTest
{
public:
	//void Print()
	//{
	//	printf("Age = %i\r\n", this->age);
	//}
	// Print() 함수는 age 값을 변경시키지 않고, 읽기 목적으로만 사용함
	// 여기서 Print() 함수는 멤버 값을 변경시키지 않는다 라는 보장을 하고 싶음
	// 예를 들면 KTest 객채를 생성할 때 const 변경자를 붙일 수 있음
	// 그것의 의미는 KTest 타입의 객체는 읽기 전용이다 라는 의미
	// 그 말은 객채가 만들어지고 나서 객채의 어떤 값도 변경되면 안된다 라는 의미
	// 하지만 IncAge, Print 는 함수 내부에서 이 값들을 변경시키는지 알 방법이 없음
	// IncAge 는 값을 변경시키므로 호출할 수 없어야 하고,
	// Print 는 값을 변경시키지 않으므로 호출되야 함
	// 하지만 실제로 빌드하면 이 두 함수 둘다 에러 발생함
	// const KTest 에서 KTest & 로 변환 못한다는 에러 뜸
	
	// 모든 맴버함수 내부에는 this 포인터가 유지됨
	// 실제로 값 접근할 때 this->age 접근하는 코드가 됨
	// 그래서 this 포인터가 값을 변경 시키지 않는다면 멤버함수 전체가 값을 변경시키지 않는 것이 됨
	// this 함수를 const 로 선언하면 됨
	// 하지만 this 는 이미 존재하는 포인터이고, 별도로 선언할 수 없음
	// 그래서 this 는 "이 멤버함수 내부에서 상수다" 라고 선언할 수 있음
	// 그 선언을 함수 이름 다음에 붙임

	void Print() const // declare this as const
	{
		printf("Age = %i\r\n", age);
	}
	// 이러면 컴파일러는 멤버 변수, 함수 접근에 대해 값을 변경시는지 this 가 상수로 사용이 되는지 검사함
	// Print() 는 const member function 이 되는 것이고,
	
	void IncAge()
	{
		age += 1;
	}
	// IncAge() 는 non const member function 이 되는 것

	//void IncAge() const
	//{
	//	age += 1;
	//} // this->age 를 1 증가시키기 때문에 에러를 발생시킴

	// 이 두 함수의 차이점은 readonly 목적인가 아닌가

private:
	int age = 154;
};

void main()
{
	//int i = 1;
	//i = 2;
	// 변수 선언 시 readonly 목적으로 선언 가능
	
	const int i = 1;
	// 이것의 의미는 변수 i 는 메모리 할당 되었지만 readonly 목적이다. 그래서 값을 변경할 수 없다
	// 라는 의미로 const 를 사용함
	//i = 2; // 에러 발생함




	const float pi = 3.141592f;
	// 의미있는 상수들 예를들어
	// float pi 로 선언하는게 아니라
	// const float pi 로 선언
	// 그러면 이 코드를 보는 프로그래머에게 이것은 읽기 목적의 변수구나 라는 것을 명확하게 해줌
	// 그러면 혹시 값을 바꾸려고 시도하는 경우 실패하게 되고, 코드를 읽기 좋게 만듬
	// 그때 const 를 사용함
	//pi = 1.54f; // 에러 발생함

	Test("Hello"); 
	// vs2022에선 매개변수 타입이 (const char*) 가 아닐 시 오류 발생함

	//KTest t;
	//t.IncAge();
	//t.Print();

	//const KTest t;
	//t.IncAge();
	//t.Print();
	// 이 함수들이 값을 변경하는지 아닌지 모르기 때문에 에러 발생시킴


	const KTest t;
	// 객체가 변경되지 않는다는 보장이 되려면
	// t 의 모든 멤버함수 호출은 상수 함수만 호출해야 함
	// Print 는 상수함수이므로 호출 가능
	t.Print();
	// 이것은 타당함

	//t.IncAge();
	// IncAge 는 상수 함수가 아니므로 타당하지 않음
}

#endif