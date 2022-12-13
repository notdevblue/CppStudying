#include <stdio.h>

#define REF
#define IN
#define OUT
// 아레쪽 메모에서 말한 메크로

//void Swap(int a, int b) // call by value. a 와 b 의 값이 새로운 메모리에 복사됨
// c 에는 call by reference 라는 기능이 없음
// int* a 는 pointer 를 전달하는 것이니 call by value
// (굳이 말한다면 call by pointer 하지만 language 개념이 아닌 os 와 밀접하기 때문에 이런 말은 사용하지 않는게 좋음)
// c++ 에선 값을 전달했을 때
// 어떤 특정한 내부 연산을 하지 않아도, 나는 Swap 함수에서 변경된 값을
// Swap 함수가 리턴되었을 때 유지하고 싶다.
// 함수 안에서 값이 바뀌었을 때 유지하고 싶다.
// 라고 명시할 수 있음
// 프로그래머가 특별한 처리를 하지 않았기 때문에 컴파일러가 자동으로 코드를 생성함
// 이런 기능을 Call by reference 라고 함
void Swap(int& a, int& b) // call by l-value reference
// call by reference 를 구현하기 위해선 c++ 의 새로운 연산자인
// ampersand (&) 를 타입 이름과 변수명 사이에 적어주면 됨
// 여기서 전달된 값은 call by reference 로 전달되었기 때문에 함수를 빠져나와도 유지됨
{
	int t = a;
	a = b;
	b = t;
}

int& AccessInt()
// Reference 를 리턴한다면 read, write 가 가능하기 때문에
// Get, Set 이라는 말 보단 다른 키워드를 사용하는게 좋음
// Get 이라고 하면 꼭 읽는 목적으로만 사용되는거 같으므로 이름 관례를 따라주는게 좋음
// 교수님은 Access 라고 쓰신다고 함. Access 의 의미를 Read Write 가능하다는 의미
//{
//	int i = 1;
//	return i;
//}
{
	static int i = 1;
	printf("%i\r\n", i);
	return i;
}
// (아레 AccessInt() = 3) 일반적으로 이런 구현은
// 함수를 빠저나갔을때에도 변수가 유지되야 하므로
// 내부에서 static 변수를 관리하는 것
// 그러면 내부에서 관리하는 이 static 변수에 값을 리턴하는 연산을 함
// AccessInt() 가 static 변수의 레퍼런스를 리턴하므로
// 함수를 빠져나왔을때, 블럭 외부에서 변경하는게 가능한 것
// 레퍼런스를 리턴하는 함수를 쓸땐 전역 변수를 리턴하든지, static 변수를 리턴하는 방식으로 구현을 해줘야 함


class KTest
{
	// 이렇게 모든 타입에 대해 print 를 해 주는 helper class 라고 가정
public:
	//KTest Print(int i)
	//{
	//	printf("%i\r\n", i);
	//	return *this;
	//}
	//// 문제 없음. 동작함.

	//KTest Print(float f) // overloading
	//// 파라미터 타입, 갯수가 다르다면 오버로딩 할수있음
	//{
	//	printf("%g\r\n", f);
	//	return *this;
	//}

	//KTest Print(const char* msg)
	//{
	//	printf("%s\r\n", msg);
	//	return *this;
	//}


	//KTest& Print(int i)
	//{
	//	printf("%i\r\n", i);
	//	return *this;
	//}

	//KTest& Print(float f)
	//{
	//	printf("%g\r\n", f);
	//	return *this;
	//}

	//KTest& Print(const char* msg)
	//{
	//	printf("%s\r\n", msg);
	//	return *this;
	//}
	// 이렇게 되면 객채가 복사되지 않고, 내부적으론 포인터만 전달할 것
	// 오버해드 없이 계속해서 Print 함수를 호출할 수 있음
	// 맴버함수가 객채의 레퍼런스를 리턴할 때
	// 이럴때 일반적으로 많이 씀

	KTest& operator()(int i)
	{
		printf("%i\r\n", i);
		return *this;
	}

	KTest& operator()(float f)
	{
		printf("%g\r\n", f);
		return *this;
	}

	KTest& operator()(const char* msg)
	{
		printf("%s\r\n", msg);
		return *this;
	}	
	// 좀더 보기 좋게 하기 위해 operator 를 오버로딩 함
	// 여기서 함수 이름은 operator 라고 할 수 있음
private:
	//int age = 0;
};

