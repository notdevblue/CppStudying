#include <stdio.h>

void endl()
{
    printf("\r\n");
}

class ostream
{
public:
    const ostream &operator<<(int i) const
    {
        printf("%i", i);
        return *this;
    }

    const ostream &operator<<(const char *s) const
    {
        printf("%s", s);
        return *this;
    }

    const ostream &operator<<(float f) const
    {
        printf("%g", f);
        return *this;
    }

    const ostream &operator<<(void (*manipulator)()) const // C programming channel 에 function programming 에 함수 포인터 설명 있음
    // iostream 라이브러리에선 iostream 을 조작한다고해서 manipulator 이라고 함
    {
        manipulator();
        return *this;
    }
};

ostream cout;

int main()
{
    int i = 3;
    float f = 3.14;

    // cout.Print(i).Print(f).Print("Hello");

    // cout.operator<<(i).operator<<(f).operator<<("Hello"); // explicit call
    // cout << i << " " << f << " " << "Hello"; // implicit call
    // (cout << i) expression 이 ostream 객채를 return 함
    // 표준 std::cout 구현 원리
    // ostream (output stream) 이라는 표준 객체를 출력을 위해 구현
    // 어떤 함수보다 cout 이라는 객채가 먼저 만들어지도록 구현됨
    // c++ understanding 에 more c++ edm 영상에서 설명
    
    // 연속적인 호출에서 기능을 추가하는것도 가능함
    cout << i << " " << f << " " << "Hello" << endl;
    // endl 은 함수 시작 주소니까 함수 시작 주소를 받는 operator<<(void (*manipulator)()) 가 실행됨


    return (0);
}