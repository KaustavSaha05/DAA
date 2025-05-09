#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXNODES 100

int adjMatrix[MAXNODES][MAXNODES];
int numnodes;

void initializematrix(int nodes){
    numnodes = nodes;
    for(int i=0; i<numnodes; i++){
        for(int j=0; j<numnodes; j++){
            adjMatrix[i][j] = 0;
        }
    }
}

void addedge(int u, int v){
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}

void printmatrix(){
    for(int i=0; i<numnodes; i++){
        for(int j=0; j<numnodes; j++){
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

bool visitedDFS[MAXNODES];

void DFS(int startnode){
    visitedDFS[startnode]=true;
    printf("%d ", startnode);

    for(int i=0; i<numnodes; i++){
        if(adjMatrix[startnode][i] == 1 && !visitedDFS[i]){
            DFS(i);
        }
    }
}

void BFS(int startnode){
    bool visitedBFS[MAXNODES] = {false};
    int queue[MAXNODES], front=0, rear=0;

    queue[rear++]=startnode;
    visitedBFS[startnode]=true;

    while(front<rear){
        int currentnode = queue[front++];
        printf("%d ", currentnode);
        for(int i=0; i<numnodes; i++){
            if(adjMatrix[currentnode][i] == 1 && !visitedBFS[i]){
                    queue[rear++] = i;
                    visitedBFS[i]=true;
            }
        }
    }
}
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAXNODES];


void initializeList(int nodes){
    numnodes = nodes;
    for(int i=0; i<nodes; i++){
        adjList[i] = NULL;
    }
}

void addEdge(int u, int v){
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->vertex = v;
    newnode->next = adjList[u];
    adjList[u] = newnode;

    newnode = (Node*)malloc(sizeof(Node));
    newnode->vertex = u;
    newnode->next = adjList[v];
    adjList[v] = newnode;
}

void printlist(){
    for(int i=0; i<numnodes; i++){
        printf("%d: ", i);
        Node* temp = adjList[i];
        while(temp){
            printf("%d ->", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

bool visitedDFS[MAXNODES];

void DFS_List(int startnode){
    visitedDFS[startnode]= true;
    printf("%d", startnode);
    Node* temp = adjList[startnode];
    while(temp){
        if(!visitedDFS[temp->vertex]){
            DFS_List(temp->vertex);
        }
        temp = temp->next;
    }
}

void BFS_List(int startnode){
    bool visitedBFS[MAXNODES] = {false};
    int queue[MAXNODES], front=0, rear=0;
    queue[rear++] = startnode;
    visitedBFS[startnode] = true;

    while(front<rear){
        int currentnode = queue[front++];
        printf("%d ", currentnode);
        Node* temp = adjList[currentnode];
        while (temp){
            if(!visitedBFS[temp->vertex]){
                queue[rear++] = temp->vertex;
                visitedBFS[temp->vertex] = true;
            }
            temp = temp->next;
        }
    }
}

int main(){
    int nodes = 6;
    printf("--- Adjacency matrix ---\n");
    initializematrix(nodes);
    addedge(0,1);
    addedge(0,2);
    addedge(1,3);
    addedge(1,4);
    addedge(2,5);
    printmatrix();

    printf("DFS (Matrix): ");
    for (int i = 0; i < nodes; i++) visitedDFS[i] = false;
    DFS(0);
    printf("\n");

    printf("BFS (Matrix): ");
    BFS(0);
    printf("\n\n");

    printf("--- Adjacency List ---\n");
    initializeList(nodes);
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 5);
    printlist();

    printf("DFS (List): ");
    for (int i = 0; i < nodes; i++) visitedDFS[i] = false;
    DFS_List(0);
    printf("\n");

    printf("BFS (List): ");
    BFS_List(0);
    printf("\n");
}