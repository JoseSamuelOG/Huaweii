#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparator(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int main()
{
    int a[3] = {};
    for(size_t i = 0; i != 3; ++i) {
        scanf("%d", a + i);
    }
    qsort(a, 3, sizeof(int), comparator);
    printf("%d\n", a[1]);
    
    return 0;
}