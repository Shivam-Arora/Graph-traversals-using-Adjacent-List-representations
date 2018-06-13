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
/*

//DFS SOLUTION
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 50

clock_t start, end;
double cpu_time_used;

int matrix[MAX_SIZE][MAX_SIZE];
int visited_matrix[MAX_SIZE][MAX_SIZE];

int move[4][2] = {
	1, 0,
	-1, 0,
	0, -1,
	0, 1
};

int check_for_level(int dest_x, int dest_y);
int check_for_last_row(int dest_x, int dest_y, int level);

int row = 0;
int col = 0;

int prob(int x)
{
	if (rand() % 100 < x)
		return 1;
	else
		return 0;
}

void init_visited_matrix()
{
	int i, j;
	for (i = 0; i < MAX_SIZE; i++)
	for (j = 0; j < MAX_SIZE; j++)
		visited_matrix[i][j] = 0;
}

void print_matrix(int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

int main()
{
	srand(10);
	int i, j, m, n, p, t, ans, loc_x, loc_y;
	int tc = 50;
	start = clock();
	for (t = 0; t < tc; t++)
	{
		m = 20 + rand() % 30;
		n = 20 + rand() % 30;

		//For safety, fill the whole matrix with -1 to start with
		for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			matrix[i][j] = -1;


		//Fill the left corner with 2
		matrix[m - 1][0] = 2;

		//Fill the last line with all 1
		for (i = 1; i < n; i++)
			matrix[m - 1][i] = 1;

		//Pick a random location and fill it with 3
		loc_x = rand() % m;
		loc_y = rand() % n;
		matrix[loc_x][loc_y] = 3;

		//pick a random probability between 40 to 60 to fill with 1
		p = 0 + rand() % 20;

		//fill the rest of the matrix with 1s and 0s with probability p

		for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		{
			if (-1 == matrix[i][j])
			{
				if (prob(p))
					matrix[i][j] = 1;
				else
					matrix[i][j] = 0;
			}
		}
		row = m;
		col = n;
		//print_matrix(m,n);
		
		ans = check_for_level(loc_x, loc_y);
		
		//printf("Row %d Col %d Loc_x %d Loc_y %d\n", m, n, loc_x, loc_y);
		printf("Case#%d: %d\n", t, ans);

	}
	end = clock();
	cpu_time_used = ((double)(end - start));
	printf("%lf\n", cpu_time_used);
	return 0;
}

int check_for_level(int dest_x, int dest_y)
{
	int level = 1;
	while (1)
	{
		init_visited_matrix();
		visited_matrix[dest_x][dest_y] = 1;
		if (1 == check_for_last_row(dest_x, dest_y, level))
		{
			return level;
		}
		level++;
	}
}

int check_for_last_row(int dest_x, int dest_y, int level)
{
	if (dest_x == row-1)
		return 1;

	int k, temp_x, temp_y;
	for (k = 0; k < (2 + 2 * level); k++)
	{
		if (k < 4)
		{
			temp_y = dest_y + move[k][1];
			temp_x = dest_x + move[k][0];
		}
		else
		{
			temp_y = dest_y;
			temp_x = dest_x + (k/2)*move[k%2][0];
		}
		if (temp_x >= 0 && temp_y >= 0 && temp_x < row && temp_y < col)
		{
			if (matrix[temp_x][temp_y] == 1 && visited_matrix[temp_x][temp_y] == 0)
			{
				visited_matrix[temp_x][temp_y] = 1;
				if (1 == check_for_last_row(temp_x, temp_y, level))
					return 1;
			}
		}
	}
	return 0;
}
/*
There is a man who wants to climb a rock from a starting point to the destination point. Given a map of the rock mountain which N = height, M = width. In the map, character '-' is the possible foot place spot (where can climb).
He can freely move up/down at vertical spots which '-' exists sequentially. It's impossible to move horizontally in case there is more than one space between '-' in the same height level.
Depending on how high/low he moves towards the upper or lower direction at one time, the level of difficulty of rock climbing gets determined.
The maximum height of moving from the starting point to destination point is the level of difficulty of rock climbing .
The total distance of movement is not important. There are more than one path from the starting point to destination point. => Output: The minimum level of difficulty of all rock climbing paths level.
Hint: Start with difficulty level 0 and then keep increasing it one by one.
*/ 
*/
	/*
	SAMPLE CODE #include <iostream> using namespace std; int a[13][5], b[5][5];
void detonate(int row){ for (int i = row; i > row - 5; i--){ for (int j = 0; j < 5; j++){ b[row - i][j] = 0; if (i >= 0 && a[i][j] == 2) { b[row - i][j] = 2; a[i][j] = 0; } } } } void unDetonate(int row){ for (int i = row; i > row - 5; i--){ for (int j = 0; j < 5; j++) { if (i >= 0 && b[row - i][j] == 2) { a[i][j] = 2; } } } }
void getMaxCoins(int pos, int coins, int n, int &maxCoins){
if (pos < 0 || pos > 4 || coins < 0) return;
if (a[n - 1][pos] == 2) coins -= 1; else if (a[n - 1][pos] == 1) coins += 1;
if (n == 1){ if (coins > maxCoins) maxCoins = coins; return; } else{ // 3 options // move right getMaxCoins(pos + 1, coins, n - 1,
	*/
