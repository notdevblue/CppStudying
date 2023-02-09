#include <stdio.h>

int main() {
    int n = 0;
    int a = 0;
    int v = 1;
    int x = 1;
    int u = 0;

    scanf("%i", &n);

    if (n == 1) {
        printf("1\r\n");
        return (0);
    }

    for (int i = 0; i < n; i++) {
        if (u == 0) {
            a = x;
            for (int j = 0; j < n; j++) {
                printf("%d ", a);
                a++;
            }
            printf("\n");
            v++;
            u = 1;
            a = n * v;
        } else if (u == 1) {
            for (int j = 0; j < n; j++) {
                printf("%d ", a);

                a--;
            }
            x = (a + n) + 1;
            u = 0;
            printf("\n");
            v++;
        }
    }

    return (0);
}