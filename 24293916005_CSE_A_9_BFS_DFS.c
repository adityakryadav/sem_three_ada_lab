/* Program 8: BFS and DFS using Adjacency Matrix and Adjacency List */

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// ---------- Adjacency List Node ----------
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// ---------- Queue for BFS ----------
int queue[MAX], front = -1, rear = -1;

void enqueue(int v) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = v;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

// ---------- BFS ----------
void BFS_matrix(int matrix[MAX][MAX], int visited[], int V, int start) {
    enqueue(start);
    visited[start] = 1;

    printf("BFS (Adjacency Matrix): ");

    while (front <= rear) {
        int u = dequeue();
        printf("%d ", u);

        for (int v = 0; v < V; v++) {
            if (matrix[u][v] == 1 && !visited[v]) {
                visited[v] = 1;
                enqueue(v);
            }
        }
    }
    printf("\n");
}

// ---------- DFS ----------
void DFS_matrix(int matrix[MAX][MAX], int visited[], int V, int start) {
    visited[start] = 1;
    printf("%d ", start);

    for (int v = 0; v < V; v++) {
        if (matrix[start][v] == 1 && !visited[v]) {
            DFS_matrix(matrix, visited, V, v);
        }
    }
}

// ---------- Adjacency List Creation ----------
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// ---------- BFS using Adjacency List ----------
void BFS_list(Node* adjList[], int visited[], int V, int start) {
    front = rear = -1;
    enqueue(start);
    visited[start] = 1;

    printf("BFS (Adjacency List): ");

    while (front <= rear) {
        int u = dequeue();
        printf("%d ", u);

        Node* temp = adjList[u];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                enqueue(temp->vertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// ---------- DFS using Adjacency List ----------
void DFS_list(Node* adjList[], int visited[], int start) {
    visited[start] = 1;
    printf("%d ", start);

    Node* temp = adjList[start];
    while (temp != NULL) {
        int v = temp->vertex;
        if (!visited[v])
            DFS_list(adjList, visited, v);
        temp = temp->next;
    }
}

int main() {
    int V, E, u, v, start;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int matrix[MAX][MAX] = {0};
    Node* adjList[MAX];

    for (int i = 0; i < V; i++)
        adjList[i] = NULL;

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        matrix[u][v] = matrix[v][u] = 1;

        Node* newNode = createNode(v);
        newNode->next = adjList[u];
        adjList[u] = newNode;

        newNode = createNode(u);
        newNode->next = adjList[v];
        adjList[v] = newNode;
    }

    printf("Enter starting node: ");
    scanf("%d", &start);

    int visited[MAX] = {0};
    BFS_matrix(matrix, visited, V, start);

    for (int i = 0; i < V; i++) visited[i] = 0;
    printf("DFS (Adjacency Matrix): ");
    DFS_matrix(matrix, visited, V, start);
    printf("\n");

    for (int i = 0; i < V; i++) visited[i] = 0;
    BFS_list(adjList, visited, V, start);

    for (int i = 0; i < V; i++) visited[i] = 0;
    printf("DFS (Adjacency List): ");
    DFS_list(adjList, visited, start);
    printf("\n");

    return 0;
}
