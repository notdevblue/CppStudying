#include <stdio.h>

template <typename T>
struct PTS {
    enum {
        IsPointer = 0,
        IsPointerToDataMember = 0
    };
}; // struct PTS
// 어떤 타입이 포인터인지 아닌지 판단하는 클레스.
// 어떤 타입이 void 인지 상속을 받는지 등등을 판단할 수 있는 구현된 클레스를 Type traits 라고 한다고 함
// 이런 원리로 구현되었다고 함

template <typename T>
struct PTS<T*> { // 기존의 타입 T 를 유지하면서 이 타입이 포인터인 경우 두번째 struct 를 이용해 특화가 일어남
    enum {
        IsPointer = 1,
        IsPointerToDataMember = 0
    };
}; // struct PTS
// char* 를 사용하면, PTS 와 PTS<T*> 를 둘다 사용이 가능함
// 이런 경우에는 partial ordering 이라고 해서 좀 더 특화된 버전을 사용한다는 규칙이 있음
// char* 를 사용하면 좀 더 적합한 버전인 PTS<T*> 를 사용

template <typename T, typename U> // 테이터 멤버에 대한 포인터를 지정하기 위해선, 클레스 타입이 필요하게 됨, U 가 필요하므로 추가적인 파라미터를 받도록 U 지정
struct PTS<T U::*> { // 어떤 데이터타입 T 인데 그것은 U 에 대한 멤버 를 가리키는 포인터
    enum {
        IsPointer = 0,
        IsPointerToDataMember = 1
    };
};

struct S {};

int main() {
    S s;
    S* pS;
    int S::*ptm;
    // int S::*ptm 는 S 구조체 안의 int 형 변수를 가리키는 포인터임
    // class A {public: int num; int num2; };
    // int A::*ptr = &A::num;
    // int A::*ptr2 = &A::num2;
    // A obj;
    // obj.*ptr = 2;
    // printf("%i\r\n", obj.num); // output: 2
    // 이렇게 사용함
    // 클레스 시작 주소에서의 offset 으로 구현되어있음
    // ptr 은 시작 주소부터 0 바이트 이동하고,
    // ptr2 는 시작 주소부터 4 바이트 이동함

    printf_s("PTS<S>::IsPointer == %d PTS<S>::IsPointerToDataMember == %d\n",
             PTS<S>::IsPointer, PTS<S>::IsPointerToDataMember); // output: 0 0

    printf_s("PTS<S*>::IsPointer == %d PTS<S*>::IsPointerToDataMember == %d\n",
             PTS<S*>::IsPointer, PTS<S*>::IsPointerToDataMember); // output: 1 0

    printf_s("PTS<int S::*>::IsPointer == %d PTS<int S::*>::IsPointerToDataMember == %d\n",
             PTS<int S::*>::IsPointer, PTS<int S::*>::IsPointerToDataMember); // output: 0 1

    return (0);
}