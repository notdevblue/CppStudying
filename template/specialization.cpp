#include <stdio.h>
#include <string.h>

// 특정한 데이터 타입에 대해서는 내부 코드가 약간씩 달라져야 하는 경우가 생김
// 예를 들어 char* 를 관리하는 경우, 그냥 stack 에 담아두면 값 자체가 아닌 포인터만 저장되므로 위험한 상황이 생길 수 있음
// KStack 클레스는 사용자가 문자열 상수를 지정한 경우 그 문자열 전체를 복사해서 유지하려고 함
// 그렇게 하려면 각각의 entry 마다 문자열을 위한 buffer 가 할당이 되야 함
// => row, column 을 가지는 2차원 배열이 됨
// 이제 KStack<char*> 인 경우 2차원 buffer 를 가지도록 구현해야함
// 이럴때 사용되는게 template specialization (템플릿 특화)

template <typename T, int SIZE = 100>
class KStack // 이렇게
{
public:
    KStack() : sp(0) {}

    void Push(T d) {
        data[sp] = d;
        ++sp;
    }

    bool Pop(T& d);

    bool IsEmpty() const {
        return sp == 0;
    }

private:
    int sp;
    T data[SIZE];

}; // class KStack

template <typename T, int SIZE>
bool KStack<T, SIZE>::Pop(T& d) {
    if (sp == 0)
        return false;

    --sp;
    d = data[sp]; // set out param
    return true;
}

// (partial) template specialization
// parameter 를 일부만 바꿨으면 partial template specialization
template <int SIZE>
// typename T (데이터가 바뀌는 곳) 를 삭제하고, SIZE 의 default 값을 지움 (위에서 이미 지정했기 때문에)
class KStack<char*, SIZE> // 클레스 이름 다음에 지정되는 데이터 타입 지정, 나머지 parameter 전달
// 데이터 타입 T 가 char* 인 경우 이 template class 를 이용해서 코드를 생성하라는 의미
{
public:
    KStack() : sp(0) {}

    void Push(char* d) {
        strcpy((char*)data[sp], d);
        ++sp;
    }

    bool Pop(char*& d);

    bool IsEmpty() const {
        return sp == 0;
    }

    // 특화 버전인 경우 추가적인 멤버 함수를 가질 수 있음
    // 좋은 방법은 아님
    // 기존 인터페이스랑 달라지니까
    // 만약 추가적으로 멤버함수 구현할 일이 있다면, 원레 버전에도 추가하고 구현하는게 바람직


private:
    int sp;
    char* data[SIZE][20];

}; // class KStack

template <int SIZE>
bool KStack<char*, SIZE>::Pop(char*& d)
{
    if (sp == 0)
        return false;

    --sp;
    d = (char*)data[sp]; // set out param
    return true;
}

// 이미 구현된 템플릿 클레스에 대해서
// 특정한 데이터타입이 달라지거나
// 특정한 데이터타입의 조합으로 작성해야하는 경우
// template specialization (템플릿 특화) 를 이용해서 구현해야 함
// 기존의 template parameter 에서 특화되는 부분을 제외하고
// template <typename T, int SIZE = 100> -> template template <int SIZE = 100>
// 실제로 템플릿의 대채되는 부분을 클레스 이름 다음에 명시적으로 적어줘야 하고, 특화되지 않은 부분 (타입이 지정되지 않은 부분) 원레대로 적어줘야 함
// 그리고 해당하는 데이터 타입을 사용하도록 모든 멤버를 적절하게 수정해야 함 (필요하다면 해당하는 기능과 데이터 타입을 사용하도록 기능을 수정해야함)
// 

int main()
{
    KStack<char*> s3;
    s3.Push("Hello");
    s3.Push("World");

    char* pText = nullptr;

    s3.Pop(pText);
    printf("%s\r\n", pText);

    s3.Pop(pText);
    printf("%s\r\n", pText);

    return (0);
}