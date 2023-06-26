// overloading 하면 c++ 객채지향의 가장 큰 특징 중 하나인 function overloading 을 말함
// funciton overloading 은 같은 이름을 가지지만 시그니처가 다르다면 (parameter 갯수나 타입) 정의가 가능하다는 것을 말함

// void Test(int);
// void Test(float);
// void Test(int, int);

// 컴파일러는 overloading 된 함수에 대해 unique 한 이름을 생성함
// name mangling 이라고 함

// c++ 에선 연산자도 오버로딩이 가능함
// 같은 + 연산자이지만 문맥에 따라 다르게 동작하도록 만들 수 있음

#include <stdio.h>
#include <string.h>


class string
{
public:
    string(const char* s = nullptr)
    {
        if (s == nullptr)
            buffer[0] = NULL;
        else
            strcpy(buffer, s);
    }


    const char* c_str() const 
    {
        return buffer;
    }

    string& Add(const char* right)
    {
        strcat(buffer, right);
        return *this;
    }

    // c++ 에는 멤버 함수, 또는 일반 함수가 기존의 연산자를 사용해서 함수 이름을 정의할 수 있음
    // Add 대신 특별하게 다른 이름을 사용할 수 있음
    // 하지만 ".", "*", "->" 같은 연산자는 오버로딩 불가능 (대부분 다 된다고 보면 됨)
    // 연산자의 특성을 반드시 유지해야 한다는 조건이 존재함

    // 예를 들어 + 는 binary operator, parameter 가 두개 필요함 (left, right)
    // 성질을 어길 순 없음. 이거만 만족한다면 연산자 함수를 정의할 수 있음

    // 연산자 함수는 operator 로 시작하고 뒤에 연산자가 들어감
    // string 의 operator+ 라는 의미임
    // + 의 첫번째 연산자는 자기 자신
    // 두번째 연산자는 right 이 됨
    string operator+(const char* right)
    {
        string temp = *this;
        strcat(temp.buffer, right);
        return temp;
    }

    string& operator=(const string& rhs)
    {
        memcpy(buffer, rhs.buffer, sizeof(buffer));
        return *this;
    }
    // = 을 사용했을 때 operator= 가 호출됨

    friend string operator+(const char *left, const string &right);

private:
    char buffer[100];
};

// 연산자 오버로딩 함수는 일반 함수로도 만들 수 있음
string operator+(const char* left, const string& right)
{
    string t = left;
    t = t + right.buffer;
    strcat(t.buffer, right.buffer);
    // 하지만 private 멤버를 외부에서 접근할 수 없어서 오류가 발생함
    // 그래서 보통 operator 함수는 friend 함수로 구현됨
    return t;
}

int main()
{
    string s = "Install"; // implicit constructor call

    // s.Add(" Gentoo").Add(" and").Add(" Remove").Add(" Windows");

    s.operator+(" Gentoo").operator+(" Always");
    // 이렇게 사용할 수 있음 ( explicit 호출 )

    s + " Gentoo" + " and" + " Remove" + " Windows";
    // operator 를 생략하고 사용할 수 있음 ( implicit 호출 )

    s.operator+(" Gentoo"); // explicit call
    // + 왼쪽에 string 객체, 오른쪽에 const char* 타입이니
    // 위와 아레는 같은 의미임
    s + " Gentoo"; // implicit call
    // 실제로 컴파일러는 이 문장을 만나면
    // s 라는 객채에 operator+ 라는 함수가 있는지 알아본다
    // 그리고 첫번째 parameter 로 const char* 타입을 받는지 알아보고 있으면 ,전달
    // s + " Gentoo"; 를 s.operator+(" Gentoo"); 로 변역
    // implicit 을 explicit 로 번역

    s = s + " Gentoo";
    // s = s.operator+(" Gentoo");
    // s.operator=(s.operator+(" Gentoo")); // explicit
    // s 값을 바꾸려면 이렇게 해야 함
    // = 에 대해서도 정의해주는것이 바람직함

    printf("%s\r\n", s.c_str());

    string t;
    t = "Hello " + s;
    // operator equal 이 사용되었고,
    // right param 으로 "Hello" + s 를 전달
    // t.operator=("Hello" + s); 로 해석
    // 그리고 "Hello" 가 operator plus 가 있는지 찾아보지만
    // 존재하지 않으니 실패 => 에러
    // 하지만 일반 함수로 정의된 operator plus 가 있고 첫 번째 parameter 가 const char* 형식이라면 가능할 것
    // operator+ 가 parameter 를 두개를 받고 멤버 함수가 아닌 일반 함수로 구현된다면 위와 같은 사용이 가능해짐

    printf("%s\r\n", t.c_str());

    return 0;
}