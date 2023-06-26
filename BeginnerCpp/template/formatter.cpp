#include <iostream>

template <typename T>
class Formatter {
    T* m_t;
public:
    Formatter(T* t) : m_t(t) {}
    void Print() {
        std::cout << *m_t << std::endl;
    } // Print()
}; // class Formatter

template<>
// T 가 전부 대채
// 만약 모든 타입이 대채된다면 (그렇게 할 일은 거의 없음. 대부분 partial 로 특화함)
// full template specialization 이라고 함
class Formatter<char*> {
    char* m_t;
public:
    Formatter(char* t) : m_t(t) {}
    void Print() {
        std::cout << m_t << std::endl;
        // char* 인 경우 char 출력이 아닌 문자열 출력이 목표
        // 이런 경우에 이렇게 특화함

    } // Print()
}; // class Formatter

int main() {
    int i = 154;
    Formatter<int> f1(&i);

    char* str1 = "Gentoo";
    Formatter<char*> f2(str1);
    f1.Print();
    f2.Print();
    // 만약 특화된 버전이 없다면 G 출력,
    // 하지만 char* 에 대해서 특화했기 때문에 Gentoo 를 출력함

    return (0);
}
