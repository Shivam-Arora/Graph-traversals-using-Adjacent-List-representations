#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
using namespace std;



struct adjlistnode{
    int dest;
    struct adjlistnode *next;
};

struct adjlist{
    struct adjlistnode *head;
};

struct Graph{
    int V;
    struct adjlist *array;
};

struct adjlistnode * newAdjListNode(int dest){
    struct adjlistnode *newnode=(struct adjlistnode *)malloc(sizeof(struct adjlistnode));
    newnode->dest=dest;
    newnode->next=NULL;

    return newnode;
}
struct Graph *createGraph(int V){
    struct Graph *graph=(struct Graph *)malloc(sizeof(struct Graph));
    graph->V=V;
    graph->array=(struct adjlist*)malloc(V*sizeof(struct adjlist));

    int i=0;
    for(i=0;i<V;i++){
        graph->array[i].head=NULL;
    }

    return graph;
}

void addEdge(struct Graph *graph,int src,int dest){
    struct adjlistnode *temp= newAdjListNode(dest);
    temp->next=graph->array[src].head;
    graph->array[src].head=temp;

    temp=newAdjListNode(src);
    temp->next=graph->array[dest].head;
    graph->array[dest].head=temp;

}

void BFS(struct Graph *graph,int s){
    int visited[graph->V];
    for(int i=0;i<graph->V;i++){
        visited[i]=0;
    }
    queue <int> q;

    q.push(s);
    visited[s]=1;

    while(!q.empty()){
        s=q.front();
        printf(" %d ",s);
        q.pop();
        //break;
        struct adjlistnode *t=graph->array[s].head;

        while(t!=NULL){
            if(!visited[t->dest]){
                q.push(t->dest);
                visited[t->dest]=1;
            }
            t=t->next;

        }
    }

}

void DFSutil(struct Graph *graph,int v,int visited[]){
    visited[v]=1;
    printf(" %d ",v);
    struct adjlistnode *t = graph->array[v].head;

    while(t!=NULL){
        if(!visited[t->dest]){
            DFSutil(graph,t->dest,visited);
        }
        t=t->next;
    }

}

void DFS(struct Graph*graph,int s){
    int visited[graph->V];
    for(int i=0;i<graph->V;i++){
        visited[i]=0;
    }
    DFSutil(graph,s,visited);
}

void printGraph(struct Graph *graph){
    int i;

    for(i=0;i<graph->V;i++){
        printf("\n Adjacency list : %d\n head ", i);
        struct adjlistnode *head=graph->array[i].head;
        while(head){
            printf("--> %d ",head->dest);
            head=head->next;
        }
        printf("\n");

    }

}

int main(){
    int V=5;

    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);


    printGraph(graph);
    printf("\n\n");

    printf("BFS traversals :\n");
    BFS(graph,2);
    printf("\n\n");
    BFS(graph,0);
    printf("\n\n");
    BFS(graph,1);
    printf("\n\n");
    BFS(graph,3);
    printf("\n\n");
    BFS(graph,4);

    printf("\n\n");

    printf("DFS traversals :\n");
    DFS(graph,2);
    printf("\n\n");
    DFS(graph,0);
    printf("\n\n");
    DFS(graph,1);
    printf("\n\n");
    DFS(graph,3);
    printf("\n\n");
    DFS(graph,4);
    return 0;


}

