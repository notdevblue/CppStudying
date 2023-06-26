#include <iostream>

// 재귀 끝내주기 위해 const char* 받는 myprintf 정의
void myprintf(const char* s) {
    while (*s) { // 포인터가 가리키는 값이 NULL 이 아닐 동안 계속 출력
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                throw std::runtime_error("invalid format string: missing arguments");
            }
        }
        std::cout << *s++;
    }
}

template<typename T, typename... Args>
void myprintf(const char* s, T value, Args... args) {
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                std::cout << value;
                s += 2;
                myprintf(s, args...);
                return;
            }
        }
        std::cout << *s++;
    }
}

int main() {
    int i = 2;
    float f = 3.1f;

    myprintf("hello %% %i, %i\r\n", i, f);
    return 0;
}