// C++ 새로 추가된 타입 케스팅 연산자

// const_cast<T>(expression)
// const 로 선언된 expression 에 const 를 버릴려면 const_cast 사용
// reinterpret_cast<T>(expression)
// 완전히 연관되지 않은 두 타입 사이의 변환이지만 값을 유지하고 싶을 때 reinterpret_cast 사용
// 관계 없는 타입이지만 컴파일 타임 에러를 피하고 싶다면 reinterpret_cast 사용

// 이 두개 설명
// static_cast<T>(expression)
// C 스타일 casting 사용하지 말고 static_cast 사용
// 연관 없는 타입에 대해 Compile time error 발생
// int 로 저장되었지만 float 로 해석해야하는 경우가 있음
// 그때는 reinterpret_cast 사용 (내가 해석할테니 컴파일러는 신경쓰지 마라)
// dynamic_cast<T>(expression)
// 대상이 상속 관계에 있는 down, cross casting 인 이라면 static_cast 대신 dynamic_cast 사용

#include <stdio.h>

class KTest {
public:
    void Print() {
        printf("KTest::Print()\r\n");
    }
};

class KHello {
public:
    void Print() {
        printf("KHello::Print()\r\n");
    }
};

int main() {
    KTest* t = new KTest;

    // 지금은 명확하기 때문에 그럴 일은 없지만
    // 실제로는 개발자의 실수로, 또는 환경이 허락하는 것 같아서 아레와 같은 casting 을 하는 경우가 있음
    // KHello* p = t; // 물론 타입이 달라서 안됨
    // 하지만 C 스타일 casting 을 사용하면 가능
    // KHello* p = (KHello*)t;
    // 억지로 KHello 타입으로 casting 후 p 에 대입

    // p->Print();
    // 놀랍게도 빌드가 가능하고 KHello 의 Print 가 호출됨
    // 내부에서 어떤 멤버를 접근하지 않으니 이상 없이 실행
    
    // 하지만 만들어지지도 않은 객체의 멤버 함수를 실행하는 아주 위험한 상황임
    // 이렇게 C 스타일의 casting 을 사용하면 디게 위험하게 됨
    // 그래서 새로운 C++ type casting 연산자가 생김
    // static_cast 를 사용해 캐스팅을 시도
    // KHello* p = static_cast<KHello*>(t);
    // 이제 빌드 시도하면 컴파일 타임 에러가 발생함
    // 컴파일러는 t 의 데이터 타입이 KTest* 이고, 캐스팅 하려는 데이터 타입이 KHello* 
    // 둘 사이 아무런 관계가 없으므로 타당하지 않은 캐스팅으로 인식
    // 연관되지 않은 포인터 사이 타입 케스팅을 c++ 의 static_cast 으로 막을 수 있음
    // 고로 c++ 사용 시 항상 static_cast 사용

    delete t;
    return (0);
}