// 템플릿을 작성했을 때 실제로 template function, template class 이름이 decorated name 으로 코드가 새롭게 생성됨
// 그런데 overload 된 function 에 대해서도 똑같이 적용됨

#include <stdio.h>

// c 함수를 c++ 에서 쓰려면 그냥 extern 하면 안되고
// 이 함수는 c 함수니까 이름을 decoration 하지 말라고 알려줘야 함
// 그것이
// extern "C"
// {
// }

// int GetMax(int a, int b)
// {
//     // 컴파일러가 GetMax 를 호출했을 때 함수 이름이 어떻게 되는지 확인할 수 있음
//     // printf("%s\r\n", __FUNCSIG__); // signature name (이름이 뭔지 리턴타입은 뭔지 파라미터는 몇게이고 타입은 얼마인지) (__PRETTY_FUNCTION__)
//     // (visual studio community 기준) __FUNCSIG__ 은 현제 function 의 signature 를 가짐
//     // 메크로 처럼 보이지만, 위의 문장이 실행될 때 적절한 function signature 의 값을 가짐. compile time 전역 변수
//     // 예시: int __cdecl GetMax(int a, int b)

//     // printf("%s\r\n", __FUNCDNAME__); // decorated name
//     // 컴파일러가 생성한 이름 가짐
//     // 예시: ?GetMax@@YAHHH@Z
//     // c++ 함수는 오버로딩 되든 되지 않았든, 혹은 템플릿 함수에 대해서도 name 이 변경됨 (decorated name 사용)

//     // c 인 경우, 함수 이름 앞에 _ 만 붙음 ( _GetMax )
//     // 원레 c 에서 함수를 생성하는 관례였음
//     // 모든 유저 함수에 대해 _ 를 붙인 이름을 내부적으로 사용
//     // 이것이 c 함수와 c++ 함수가 호환되지 않는 이유

//     // 같은 함수지만 c 함수와 c++ 함수는 다름
//     // c++ 인 경우 GetMax 가 아닌 decorated name 을 사용함

//     // printf("%s\r\n", __FUNCTION__);
//     // 실제 유저가 작성한 function name
//     // 예시: GetMax

//     return a > b ? a : b;
// }

// // 같은 일을 하는데 내부 기능이 약간 다른 경우 일반적으로 오버로딩 함
// float GetMax(float a, int b)
// {
//     // printf("%s\r\n", __FUNCSIG__); // signature name
//     // printf("%s\r\n", __FUNCDNAME__); // decorated name
//     // 예시: ?GetMax@@YAMMH@Z

//     return a > b ? a : b;
// }

// 컴파일러가 실제로 decorated name 을 사용해서 overload 된 함수를 구분함
// 컴파일러는 같은 이름을 가지는 오버로딩된 함수에 대해 name mangling

// 같은 일을 하는 함수이지만 타입이 다르기 때문에 함수를 두번 작성
// 일반적으로 하는 일은 같지만 타입이 다른 경우에는 오버로딩으로 구현하지 않고 template 으로 구현함

// #define DATA_TYPE int
// 만약 int 가 아닌 float 가 필요한 상황이라면
// int 를 float 로 치환하면 가능
// 이렇게 하는 일은 같지만 데이터 타입이 다른 경우에
// 각각의 함수가 필요한 상황에 대해서 c++ 은 template 를 이용해서 이런 함수들을 만들어 낼 수 있음
// template 은 실제 함수가 아니라 함수를 만들어내는 함수임
// meta function 이라고 함
// DATA_TYPE GetMax(DATA_TYPE a, DATA_TYPE b)
// {
//     return a > b ? a : b;
// }

// template<class>
// 예전에는 class 라는 키워드를 사용함 (표준이 있기 전까지는 새로운 키워드를 추가할 수 없었기 때문)

// template <typename DATA_TYPE, typename T2, int SIZE>
// 타입을 여러게 받는다면 위와 같이 타입을 작성하면 됨
// native type 도 위와 같이 받을 수 있음

// template function
// 하나의 함수가 각각의 타입에 대해서 함수를 만들어 내도록 한 뒤 그 함수를 호출
template <typename DATA_TYPE>
// 이 함수는 일반 함수가 아닌 template 함수다 라는 의미
// 이 템플릿 함수는 DATA_TYPE 이라는 타입을 하나 parameter 로 받는다 라는 뜻
DATA_TYPE GetMax(DATA_TYPE a, DATA_TYPE b)
// 그리고 함수가 하는 일을 정의
// (읽기 좋으라고 이렇게 한줄 따로 분리해서 작성한다고함)
{
    // printf("%s\r\n", __FUNCDNAME__); // decorated name
    // 다른 타입은 decorated name 이 다름
    return a > b ? a : b;
}
// 위의 타입 (DATA_TYPE 을 사용자가 지정을 하면) DATA_TYPE 대신 전달된 타입을 함수에 정의해서 DATA_TYPE 이 그 타입으로 사용됨
// 그래서 그 함수를 만들어 낸 다음에 GetMax 가 그 함수를 호출하게 되는 것

int main()
{
    // int i = 2;
    // int j = 3;

    // GetMax(i, j);
    // // 컴파일러는 ?GetMax@@YAHHH@Z 를 호출
    // GetMax(2.1f, 3.1f);
    // // 컴파일러는 ?GetMax@@YAMMH@Z 를 호출

    // // 이래서 같은 이름의 함수를 정의하고 호출할 수 있음

    // int i = 2;
    // int j = 3;
    // GetMax(i, j);

    GetMax<int>(2, 3); // explicit call
    GetMax<float>(2.154f, 3.154f); // explicit call
    // 이렇게 함수를 호출할 때 DATA_TYPE 을 명시해 줘야 함 (컴파일러가 유츄할 수 없다면)

    int i = 2;
    int j = 3;
    GetMax(i, j); // implicit call
    // 둘다 int 이기 때문에 DATA_TYPE 이 int 라는걸 알 수 있음 (컴파일러가 유추할 수 있음)
    // 일반적으로 implicit call 을 함
    // 일반 함수인지 템플릿 함수인지 해깔리는 상황이 오지만 쓰기가 편하고 더 자연스럽다고 교수님이 그럼

    return (0);
}
