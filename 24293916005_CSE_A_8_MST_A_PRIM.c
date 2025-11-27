/* prim_mst.c
   Prim's algorithm for MST using adjacency matrix
*/

#include <stdio.h>
#include <limits.h>
#define MAXV 100

int V;

int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++)
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    return min_index;
}

void printMST(int parent[], int graph[MAXV][MAXV]) {
    int total = 0;
    printf("\nEdge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        total += graph[i][parent[i]];
    }
    printf("Total weight of MST = %d\n", total);
}

void primMST(int graph[MAXV][MAXV]) {
    int parent[MAXV];
    int key[MAXV];
    int mstSet[MAXV];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
        parent[i] = -1;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        if (u == -1) break;
        mstSet[u] = 1;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }

    printMST(parent, graph);
}

int main() {
    int graph[MAXV][MAXV];
    printf("Enter number of vertices: ");
    if (scanf("%d", &V) != 1) return 0;

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);

    primMST(graph);
    return 0;
}
