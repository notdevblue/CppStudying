#include <stdio.h>

int main() {
    int n;
    int o = 0;
    scanf("%i", &n);

    for (int i = 0; i < n * n; i += n) {
        for (int j = 0; j < n; ++j) {
            printf("%i ",
                ((i / n) % 2 == 0
                ? j + 1
                : n - j) + i
            );
        }
        printf("\r\n");
    }

    return (0);
}