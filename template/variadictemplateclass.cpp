#include <stdio.h>
#include <memory>

class KBase1 {
public:
    KBase1(int i) {
        
    }
};

class KBase2 {
public:
    KBase2(float f) {

    }
};

// template <typename BaseClass>
// class KTest : public BaseClass
// KTest 를 생성할때 template parameter 로 BaseClass 를 지정해준다면 다양하게 상속받는것이 가능해짐
// 실제로 실무를 하다보면 어떤 클레스는 경우에 따라 베이스 클레스를 한개 받거나 두개 가지거나 하는 경우가 생김

template <typename... BaseClass> // type parameter pack
class KTest : public BaseClass...
// parameter pack 이 전달됨. 실제로 각각의 argument value 나 type 다음에 , 가 확장됨
// 그래서 실제로는 public BaseClass1, public BaseClass2, public BaseClass3 (등등으) 로 확장되기 때문에 문법에 문제가 없음
// 중요한건 BaseClass 가 확장되는 것이 아닌 ... 앞의 표현식이 확장되다는 것 (expression 의 조합이 확장된다는 거)
{
public:
    // KTest() : BaseClass() {
    // }
    
    KTest(BaseClass&&... baseValues)
    // BaseClass 를 파라미터로 받았으므로
    // BaseClass 의 생성자가 어떤 값을 필요로 한다면 
    // BaseClass 타입의 rvalue 레퍼런스를 받아야 함
    // rvalue 레퍼런스를 받아야 하는 이유는 
    // template 구현에서 rvalue 레퍼런스나 lvalue 레퍼런스를 자유롭게 받으려면
    // & 두개 쓰면 유니버셜 레퍼런스가 됨 (C++ Understanding 에 있음 ㅎㅇ)

        : BaseClass(baseValues)... {
        // BaseClass  = 하나의 타입
        // baseValues = 하나의 값
        // BaseClass(baseValues)... 으로 하면
        // 각각의 타입과 value 에 대해 확장됨

        // 타입을 <int, const char*, float> 으로 전달하고 값을 (1, "Hello" 3.14f) 로 전달했을 시
        // int(1), const char*("Hello"), float(3.14f)
        // 이런 식으로 확장됨
        // ... 앞에 어떤 표현식이든 가능함
    }
};


template <typename T, typename... Args>
// variadict template 있기 전 버전에는 여러가지 트릭들을 이용해 구현했다고 함
std::unique_ptr<T> mymake_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    // 내부적으로 이렇게 구현되어있다고 함
    // variadict template 를 이용하니 모든 생성자 조합에 대해 unique_ptr 를 생성하는 mymake_unique 같은 구현이 가능
}
// unique_ptr<T> 를 만드는 헬퍼 함수

class KTest2 {
public:
    KTest2(int i, const char* s, float f) {

    }
};

int main() {

    // KTest<KBase1, KBase2> t(1, 24.0f);
    // 이렇게 하면 가변 타입 파라미터를 받는 템플릿 클레스를 구현할 수 있음

    std::unique_ptr<KTest2> sp = mymake_unique<KTest2>(10, "Hello", 1.54f);
    // make_unique 는 만드는 객채의 생성자 파라미터를 자유롭게 명시할 수 있음
    // 위의 함수 선언처럼 하면 자유롭게 명시하는 구현이 가능해짐

    return (0);
}