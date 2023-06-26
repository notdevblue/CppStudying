#include <stdio.h>
#include <vector>

template<typename T>
class myvector {
private:
    T       data[100];
    int     ibegin;     // 첫번째 요소를 가리킴
    int     iend;       // 마지막 요소 다음값을 가리킴

    // 데이터가 3개 들어가 있는 경우,
    // ibegin 은 0  (첫번째 요소)
    // iend 는 3    (마지막 요소의 다음)

public:
    inline myvector() {
        ibegin = 0;
        iend = 0;
    }

    void push_back(const T& i) {
        data[iend] = i;
        ++iend;
    }

    T& at(int index) {
        return data[index];
    }

    int size() const {
        return iend - ibegin;
    }
};

int main() {
    myvector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);
    v.push_back(9);

    for (int i = 0; i < v.size(); ++i) {
        printf("%i\r\n", v.at(i));
    }

    return 0;
}