int main()
{
	int a = 2;
	int b = 3;
	//Swap(a, b);
	// Swap 을 호출했을 때 a, b 가 call by value 인지 call by reference 인지 알 방법이 없음
	// C# 엔 ref 키워드가 있긴 함
	// 하지만 C++ 에선 선언한 쪽에서만 reference 심볼만 명시하면 됨
	// 그래서 개발팀에 들어가면 이런 것들을 해결하기 위해 메크로같은걸 정의해서 씀
	// Swap 의 a, b 는 전달하는 값의 의미가 있음. 그리고 안에서 값이 바뀌게 됨
	// 이런 파라미터는 in out 파라미터가 되는 것
	//Swap(IN OUT a, IN OUT b);
	// 그래서 아무 의미가 없는 IN OUT 을 정의한 다음
	// 파라미터로 a 를 전달할 때 이렇게 명시함
	// 이러면 a 는 IN OUT 파라미터구나, 들어갈 때도 의미 있는 값이고, 값도 바뀌어서 나오는구나
	// 라고 알 수 있는 것 
	// 값을 받는 것만 목적이라면 Swap(OUT a);
	// 이렇게 보통 쓴다고 함. 이러면 코드를 읽기 좋게 만듬

	// Swap(int& a, int& b) 의 & 를 주소 연산자와 해깔리지 않도록 해야 함
	
	//&a;
	// 는 타당한 표현식, a 의 주소 라는 뜻, 에러 발생 안함
	// 이때의 ampersand 는 address-of operator
	// 하지만 변수로 선언할 때의 ampersand 는
	// 이것은 call by reference 로 전달된 파라미터라는 의미

	//printf("%i, %i\r\n", a, b);


	//AccessInt() = 3;
	// AccessInt() 를 호출하고, 함수가 레퍼런스를 리턴하므로,
	// 이 값을 변경하려는 시도가 가능함 
	// 아무 문제 없음
	// 하지만 이 상황은 아주 위험한 상황임
	// AccessInt 가 return 하는 i 는 
	// AccessInt 가 호출되었을 때 stack 에 할당된 변수임
	// 컴파일러는 내부적으로 이 stack 에 할당된 변수의 시작 주소로 레퍼런스를 관리
	// 하지만 그 메모리는 stack 에 없는 상황
	// 고로 타당하지 않은 메모리를 접근하는 상황
	// (reference 2, 3 강의 내용. 함수 종료 시 display 읽고 stack 에서 pop 하기 때문)
	// 그래서 레퍼런스를 리턴할 때는 임시 변수, stack 에 할당된 변수에 대해선 레퍼런스를 리턴하지 않아야 함

	//AccessInt();
	// 위에서 리턴된 레퍼런스에다 3을 대입하였기 때문에 3이 출력됨

	KTest t;
	//t.Print(a);
	//t.Print(3.14151f);
	//t.Print("Install Gentoo");

	// 하지만 Print 를 연속적으로 사용하고 싶음.
	// t.Print(1).Print(154.1f).Print("Wa sans");
	// 이러면 Print 호출이 객채를 return 해 줘야 함
	// 그렇게 하려면 Print 가 this 를 리턴하면 됨

	//t.Print(a).Print(3.141519f).Print("Proceed Linux From Scratch.");
	// 지금 t 의 Print 가 객체를 리턴하는데
	// 이 객채가 값으로 리턴됨
	// 계속해서 객채가 복사되는 상황이 일어난다는 의미
	// Print 함수가 쭉 호출되면 될수록 비효율적임
	// 이럴때 레퍼런스를 리턴하도록 할 수 있음.


	//t.operator()(a).operator()(1.54f).operator()("Uninstall Windows");
	// 하지만 operator 는 이렇게 explicit 으로 쓰려고 만든게 아니고
	// 함수 이름 대신 쓰려고 만든 것.
	// t.operator()(a) 연산에서 괄호 열고 닫고가 있으므로
	// t(a); 가 가능하고, 괄호 열고 닫고는 KTest 를 리턴하므로, 연속적으로 괄호 열고 닫고 가능
	t(a)(2.25f)("um");
	// 미친 세상에
	// 무튼 이럴때 래퍼런스를 리턴하는 함수를 씀

	// 연산자 오버로딩은 나중에 설명하신데요.

	return(0);
}