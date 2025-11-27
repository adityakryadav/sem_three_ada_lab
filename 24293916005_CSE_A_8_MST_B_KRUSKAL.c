/* kruskal_mst.c
   Kruskal's algorithm using Union-Find
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, w;
} Edge;

int compareEdges(const void *a, const void *b) {
    Edge *ea = (Edge*)a;
    Edge *eb = (Edge*)b;
    return ea->w - eb->w;
}

int findSet(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = findSet(parent, parent[i]);
    return parent[i];
}

void unionSet(int parent[], int rank[], int x, int y) {
    x = findSet(parent, x);
    y = findSet(parent, y);
    if (rank[x] < rank[y]) parent[x] = y;
    else if (rank[x] > rank[y]) parent[y] = x;
    else { parent[y] = x; rank[x]++; }
}

void kruskalMST(Edge edges[], int E, int V) {
    qsort(edges, E, sizeof(Edge), compareEdges);

    int *parent = malloc(V * sizeof(int));
    int *rank = malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) { parent[i] = i; rank[i] = 0; }

    Edge *result = malloc((V-1) * sizeof(Edge));
    int e = 0; // index for result
    int i = 0; // index for sorted edges

    while (e < V - 1 && i < E) {
        Edge next = edges[i++];
        int x = findSet(parent, next.u);
        int y = findSet(parent, next.v);

        if (x != y) {
            result[e++] = next;
            unionSet(parent, rank, x, y);
        }
    }

    int total = 0;
    printf("\nEdges in MST:\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d : %d\n", result[i].u, result[i].v, result[i].w);
        total += result[i].w;
    }
    printf("Total weight of MST = %d\n", total);

    free(parent); free(rank); free(result);
}

int main() {
    int V, E;
    printf("Enter number of vertices: ");
    if (scanf("%d", &V) != 1) return 0;
    printf("Enter number of edges: ");
    scanf("%d", &E);

    Edge *edges = malloc(E * sizeof(Edge));
    printf("Enter edges as: u v weight (vertices numbered from 0 to V-1)\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    kruskalMST(edges, E, V);
    free(edges);
    return 0;
}
