// complie time class generation
// 을 이해하기 위해선 recursion 을 이해해야 함
// 대부분 recursion 을 이융해서 compile time class generation 하기 때문
// recursion 은 함수가 자기 자신을 호출하는 방식
// 대표적으로 펙토리얼 같은 것의 구현은 루프를 쓰는 것 보다 recursion 을 이용해서 구현하면 좀더 직관적이고 알아보기 쉬운 코드가 생성됨

#include <iostream>
#include <stdio.h>
#include <chrono>

int Fact(unsigned long long n)
{
    if (n == 0)
        return 1;
    else
        return n * Fact(n - 1);
}

template<unsigned long long n>
struct KFactorial
{
    // enum { valule = 1; };
    // 클레스 안에 enum 타입이 정의된 경우 값을 초기화할 수 있음
    enum { value = n * KFactorial<n - 1>::value };
    // KFactorial<4>::value 를 한 경우
    // KFactorial<3> 을 확장하려 하고
    // KFactorial<2> 을 확장하려 하고
    // KFactorial<1> 을 확장하려 하고
    // KFactorial<0> 을 확장하려 함
};

// 계속 확장되면 안되니 종료조건을 명시해야 함
template<>
struct KFactorial<0ULL> // 템플릿 특화를 통해 종료조건을 만듬
// partial ordering 으로 인해 0 인 경우 이 버전을 사용 
{
    enum { value = 1 };
};
// 일반 함수로 재귀호출을 통해 구현해야하는 문제를
// 템플릿 클레스를 이용하면 똑같이 구현할 수 있음 
// 이렇게 템플릿의 원레 기능이 아니라
// 템플릿의 특징을 이용해 문제를 푸는 (템플릿을 이용해서 문제를 푸는)
// 그러한 방법들을 template meta programming

// 재귀 호출 방식으로 템플릿을 계속 생성하는것은 아주 잘 알려진 대표적인 template meta programming 의 예
// 하지만 위에 방법처럼 구현하면 100! 구하면 클레스가 101개 생성됨
// 실제로 구현할 때는 함수 사용하도록
// 일단 이런거가 template meta programming

int main()
{
    unsigned long long i = 0;
    
    auto start = std::chrono::system_clock::now();
    i = Fact(4000);
    std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;

    printf("결과: %llu, 걸린 시간 %e or %lf\r\n", i, sec.count(), sec.count());
    // 8.000000e-07

    start = std::chrono::system_clock::now();
    i = KFactorial<4000>::value;
    sec = std::chrono::system_clock::now() - start;

    printf("결과: %llu, 걸린 시간 %e or %lf\r\n", i, sec.count(), sec.count());
    // 3.000000e-07
    

    // 컴파일러가 이 문장을 보면 KFactorial 에 대해 클레스 코드를 생성하려 함
    // 이렇게 하면 객채를 만들지 않고 enum 상수값을 접근하는 코딩이 가능함

    return (0);
}

