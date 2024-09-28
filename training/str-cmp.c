#include <stdio.h>
#include <string.h>

int backstrcmp (void *s1, void *s2) {
    printf("backstrcmp have been started\n\n");
    size_t n1 = strlen((const char *)s1), n2 = strlen((const char *)s2);
    printf("%d\t%d\n", n1, n2);

    for (; n1 > 0 && n2 > 0; --n1, --n2) {
        printf("<%d> %s\t<%d> %s\n", n1, (const char *)s1, n2, (const char *)s2);
        if (*((const char *)s1 + n1 - 1) != *((const char *)s2 + n2 - 1)) {
            printf("%c\t-\t%c\t=\t%d\n", *((const char *)s1 + n1 - 1), *((const char *)s2 + n2 - 1), *((const char *)s1 + n1 - 1) - *((const char *)s2 + n2 - 1));
            return *((const char *)s1 + n1 - 1) - *((const char *)s2 + n2 - 1);
        }
    }
    return n1 - n2;
}

int main() {
    char *str1 = "GOVNO";
    char *str2 = "ZOVNO";
    char *str[2] = {str1, str2};

    int d = backstrcmp(str1, str2);
    printf("%d\n", d);

}