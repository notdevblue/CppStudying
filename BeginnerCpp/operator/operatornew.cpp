#include <stdio.h>

// operator new overloading 은
// 프로파일러를 만든다거나 메모리를 추적하기 위해 가끔 사용되는 테크닉

int buffer[1024] = { 0, };

class KTest
{
public:
    KTest()
    {
        printf("KTest()\r\n");
    }
    ~KTest()
    {
        printf("~KTest()\r\n");
    }

    // type independent 하게 동작되기 때문에 std::size_t 를 받지만 실제로는 unsigned int 와 호환됨
    // (긴 하지만 gdb 는 아주 까다롭지)
    // 메모리가 할당되는 동작을 이 함수가 대채함
    // void* 를 return 함
    void* operator new(size_t size)
    {
        printf("operator new(), size = %i\r\n", size);
        // 자기가 관리하는 메모리를 size 만큼 할당해서 return 해 줘야 함
        // malloc 또는 전역 operator new 함수를 호출할 수 있음

        return buffer;
    }

    // operator new 는 parameter 추가 명시가 가능함
    void *operator new(size_t size, const char *msg, int ivalue)
    {
        printf("operator new(const char *msg, int ivalue), size = %i, %s, %i\r\n", size, msg, ivalue);
        // operator new 를 overload 했을 때 이점은, 기존의 size 뿐만이 아니라 추가적인 parameter 를 받는 함수도 정의할 수 있다는 것
        // 

        return buffer;
    }

    // 해제해야할 메모리의 시작 주소를 받음
    void operator delete(void* p)
    {
        printf("operator delete(), p = %p\r\n", p);
        // 해제하고자 하는 메모리를 받아서 그 메모리를 해제해주는 코드가 들어가야 함
    }

    // 일반적으로는 operator new 에는 malloc(), delete 에는 free() 사용

    void *operator new[](size_t size)
    {
        printf("operator new[](), size = %i\r\n", size);
        return buffer;
    }
    void operator delete[](void *p)
    {
        printf("operator delete[](), p = %p\r\n", p);
    }
    // bracket 을 사용하는 opreator new, operator delete 도 정의 가능

private:
    int i = 3;
};

void PrintBuffer()
{
    bool ok = false;

    for (int value : buffer)
    {
        if (value == 0)
        {
            if (ok)
                break;
            ok = true;
        }
        printf("%i, ", value);
    }
    printf("\r\n");

    // int i = 3; 으로 초기화했기 때문에
    // 3 이 출력됨
}

int main()
{
    // KTest *p;

    // p = new KTest;
    // KTest 만큼 메모리 할당 후 KTest() 호출
    // 위의 new 는 두 단계로 나눠짐
    // p = (KTest *)operator new(sizeof(KTest));
    // operator new 는 전역 함수, 어디에서나 호출 가능함
    // 그리고 모든 포인터에 대해 동작해야하므로 void* 리턴함
    // p->KTest::KTest(); // gdb 에서는 직접적으로 생성자 호출이 불가능함
    // 그리고 생성자를 호출

    // 여기서 이미 정의된 new operator 를 KTest 에 대해만 동작하도록 재정의 할 수 있음
    // p->KTest::KTest(); 는 재정의 불가능

    // delete p;
    // ~KTest() 호출 후 메모리 해제
    // delete 도 두 단계로 나눠짐
    // p->~KTest();
    // operator delete(p);

    // p = new KTest();
    // PrintBuffer();
    // delete p;
    // 위에서 정의한 operator new 와 operator delete 를 호출함

    // KTest *p;
    // p = new KTest[5];
    // PrintBuffer();
    // delete[] p;
    // KTest 타입의 객채를 메모리에 할당하려고 할 때
    // new KTest 라는 expression 을 사용을 하면
    // KTest 에 overloaded operator new[] 이 있는지 찾고
    // 있기 때문에 overloaded operator new[] 를 호출함
    // delete[] 도 같음

    // 실행시키면 24바이트가 할당되고 5, 3, 3, 3, 3, 3 이 출력되는걸 알 수 있음
    // (x86에서는 메모리가 4바이트기 때문에 위와 같이 출력되지만 x64에선 아레처럼 할당, 출력)
    // (28바이트 할당 후 5, 0, 3, 3, 3, 3, 3 출력) (메모리가 8바이트기때문에 int 한자리가 남음) (일단 x86으로 설명 적어둠)
    // 앞의 4바이트를 제외한 나머지는 객채를 위해서 할당된 것,
    // 첫번째 5는 만들어진 객채의 수
    // KTest 가 5개 만들어졌다는 의미
    // 각각의 생성자는 1~5번까지의 메모리의 엔트리를 사용하도록 코드가 생성됨
    // bracket operator new 를 사용하면 연속된 메모리가 할당되고, 첫번째 메모리 (4바이트) 에는 천채 메모리의 크기가 할당됨

    // KTest *p;
    // p = new KTest[5];
    // PrintBuffer();
    // delete p;
    // 만약 실수로 일반 opeartor delete 를 사용한 경우
    // 제대로 해제할 가능성이 사실 높음
    // 실제로 객체를 위해서 객체 각각의 내용을 작성하는 것이고
    // 힙 메니저의 내부에서는 이 전체 매모리의 크기가 헤더에 유지가 됨
    // 그래서 실제로 delete[] 대신 delete p 하더라도 메모리 해제에 문제는 없음
    // 하지만 파괴자가 첫번째 객체에 대해서만 호출되기 때문에 아주 위험한 상황이 됨
    // bracket 을 사용한 경우 반드시 bracket 을 사용한 delete 를 사용해 문제가 생기지 않도록 해야 함

    KTest *p;
    p = new ("Hello", 4) KTest;
    // operator new 의 size 를 명시하지 않아도 sizeof(KTest) 가 암시적으로 전달됨
    // overload 된 또다른 operator new 를 호출하고 싶으면 new 의 인자로 전달하면 됨
    // KTest 의 operator new 중 첫번째 인자가 size_t, 두번째가 const char*, 세번째가 int 인 것을 찾음

    // p = new ("Hello") KTest;
    // 만약 integer 를 전달하지 않으면 operator new(size_t, const char*) 를 찾음
    // 하지만 없으니 오류 발생

    PrintBuffer();
    delete p;

    return 0;
}

// 이러한 테크닉은
// 메모리 풀을 구현할 때 자기가 메모리를 관리하면서 사용자가 new 를 쓸 때마다 내가 관리하는 메모리를 돌려주기 위해 사용
// 대표적인 구현이 boost 의 singleton_pool object_pool
// 표준 구현에는 pool 이 없다고 함 (2017년 기준입니다)