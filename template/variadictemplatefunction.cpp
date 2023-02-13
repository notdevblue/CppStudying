#include <stdio.h>

// variadic template 나오기 전
// BOOST_PP (boost preprocessing library 라는 것) 썻다고 함
// vs community 2013 이상에선 variadic template 

// template 의 인자를 가변적으로 받을 수 있다는 의미
// variable argument ( ... ) 내부의 parameter 가 stack 에 푸쉬되는 동작을 이용해서 구현되어있음 ( va_list va_start ) (자세한 것은 C Programming 에)

// 어떤 이유에서 template 함수나 클레스가 template type parameter 를 가변적으로 받아야 할 이유가 있음
// 

// template <typename Arg1, typename Args>
// void Func(const Args1& arg1, const Args& args) {
//     Process(arg1);
//     // ...
// }
// Func 는 뒤에 있는 type parameter 를 가변적으로 명시하고 싶음

void Process(int i) { // 1 을 처리 (Func(1, "Hello", 3.14f) 전달했으니)
    printf("%i\r\n", i);
}

void Process(const char* s) {
    printf("%s\r\n", s);
}

void Process(float f) {
    printf("%g\r\n", f);
}

void Func() {
    printf("void\r\n");
}


template <typename Arg1, typename... Args> // template argument pack
// typename 뒤에 ... 을 찍어주면 Args 는 type parameter 가 가변적이라는 것
// 이것을 template argument pack 이라고 함
// Args 는 더이상 하나의 타입이 아니므로 Args 포함한 expression 마지막에 ... 적어줘야 함
// 이 표현식은 가변적으로 받은 어떤 파라미터 타입 List 에 해당하는 가변 변수를 받는다는 뜻

// Args 가 하나의 타입이라고 생각
// 이 타입을 받은 parameter 를 선언할 때 중간에 어떤 조합이 들어올 수 있음 (아무 조합이나 가능)
// 마지막에 ... 찍어주면 가변 타입 만큼 선언하는 어떤 변수라는 그런거
void Func(const Arg1& arg1, const Args&... args) { // Args&... => function argument pack
    Process(arg1);
    // ...

    // 만약 가변인자가 없다면 void 가 됨
    // 그렇다면 void 를 받는 Func 가 필요 (재귀 호출을 막는 것)
    Func(args...); // 재귀 호출에서는 arg1 = "Hello", args = 3.14f 로 넘어감. 
    // 사용자가 가변적으로 넘어온 argument 를 전달하겠다 라는 의미
}

// Func 호출 시 타입 파라미터가
// Func<int, const char*, float>(...);
// arg1 이 int, args 가 나머지 타입이 됨
// 이 타입들의 리스트를 사용하려면 펑션의 바디 안에서 (expression)Args(expression)... 라고 적어줌
// Args&&... 으로 적으면
// const char*&&, float&& 이라는 의미
// Func 바디 안에서 args... 은 "Hello" 와 3.14f 가 되는 것
// Func(args...) 은 Func("Hello", 3.14f) 로 확장됨
// 그렇게 되면 Func<const char*, float> 로 확장됨
// 첫번째 arg1 는 const char* 타입이 되고, 나머지 args 는 float 이 됨
// 그래서 Process 에선 const char* 버전을 호출
// 그리고 Func(float) 버전을 호출
// 그러면 Func<float> 이 되고, arg1 이 float 이 되고 콤마가 있더라도 없다고 무시됨 (컴파일러가 지원하기 때문에 가능함)
// 그러면 args 는 void 가 됨.
// args... 는 void 이므로 void 받는 함수가있어야 에러가 나지 않음

// 많이 쓰는 예로 variadic argument 를 이용해서 printf 를 구현한 것들이 인터넷에 많이 돌아다님

int main() {

    // Func(1, "Hello", 3.14f);
    // 처럼 가변적으로 주고 싶음
    // 이렇게 하려면 type parameter 를 가변적으로 받아야 함. 이걸 해 주는 것이 variadic template

    Func(1, "Hello", 3.14f);

    return (0);
}