#include <stdio.h>

class KBase {
public:
    virtual ~KBase() {}
};

class KDerived : public KBase {
public:
    void Print() {
        printf("KDerived::Print()\r\n");
    }
};

class KDerived2 : public KBase {
public:
    void Print() {
        printf("KDerived::Print2()\r\n");
    }
};

int main() {
    KBase* a = new KBase;
    #pragma region Down casting
    // KDerived* b = static_cast<KDerived*>(a);
    // 빌드가 되고, 캐스팅이 됨
    // b 가 null 이 아니므로 Print 호출
    // 실제로 만들어진 타입의 객체는 KBase 이지만, KDerived 타입으로 케스팅 됬기 때문에 KDerived 의 Print 를 호출해버리는 것
    // 멤버변수를 선언, 엑세스하지 않기 때문에 죽지 않음
    // 하지만 대부분의 경우에 프로그램은 죽음
    
    // 컴파일 시간에 이것을 막는 것은 불가능함
    // KDerived 타입이 다운케스팅이 안전한지, 안전하지 않은지 알 방법이 없기 때문
    // 그래서 static_cast 는 static 정보로 케스팅해라 라는 의미기 때문에
    // static_cast 로는 안전하지 않은 변환을 막을 방법이 없음

    // 실제로 안전한지 안전하지 않은지 판별하기 위해선 실행 시간 정보를 이용해야 하는 것
    // 실행 시간 정보를 이용해서 케스팅을 해라 라는 것이 dynamic_cast 임
    // Down casting 은 안전할수도, 안전하지 않을수도 있음
    // 지금 이 경우는 KBase 로 만들어진 객체를 KDerived 로 캐스팅하기 때문에 안전하지 않은 경우
    KDerived* c = dynamic_cast<KDerived*>(a);
    // 빌드가 됨
    // 하지만 c 가 null 이기 때문에 아무것도 찍히지 않음
    // dynamic_cast 를 사용하면 이런 class hierarchy 상에서 업 케스팅이나 다운 케스팅, 크로스 케스팅의 실행 시간 정보를 이용해서 케스팅하기 때문에
    // 안전하지 않은 케스팅은 null 을 리턴
    // 고로 c 에 null 대입

    // 대부분의 경우에선 static_cast
    // 하지만 casting 하려는 데이터 타입이 virual 을 포함한 class 타입이라면 dynamic_cast
    // 즉 down casting 이나 cross casting 인데 virtual 을 포함한 상속 관계의 케스팅일 때 dynamic_cast
    // 이것이 dynamic_cast 를 사용하는 일반적인 관례
    #pragma endregion // Down casting
    // down casting, 안전하지 않을 수 있음
    // 이미 만들어진 KDerived 객채를 KBase 로 캐스팅하고 다시 KDerived 로 캐스팅 하는 경우는 안전함
    // 그래서 안전할수도, 안전하지 않을수도 있지만
    // 코드만 보고 판단할 방법이 없음

    // KDerived2 타입의 포인터를 KBase 로 캐스팅하는 형식의 케스팅을 업 케스팅이라고 함
    // 항상 안전함
    // subtype principle 을 만족함
    // static_cast 를 사용하거나, dynamic_cast 를 사용하든 문제가 없는 상황

    // KDerived2 타입 객체를 KDerived 로 케스팅 (혹은 반대로)
    // 이것을 cross casting 이라고 함
    // 안전하지 않음
    // 실제로 만들어진 객체가 KDerived 라면, KBase* 로 형번환 하는것은 안전하지만
    // KDerived2 타입으로 형변환하는것은 
    // KDerived2 타입이 KDerived 에서 선언된 변수들을 가지지 않기 떄문에 안전하지 않음


    // if (b != nullptr) {
    //     b->Print();
    // }

    // if (c != nullptr) {
    //     c->Print();
    // }

    KDerived* f = new KDerived();
    KDerived2* g = dynamic_cast<KDerived2*>(f);
    // 안전하지 않은 casting 이므로 g 는 null

    if (g != nullptr) {
        g->Print();
    }

    delete a;
    delete f;
    return (0);
}