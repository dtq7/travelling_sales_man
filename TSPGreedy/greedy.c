#include <stdlib.h>

//Cheapest Link greedy algorithm
//Other possible greedy algorithm includes Nearest neigbour and repitive nearest neigbour
typedef struct {
    unsigned int first;
    unsigned int second;
    unsigned int weight;
} weighted_edge;

static int compare_weighted_edges(const weighted_edge *edge1, const weighted_edge *edge2)
{
    return edge1->weight - edge2->weight;
}

static unsigned int cyclic_recursive(const weighted_edge *edges, unsigned int n,
        unsigned int *visited, unsigned int order, unsigned int vertex,
        unsigned int predecessor)
{
    unsigned int i;
    unsigned int cycle_found = 0;
    visited[vertex] = 1;
    for (i = 0; i < n && !cycle_found; i++) {
        if (edges[i].first == vertex || edges[i].second == vertex) {
            /* Adjacent */
            const unsigned int neighbour = edges[i].first == vertex ?
                    edges[i].second : edges[i].first;
            if (visited[neighbour] == 0) {
                /* Not yet visited */
                cycle_found = cyclic_recursive(edges, n, visited, order, neighbour, vertex);
            }
            else if (neighbour != predecessor) {
                /* Found a cycle */
                cycle_found = 1;
            }
        }
    }
    return cycle_found;
}

unsigned int cyclic(const weighted_edge *edges, unsigned int n, unsigned int order)
{
    unsigned int *visited = calloc(order, sizeof(unsigned int));
    unsigned int cycle_found;
    if (visited == NULL) {
        return 0;
    }
    cycle_found  = cyclic_recursive(edges, n, visited, order, 0, 0);
    free(visited);
    return cycle_found;
}

weighted_edge *cheapest_link_tsp(weighted_edge *edges, unsigned int size, unsigned int order)
{
    unsigned int t, e = 0;
    weighted_edge *tour = malloc(order * sizeof(weighted_edge));
    unsigned int *degrees = calloc(order, sizeof(unsigned int));
    if (tour == NULL || degrees == NULL) {
        free(tour);
        free(degrees);
        return NULL;
    }
    /* Sort the edges by weight */
    qsort(edges, size, sizeof(weighted_edge),
            (int(*)(const void *, const void *))compare_weighted_edges);
    /* Main algorithm */
    for (t = 0; t < order; t++) {
        unsigned int added = 0;
        while (!added && e < size) {
            if (degrees[edges[e].first] < 2 && degrees[edges[e].second] < 2) {
                tour[t] = edges[e];
                if (t == order - 1 /* It's the last edge */
                    || !cyclic(tour, t + 1, order)) /* It doesn't close the circuit */
                {
                    added = 1;
                    degrees[edges[e].first]++;
                    degrees[edges[e].second]++;
                }
            }
            e++;
        }
        if (!added) {
            /* Edges were not correct */
            free(tour);
            free(degrees);
            return NULL;
        }
    }
    free(degrees);
    return tour;
}
