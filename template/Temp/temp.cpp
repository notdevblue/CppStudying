#include <stdio.h>

int main() {
    int n, a;
    // int na[100][100];
    // 단순히 출력만 하면 되서 따로 값을 저장할 필요는 없는 듯 합니다.
    int v = 1;
    int x = 1;
    int u = 0;
    scanf("%d", &n);

    if (n != 1) {
        for (int i = 0; i < n; i++) {
            if (u == 0) {
                a = x;
                for (int j = 0; j < n; j++) {
                    // na[i][j] = a;
                    // printf("%d ", na[i][j]);
                    // 배열을 삭제해서
                    printf("%d ", a);
                    a++;
                }
                printf("\n");
                v++;
                u = 1;
                // a = n;
                a = n * v;
            } else if (u == 1) {
                for (int j = 0; j < n; j++) {
                    // na[i][j] = a;
                    // printf("%d ", na[i][j]);
                    // 배열을 삭제해서
                    printf("%d ", a);

                    a--;
                }
                x = (a + n) + 1;
                u = 0;
                printf("\n");
                v++;
            }
        }
    } else if (n == 1) {
        printf("1");
    }

    return 0;
}