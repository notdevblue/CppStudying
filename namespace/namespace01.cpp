#include <stdio.h>

#include <utility> // swap 호출 용

int i = 1;
// 전역 변수 i 가 1 로 초기화됨 
// 전역 공간 (Global namespace) 에 선언된 변수

int k = 1;
// C 에선 전역변수
// C++ 에선 Global namespace 에 선언된 변수

// int i = 0;
// 위에 전역변수 i 가 선언되어있는지 모르는 사람이 전역변수 i 를 사용하려고 함
// 라이브러리 같은걸 사용할 경우 이런 경우가 생김
// 전역으로 정의되는 클레스, 함수, 변수들을 자기만의 특별한 이름 공간에 선언할 수 있음

namespace han
// 이름 공간은 namespace 이라고 적고 identifier 로 이름 공간의 이름을 주고
// bracket 으로 감싸줌
{
    int i = 154;
    int k = 2;
    // han 이름공간 안에 전역변수과 같은 이름을 가진 변수를 선언하는것이 가능함
    // 전역변수지만 han 이라는 namespace 안에 선언된 변수

    // namespace 안에 class 도 정의할 수 있음
    class KTest
    {
    public:
        void Print()
        {
            k += 1;
            // han namespace 에 있는 k 를 접근함

            // i += 1;
            // KTest::i 를 접근함

            ::i += 1;
            // 어떤 이유에서 Global namespace 의 정의된 i 를 접근해야 할 때
            // 이렇게 접근함

            han::i += 1;
            // han 에 정의된 i 를 접근함

            printf("KTest::Print()\r\n");
        }
        static int GetInt() { return i; }
        // static member 를 접근하니 static int () 로 선언이 가능

    public:
        static const int i = 3;
        // 객채가 만들어지는 안만들어지는 접근 가능
    };

    class KDerived : public KTest
    {
    public:
        // void Print() // override
        // {
        //     printf("KDerived::Print()\r\n");
        // }


        void Print(int i) // using KTest::Print 를 작성한 경우에는 overload, 안 했다면 override
        {
            printf("KDerived::Print()\r\n");
        }
        // base class 에 정의된 Print 를 override 했기 때문에 base::Print() 는 없다고 간주되고
        // derived.Print() 를 호출 시 해당하는 함수가 없기 때문에 에러 발생
        // override 한 경우에는 상위 클레스의 함수가 완전히 무시됨

        // 기존의 함수를 override 가 아닌 overload 하는 방식으로 가고 싶을 때가 있을 수 있음
        // base 와 derived 의 Print 함수를 다 사용하고 싶지만
        // derived 에서 같은 이름의 함수를 사용하게 되면 자동으로 overriding 이 되어 불가능함
        // 이때도 using 을 사용함
        using KTest::Print;
        // KDerived 에선 KTest 의 Print 도 사용하겠다 라는 의미
    };
}
// 문장이 아니기에 세미콜론을 안 찍어줘도 됨
// 찍어주면 empty statement 로 해석이 될 것
// 문제는 없지만 안 찍어주세요..


namespace han
{
    int j = 4;
    // int i = 0;
    // redefinition of int han::i
}
// namespace 는 클레스가 할 수 없는 이미 정의된 namespace 에 새로운 요소를 추가할 수 있다는 것
// 위에 이미 han 이라는 namespace 가 정의되어있지만, 다시 한번 더 정의해서 추가적으로 요소를 추가할 수 있음
// C# 은 partial class 가 있지만 C++ 은 지원하지 않음
// 이렇게 확장할때 이미 정의된 변수를 선언하는건 불가능

using namespace han;
// han 이라는 이름공간을 이 문장 아레로 활성화 시키겠다 라는 의미

// 어떤 프로젝트 환경에서 팀이 항상 han 이라는 namespace 를 사용한다고 할 때
// 이름 공간을 활성화함, han:: 을 안해도 사용할 수 있게
// 그때 using 을 사용
// using namespace 이름공간이름

// c++14 의 using 은 type aliasing 으로도 사용될 수 있음
// c++ understanding 에 나와있다고 합니다. (lambda 쪽)

// 표준 c++ library 는 표준 이름 공간을 사용함
// std 임



int main()
{
    // printf("%i\r\n", i);
    // 전역변수 i 를 출력함
    // 따로 구분이 필요하다면
    printf("%i\r\n", ::i);
    // 특별한 identifier 가 없기 때문에 콜론만 명시함
    // 

    printf("%i\r\n", han::i);
    // namespace 안의 변수를 접근하기 위해선
    // 식별자::변수 이렇게 접근함
    // han::i 는 han namespace 안에 정의된 i 를 접근한다는 의미

    printf("%i\r\n", han::KTest::i);
    // 어떤 identifier 다음에 사용된 scope resolver 를 봤을 때,
    // identifier 가 꼭 namespace 라고 가정해선 안됨
    // 위의 예제처럼 namespace 또는 class name 이 될 수가 있음
    // scope resolver 대신 . 을 사용하는 언어에선
    // object, namespace, class name 이 될 수 있음

    printf("%i\r\n", han::j);
    // 추가된 j 변수에 접근 가능

    printf("%i\r\n", j);
    // using namespace han 을 작성한 경우
    // han 의 j 를 접근 
    // 원레는 위의 han::j 처럼 접근해야 함

    // printf("%i\r\n", i);
    // han 이름공간을 활성화해서 i 는 모호함이 생김
    // i 는 global, han namespace 에 둘다 정의되어 있기 때문
    // 구분할 방법이 없음
    // 이런 경우에는 명시적으로 scope resolver 를 작성해 주어야 함
    printf("%i\r\n", ::i);
    printf("%i\r\n", han::i);

    han::KDerived d;

    // ::KDerived e;
    // han namespace 가 활성화 된 경우, 이렇게 적어도 han 안에 있는 KDerived 를 찾음 (Global namespace 에 KDerived 가 없는 경우에)

    d.Print(); // KTest::Print 호출
    d.Print(154); // KDerived::Print 호출

    // d.KTest::Print();
    // 사실 이렇게 접근할수도 있음

    // c++ 에서는 호환성을 위해 c 의 함수는 global namespace 에 정의되어 있음
    // c++ 에 추가된 표준 라이브러리는 std 이름 공간 안에 정의됨
    int a = 2;
    int b = 3;
    std::swap(a, b);

    printf("%i %i\r\n", a, b);

    return 0;
}