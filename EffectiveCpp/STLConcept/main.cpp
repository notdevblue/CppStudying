/*
크게 STL 라이브러리를 보면 Container 를 이해하고
Container 요소 (노드)들을 접근하기 위해서 Iterator 라는 개념을 이해해야 함
그다음 Container 가 제공하는 알고리즘이나 아니면 모든 Container 에 적용 가능하도록 구현된 알고리즘 클레스들을 이해하는게 그 다음 단계
그다음 Utility 함수들
*/

// Container
/*
여러가지 요소들을 담고 있는 자료구조

대표적으로 배열
배열은 크기가 일정한 어떤 데이터들을 n 개 가질 수 있음
그리고 배열을 선언했을때 각각의 element 들을 접근할 수 있음
Index bracket 연산자를 이용해서 index 를 지정함으로 요소 접근 가능

그다음으로 Linked List
배열처럼 크기가 고정 X
노드 갯수 동적으로 유지할 수 있음

배열은 크기가 고정, 요소들이 연결된 메모리 공간에 할당됨
Linked List 는 노드 단위로 메모리 할당이 이루어짐
연속적이진 않지만 크기를 자유롭게 변경하고 추가하는게 가능해짐
예를 들어 새로운 노드를 Insert 하는 경우에 메모리 할당 후 기존 노드의 Link 를 업데이트 함으로서 중간에 노드를 Insert 하는게 가능

그다음으로 Tree
Root 노드가 있고, Child 가 있고, 정렬이 되 있든 안되있든간에 노드간 차래대로 링크를 가짐
그렇게 노드들의 자료를 유지할 수 있음
*/

// 표준 템플릿 라이브러리 (Standard Template Library) (STL)
/*
두번째 Template 는 C++ 의 template 으로 만들어진 라이브러리 라는 의미
STL에서 가장 큰 덩치를 자지하는 부분이 위의 Array, Linked List, Tree, Graph 등등을 유지하는 자료구조
Element 들의 덩어리를 유지하기 때문에 Container 라고 함
Container 라고 하면 요소들을 여러개 가진 어떤 덩어리 라고 생각하면 됨
Container 의 종류와 상관 없이 요소들을 클레스 외부에서 접근하는 방법이 Iterator

Container 클레스가 주어지면, Container 에 요소를 담은 다음에 Iterator 를 이용해서 요소들을 차래대로 접근하거나, 필요에 따라 Insert 하거나, Delete 하는게 가능해짐
*/

#include <stdio.h>
#include <vector>

int main() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);
    v.push_back(9);
    // 마지막에 넣는 함수

    // 외부에서 각각의 element 들을 꺼내오고 읽고 하기 위해 iterator 사용
    // iterator 는 container 마다 내부에 정의된 특정한 구조체 데이터 타입
    std::vector<int>::iterator it;

    // v.begin() : instance v 가 제공하는 첫번째 iterator 값
    // v.end() : instance v 가 제공하는 마지막 요소의 다음을 가리키는 iterator 값
    for (it = v.begin(); it != v.end(); ++it) {
        // iterator 는 element 를 가리키는 요소에 대한 레퍼 클레스
        const int idata = *it; // iterator 가 가리키는 대상을 읽어서 idata 에 저장
        printf("%i\r\n", idata);
    }

    for (int i = 0; i < v.size(); ++i) {
        printf("%i\r\n", v[i]);
        // 이렇게 해도 iteration 하는게 가능
    }

    // vector 를 container 라고 하고
    // container 안에 선언된 요소를 접근하기 위한 레퍼 구조체를 iterator 라고 함

    // begin, end 구조를 데이터 타입에 상관없이 일관된 구조로 이용하려고 함
    // vector 를 사용했지만 다른 container 클레스에 대해서도 begin, end 를 사용해서 모든 요소들을 iteration 가능하게 만든 것이 iterator 임.
    // 위에서 사용한 vector 를 set, map 등으로 바꾸더라도, 아레에 iteration 쪽은 바꿀 필요가 없음
    // container 에 종류에 상관 없이 iterator 를 사용하면 일관된 요소로 접근이 가능해 지는 것이 iterator

    return 0;
}