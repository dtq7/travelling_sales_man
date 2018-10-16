#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    unsigned int r1[] = {0, 5, 7, 9, 10};
    unsigned int r2[] = {4, 0, 11, 3, 7};
    unsigned int r3[] = {3, 1, 0, 4, 5};
    unsigned int r4[] = {6, 5, 7, 0, 11} ;
    unsigned int r5[] = {13, 2, 8, 3, 0} ;
    const size_t order = 5; /* Vertices */
    const unsigned int *adjmat[] = { r1, r2, r3, r4, r5 };
    unsigned int *best_tour;
    unsigned int cost = traveling_salesman(adjmat, order, &best_tour);
    unsigned int i;
    printf("Best tour cost: %u\n", cost);
    printf("Vertices:\n");
    for (i = 0; i < order; i++) {
        printf("%u ", best_tour[i]);
    }
    putchar('\n');
    printf("Edge weights:\n");
    for (i = 0; i < order - 1; i++) {
        printf("%u ", adjmat[best_tour[i]][best_tour[i + 1]]);
    }
    printf("%u\n", adjmat[best_tour[order - 1]][0]);
    free(best_tour);
    return 0;
}
