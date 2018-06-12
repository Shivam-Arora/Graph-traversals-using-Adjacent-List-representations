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
