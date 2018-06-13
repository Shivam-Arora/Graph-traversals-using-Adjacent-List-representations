#include<iostream>
#include<queue>
#include<malloc.h>
#include<limits.h>
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

    int i;
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

int dfsutil(int v,int *visited,int *arr,struct Graph *graph,int k){
	visited[v]=1;

	struct adjlistnode *temp=graph->array[v].head;
	while(temp!=NULL){
		int curr=temp->dest;		
		if(arr[v]<k)
			arr[curr]--;
		if(visited[curr]==0){
			if(dfsutil(curr,visited,arr,graph,k)==1){
				arr[v]--;
			}
		}
		temp=temp->next;
	}
	if(arr[v]<k){
		return 1;
	}
	else{
		return 0;
	}
}

void printKCores(struct Graph *graph,int k){
	int arr[graph->V]; 
	for(int i=0;i<graph->V;i++){	
        struct adjlistnode *head=graph->array[i].head;
        int ct=0;
		while(head!=NULL){
			ct++;
      		head=head->next;
        }
        arr[i]=ct;
    }	
    
	int mindeg=INT_MAX;
	int start=0;
	for(int i=0;i<graph->V;i++){
		if(arr[i]<=mindeg){
			mindeg=arr[i];
			start=i;
		}
	}
	int visited[graph->V];
	for(int i=0;i<graph->V;i++){
		visited[i]=0;
	}
  
	dfsutil(start,visited,arr,graph,k);
	
  	for(int i=0;i<graph->V;i++){
		if(visited[i]==0){
			dfsutil(i,visited,arr,graph,k);
		}
	}
	cout << "K-CORES PRINTING" << endl;
	for(int i=0;i<graph->V;i++){
		if(arr[i]>=k){
			cout << "[" << i << "]" ;	
			struct adjlistnode *temp = graph->array[i].head;
			while(temp!=NULL){
				if(arr[temp->dest]>=k){
					cout << " -> " << temp->dest << " ";
				}
				temp=temp->next;
			}
			cout << endl;
		}
		
	}	
}

int main(){
	int k = 3;
    struct Graph* g1 = createGraph(9);
    addEdge(g1,0, 1);
    addEdge(g1,0, 2);
    addEdge(g1,1, 2);
    addEdge(g1,1, 5);
    addEdge(g1,2, 3);
    addEdge(g1,2, 4);
    addEdge(g1,2, 5);
    addEdge(g1,2, 6);
    addEdge(g1,3, 4);
    addEdge(g1,3, 6);
    addEdge(g1,3, 7);
    addEdge(g1,4, 6);
    addEdge(g1,4, 7);
    addEdge(g1,5, 6);
    addEdge(g1,5, 8);
    addEdge(g1,6, 7);
    addEdge(g1,6, 8);
    
    //cout << "sddsd";
	printKCores(g1,k);
 
    cout << endl << endl;	
}
/*
#include<stdio.h>
#include<stdlib.h>

//  \  "\n"
//   ||
struct adjlistnode{
    int data;
    struct adjlistnode *next;
};
struct adjlist{
    struct adjlistnode *head;
};
struct graph{
    int v;
    struct adjlist *arr;
};
struct qnode{
    int data;
    struct qnode *next;
};
struct queue{
    struct qnode *front;
    struct qnode *rear;
};
struct qnode * newqnode(int data){
    struct qnode *temp=(struct qnode *)malloc(sizeof(struct qnode));
    temp->data=data;
    temp->next=NULL;
    return temp;
}
struct queue *createqueue(){
    struct queue* temp=(struct queue *)malloc(sizeof(struct queue));
    temp->front=NULL;
    temp->rear=NULL;
    return temp;
}
void push_in_queue(struct queue *q,int data){
    struct qnode *temp = newqnode(data);
    if(q->rear==NULL){
        q->front=q->rear=temp;
        return;
    }
    q->rear->next=temp;
    q->rear=temp;
}
struct qnode* pop_from_queue(struct queue *q){
    if(q->front==NULL){
        return NULL;
    }
    struct qnode *temp=q->front;
    q->front=q->front->next;

    if(q->front==NULL){
        q->rear=NULL;
    }
    return temp;
}
int isEmpty(struct queue *q){
    if(q->rear==NULL){
        return 1;
    }
    else{
        return 0;
    }
}
struct adjlistnode* new_adjlistnode(int data){
    struct adjlistnode *temp=(struct adjlistnode*)malloc(sizeof(struct adjlistnode));
    temp->data=data;
    temp->next=NULL;
    return temp;
}
struct graph* creategraph(int v){
    struct graph* temp=(struct graph *)malloc(sizeof(struct graph));
    temp->v=v;
    temp->arr=(struct adjlist *)malloc(v*sizeof(struct adjlist));

    int i;
    for(i=0;i<v;i++){
        temp->arr[i].head=NULL;
    }
    return temp;
}
void addedge(struct graph *g,int src,int dest){
    struct adjlistnode *temp=new_adjlistnode(dest);
    temp->next = g->arr[src].head;
    g->arr[src].head=temp;

    temp=new_adjlistnode(src);
    temp->next=g->arr[dest].head;
    g->arr[dest].head=temp;
}
void BFS(struct graph *g,int s){
    int visited[g->v];
    int i;
    for(i=0;i<g->v;i++){
        visited[i]=0;
    }
    visited[s]=1;

    struct queue *q=createqueue();
    push_in_queue(q,s);

    while(isEmpty(q)==0){
        struct qnode *f= q->front;
        printf("%d\n",f->data);
        pop_from_queue(q);

        struct adjlistnode *t=g->arr[f->data].head;

        while(t!=NULL){
            if(visited[t->data]==0){
                push_in_queue(q,t->data);
                visited[t->data]=1;
            }
            t=t->next;
        }
    }
}
void printGraph(struct graph *g){
    int i;
    for(i=0;i<g->v;i++){
        printf("\n Adjacency list : %d\n head ", i);
        struct adjlistnode *head=g->arr[i].head;
        while(head!=NULL){
            printf("--> %d ",head->data);
            head=head->next;
        }
        printf("\n");
    }
}
int main(){
    int v=5;

    struct graph *g=creategraph(v);
    addedge(g,0,1);
    addedge(g,0,4);
    addedge(g,1,2);
    addedge(g,1,3);
    addedge(g,1,4);
    addedge(g,2,3);
    addedge(g,3,4);

    printGraph(g);

    printf("\n\n");

    BFS(g,2);

}
//   "\n"

*/
