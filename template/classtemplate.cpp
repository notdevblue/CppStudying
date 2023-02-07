#include <stdio.h>


// 필요에 의해 정수 스택이 아니라 float stack 이 필요한 상황이 됬을 때
// KStack 을 한번 더 만들어야 하는 상황이 됨
// 같은 기능을 하지만 타입이 다를 때 template class 도 만들 수 있음

// #define T int
// 이걸 템플릿으로 만들면

// template <typename T, typename U, int SIZE>
// KStack 은 parameter 를 세가지 받는다.
// 첫번째 parameter 는 어떤 타입 T
// 두번째 parameter 는 어떤 타입 U
// 세번째 parameter 는 이미 알려진 데이터 타입인데 그 값을 SIZE 로 쓰겠다 라는 의미

// template <typename T = int, int SIZE = 100>
// 이렇게 default type 을 명시할 수도 있음
// 그러면 만들때 type parameter 를 생략할 수도 있음
template <typename T, int SIZE = 100>
// 
// template <typename T, int SIZE>
class KStack
// KStack 이 템플릿인데 타입을 parameter 로 받는다
// 그리고 그 타입은 하나를 받는데 T다
// 이제 그냥 클레스에서 template class 가 됨
{
public:
    KStack() : sp(0) {}
    
    void Push(T d)
    {
        data[sp] = d;
        // data[sp++] = d; 로 대부분 하긴 하지만 증가가 먼저일수도 있고, 접근이 먼저일수도 있으니
        // 하나의 문장은 하나의 의미만
        ++sp;
    }

    bool Pop(T &d);

    bool IsEmpty() const
    {
        return sp == 0;
    }

private:
    int sp;
    T data[SIZE]; // 크기가 SIZE 인 T 타입의 data array 가 만들어짐

}; // class KStack

// template class 의 member function 을 클레스 블록 안에서 정의한 경우 문제가 없지만
// 클레스 밖에서 정의한 경우에는
template <typename T, int SIZE> // 템플릿 정의를 위해서 필요함
// 클레스와 타입 동일하게 따라가야 함
bool KStack<T, SIZE>::Pop(T &d)
// 이 템플릿은 T 를 파라미터로 받는다라는 의미
{
    if (sp == 0)
        return false;

    --sp;
    d = data[sp]; // set out param
    return true;
}

int main()
{
    // KStack s;
    KStack<int, 10> s;
    // template function explicit call 처럼 사용하면 된다

    KStack<float, 100> s2;

    KStack s3;
    KStack<> s4;
    KStack<float> s5;
    // 만약 default type 이 명시되어있다면 전부 다 가능
    // 하지만 해깔리게 만들기 때문에 추천하지 않음


    s.Push(3);
    s.Push(5);

    int i = 0;
    s.Pop(i);

    printf("%i\r\n", i);

    return (0);
}