#include <stdio.h>

// template method pattern
// 아주 많이 쓰는 디자인 패턴
// base 클레스와 derived 클레스가 있을 때
// base 클레스에 이미 만들어진 어떤 interface (예: foo())
// base 의 interface 함수를 호출하면 derived 의 implementation 이 호출되는 방식
//      Base obj = derived;
//      obj.foo(); => derived.foo() 이 되게
// 저 위의 구현은 virtual function 으로 구현이 가능함
// binding 이 runtime 때 이루어지기 때문에 가능하다.

// 이것은 runtime 에 binding 됨. implementation 호출은 실행 시간에 일어나는 것
// 컴파일 타임에 일어나도록 하면 약간 더 빠름. vtable 찾을 필요가 없으니

template <typename DERIVED>
struct KBase {
    void Interface() {
        // template method function 에서는
        // 기타 housekeeping 작업을 함

        // 그리고 실제로 Implementation 함수를 호출
        // /* virtual */ Implementation();
        // 이것이 재대로 동작하려면 virtual function 이 되어야 함
        // 하지만 virtual 이 runtime binding.

        // Interface 내부에서 this pointer 를 알고 있으므로
        // this 를 지정된 DERIVED 타입으로 casting 함
        static_cast<DERIVED*>(this)->Implementation();
        // 만들어진 객채가 KDerived 객채라면 this 포인터는 KBase 타입에서 KDerived 타입으로 캐스팅 되는 것
        // 그리고 캐스팅된 this 포인터에 대해 Implementation 함수를 호출
        // 이러면 compile time 에 derived class 의 Implementation 을 호출할 수 있음
        // 위는 template method function 과 동일하게 동작하지만 complie time binding 으로 구현할 수 있음 

        // static polymorphism 이라고 함
    }
};

struct KDerived : public KBase<KDerived> {
    void Implementation() {
        printf("Install Gentoo\r\n");
    }
};

int main() {

    KBase<KDerived> base = KDerived();
    base.Interface();

    KDerived k;
    k.Interface();

    return (0);
}

// template meta programming 은 compile time class generation 과 static polymorphism 뿐만 아니라
// 원레 고유의 템플릿 기능 뿐만이 아닌 다른 여러가지 것들을 구현할 수 있음
// 이것들이 template meta programming 의 범주의 속함