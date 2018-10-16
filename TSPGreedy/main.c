#include <stdio.h>
#include <stdlib.h>

/* Connect two edges */
void connect(weighted_edge *edges, unsigned int first, unsigned int second,
        unsigned int weight, unsigned int *pos)
{
    edges[*pos].first = first;
    edges[*pos].second = second;
    edges[*pos].weight = weight;
    (*pos)++;
}

static void print_edges(const weighted_edge *edges, unsigned int n)
{
    unsigned int e;
    for (e = 0; e < n; e++) {
        printf("(%u, %u, %u) ", edges[e].first, edges[e].second, edges[e].weight);
    }
    putchar('\n');
}

int main(void)
{
    unsigned int i = 0;
    const unsigned int size = 15; /* Edges */
    const unsigned int order = 6; /* Vertices */
    weighted_edge *edges = malloc(size * sizeof(weighted_edge));
    weighted_edge *tour;

    connect(edges, 0, 1, 25, &i);
    connect(edges, 0, 2, 19, &i);
    connect(edges, 0, 3, 19, &i);
    connect(edges, 0, 4, 16, &i);
    connect(edges, 0, 5, 28, &i);
    connect(edges, 1, 2, 24, &i);
    connect(edges, 1, 3, 30, &i);
    connect(edges, 1, 4, 27, &i);
    connect(edges, 1, 5, 17, &i);
    connect(edges, 2, 3, 18, &i);
    connect(edges, 2, 4, 20, &i);
    connect(edges, 2, 5, 23, &i);
    connect(edges, 3, 4, 19, &i);
    connect(edges, 3, 5, 32, &i);
    connect(edges, 4, 5, 41, &i);

    tour = cheapest_link_tsp(edges, size, order);
    print_edges(tour, order);

    free(tour);
    free(edges);
    return 0;
}
