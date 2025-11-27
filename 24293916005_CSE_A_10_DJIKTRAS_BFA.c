#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define INF 99999
#define MAX 100

// ------------------- MIN HEAP FOR DIJKSTRA -------------------
typedef struct {
    int vertex;
    int dist;
} HeapNode;

typedef struct {
    HeapNode arr[MAX];
    int size;
} MinHeap;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap *h, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (h->arr[parent].dist > h->arr[idx].dist) {
            swap(&h->arr[parent], &h->arr[idx]);
            idx = parent;
        } else break;
    }
}

void heapifyDown(MinHeap *h, int idx) {
    while (1) {
        int left = 2 * idx + 1, right = left + 1, smallest = idx;
        if (left < h->size && h->arr[left].dist < h->arr[smallest].dist)
            smallest = left;
        if (right < h->size && h->arr[right].dist < h->arr[smallest].dist)
            smallest = right;
        if (smallest != idx) {
            swap(&h->arr[smallest], &h->arr[idx]);
            idx = smallest;
        } else break;
    }
}

void push(MinHeap *h, int v, int dist) {
    h->arr[h->size].vertex = v;
    h->arr[h->size].dist = dist;
    heapifyUp(h, h->size);
    h->size++;
}

HeapNode pop(MinHeap *h) {
    HeapNode top = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    heapifyDown(h, 0);
    return top;
}

// ------------------- DIJKSTRA USING ARRAY -------------------
void dijkstra_array(int graph[MAX][MAX], int V, int start) {
    int dist[MAX], visited[MAX]={0};

    for(int i=0;i<V;i++) dist[i]=INF;
    dist[start]=0;

    printf("\nDijkstra (Array/Linear Search) Output:\n");

    for(int count=0;count<V-1;count++) {
        int u=-1;

        for(int i=0;i<V;i++)
            if(!visited[i] && (u==-1 || dist[i]<dist[u]))
                u = i;

        visited[u] = 1;

        for(int v=0;v<V;v++)
            if(graph[u][v] && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    for(int i=0;i<V;i++)
        printf("Node %d → Cost: %d\n", i, dist[i]);
}

// ------------------- DIJKSTRA USING MIN HEAP -------------------
void dijkstra_heap(int graph[MAX][MAX], int V, int start) {
    int dist[MAX];
    for (int i = 0; i < V; i++) dist[i] = INF;

    MinHeap h;
    h.size = 0;

    dist[start] = 0;
    push(&h, start, 0);

    printf("\nDijkstra (Min Heap/Priority Queue) Output:\n");

    while (h.size > 0) {
        HeapNode node = pop(&h);
        int u = node.vertex;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                push(&h, v, dist[v]);
            }
        }
    }

    for (int i = 0; i < V; i++)
        printf("Node %d → Cost: %d\n", i, dist[i]);
}

// ------------------- BELLMAN-FORD -------------------
void bellman_ford(int graph[MAX][MAX], int V, int start) {
    int dist[MAX];
    for(int i=0;i<V;i++) dist[i]=INF;
    dist[start]=0;

    printf("\nBellman-Ford Output:\n");

    for(int i=0;i<V-1;i++) {
        for(int u=0;u<V;u++) {
            for(int v=0;v<V;v++) {
                if(graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    for(int u=0;u<V;u++)
        for(int v=0;v<V;v++)
            if(graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                printf("Negative cycle detected!\n");
                return;
            }

    for(int i=0;i<V;i++)
        printf("Node %d → Cost: %d\n", i, dist[i]);
}

// ------------------- MAIN -------------------
int main() {
    int V, E;
    int graph[MAX][MAX] = {0};

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges u v w:\n");
    for(int i=0;i<E;i++) {
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;   // directed graph
    }

    int start;
    printf("Enter starting node: ");
    scanf("%d", &start);

    dijkstra_array(graph, V, start);
    dijkstra_heap(graph, V, start);
    bellman_ford(graph, V, start);

    return 0;
}
