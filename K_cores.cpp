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
			cout << "[" << i << "]" ;	// Printing Vertice and it's Core
			struct adjlistnode *temp = graph->array[i].head;
			while(temp!=NULL){
				if(arr[temp->dest]>=k){
					cout << " -> " << temp->dest << " "; //printing K-Cores
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
	
	
	
	We have a game where an airplane is placed in the middle column of the bottom row. The airplane can move right or left by one step and in every step the row moves down. When the airplane meets ‘1’ (coin) the number of points increase by 1 and when the airplane meets ‘2’ (bomb) the number of points decrease by 1. Whenever the airplane meets the bomb with score 0 the airplane dies and game is over. The user has one detonate option throughout the game where he can detonate all the bombs in the next 5 rows. Find the maximum number of points (coins) that can be collected by the user. Number of rows 1 <= N <= 12. Return -1 if score < 0*/

	
	
	
	
	/*
	
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX 16

///////////// Method #1

int N, M;
int cells[MAX][MAX];
int visited[MAX][MAX];
int maxcount;

int odir[2][6] = { { 0, 0, -1, 1, 1, 1 },
					{ -1, 1, 0, 1, -1, 0 } };
int edir[2][6] = { { -1, -1, -1, 0, 1, 0 },
					{ -1, 1, 0, 1, 0, -1 } };


int isvalid(int i, int j){
	if (i < 0 || i >= N || j < 0 || j >= M)
		return 0;
	return 1;
}
int findmaxscore(int cX, int cY, int count, int curValue){

	int i, nX, nY;
	if (count == 4){
		if (maxcount < curValue){
			maxcount = curValue;
		}
		return;
	}

	for (i = 0; i < 6; i++){
		if (cY % 2 == 0){
			nX = cX + edir[0][i];
			nY = cY + edir[1][i];
		}
		else{
			nX = cX + odir[0][i];
			nY = cY + odir[1][i];
		}

		if (isvalid(nX, nY) && visited[nX][nY] == 0){
			visited[nX][nY] = 1;
			findmaxscore(cX, cY, count + 1, curValue + cells[nX][nY]);
			findmaxscore(nX, nY, count + 1, curValue + cells[nX][nY]);
			visited[nX][nY] = 0;
		}
	}
}

///////////// Method #2

int Hcells[MAX * 2][MAX];
int visit2[MAX * 2][MAX];
int gmaxcore;

int dir[2][6] = { { -1, 1, 2, 1, -1, -2 },
					{ 1, 1, 0, -1, -1, 0 } };

int issafe(int i, int j){
	if (i < 0 || i >= N * 2 || j < 0 || j >= M)
		return 0;
	return 1;
}
int findmax2(int cX, int cY, int count, int curValue){

	int i, nX, nY;
	if (count == 4){
		if (gmaxcore < curValue){
			gmaxcore = curValue;
		}
		return;
	}

	for (i = 0; i < 6; i++){
		nX = cX + dir[0][i];
		nY = cY + dir[1][i];

		if (issafe(nX, nY) && visit2[nX][nY] == 0){
			visit2[nX][nY] = 1;
			findmax2(cX, cY, count + 1, curValue + Hcells[nX][nY]);
			findmax2(nX, nY, count + 1, curValue + Hcells[nX][nY]);
			visit2[nX][nY] = 0;
		}
	}
}



int main(void)
{
	int T, test_case;

	freopen("input.txt", "r", stdin);

	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (test_case = 0; test_case < T; test_case++)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Implement your algorithm here.
		The answer to the case will be stored in variable Answer.
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////

		int i, j, k, l;
		scanf("%d %d", &N, &M);

		for (i = 0; i < N; i++){
			for (j = 0; j < M; j++){
				scanf("%d", &cells[i][j]);
			}
		}

		maxcount = 0;
		for (i = 0; i < N; i++){
			for (j = 0; j < M; j++){
				visited[i][j] = 1;
				findmaxscore(i, j, 1, cells[i][j]);
				visited[i][j] = 0;
			}
		}

		//////////// Method 2  ////////////

		int x, y;
		for (i = 0, x = 0; i < N; i++, x += 2){
			for (j = 0; j < M; j++){
				if (j % 2 == 0)
					Hcells[x][j] = cells[i][j];
				else
					Hcells[x + 1][j] = cells[i][j];
			}
		}

		gmaxcore = 0;
		for (i = 0; i < N * 2; i++){
			for (j = 0; j < M; j++){
				if (Hcells[i][j] != 0){
					visit2[i][j] = 1;
					findmax2(i, j, 1, Hcells[i][j]);
					visit2[i][j] = 0;
				}
			}
		}

		// Print the answer to standard output(screen).
		printf("%d\n", maxcount*maxcount);
		printf("%d\n", gmaxcore*gmaxcore);

	}

	return 0;//Your program should return 0 on normal termination.
}

	
	Four 5G base station towers needs to be installed in a  Landscape which is divided as hexagon cells as shown in Fig below, which also contains number of people living in each cell. Need to find four cells  to install the 5G towers which can cover maximum number of people  combining all four cells, with below conditions
Only one tower can be placed in a cell
Each of the four chosen cell should be neighbor to atleast one of the remaining 3 cells. 
All four cells should be connected  (like  one island)
Input range:  1 <= N, M <= 15
Sample input Format for Fig in right
3 4
150 450 100 320
120 130 160 110
10 60 200 220

Output
Square of  Maximum number of people covered by 4 towers

	*/
	/*
	/*There will be a N Balloons marked with value Bi (where B(i…N)).
User will be given Gun with N Bullets and user must shot N times.
When any balloon explodes then its adjacent balloons becomes next to each other.
User has to score highest points to get the prize and score starts at 0.
Below is the condition to calculate the score.
When Balloon Bi Explodes then score will be a product of Bi-1 & Bi+1 (score = Bi-I * Bi+1).
When Balloon Bi Explodes and there is only left Balloon present then score will be Bi-1.
When Balloon Bi Explodes and there is only right Balloon present then score will be Bi+1.
When Balloon Bi explodes and there is no left and right Balloon present then score will be Bi.
Write a program to score maximum points.
Conditions:
Execution time limits 3 seconds.
No of Balloons N, where 1 <= N <= 10
Bi value of the Balloon 1 <= Bi <= 1000.
No two Balloons explode at same time.


Input:
Consists of TC (1 <= TC <= 50).
N – No of Balloons.
B0…..BN  N Balloons with their values .
Output: 
#TC SCORE

Sample Input:
5
4
1 2 3 4
5
3 10 1 2 5
7
12 48 28 21 67 75 85
8
245 108 162 400 274 358 366 166
10
866 919 840 944 761 895 701 912 848 799
 

Sample Output:
#1 20
#2 100
#3 16057
#4 561630
#5 6455522

*/

#include<iostream>
using namespace std;
int balloon[100];

int getmaxpoint(int l,int r,int n)
{
  int maxscore=0;
  for(int i=l+1;i<=r-1;i++)
  {
    int current_sum=0;
    current_sum=getmaxpoint(l,i,n)+getmaxpoint(i,r,n);
    if(l==0 && r==n+1)
    current_sum=current_sum+balloon[i];
    else
    current_sum=current_sum+balloon[l]*balloon[r];
    cout<<"l= "<<l<<" "<<"r="<<r<<" "<<"i= "<<i<<" "<<"current_sum= "<< current_sum<<endl;
    if(current_sum>maxscore)
    maxscore=current_sum;
  }
  return maxscore;
}



int main()
{
  int t,n;
  cin>>t;
  while(t--)
  {
    cin>>n;
    balloon[0]=1;
    balloon[n+1]=1;
    for(int i=1;i<=n;i++)
    {
      cin>>balloon[i];
    }
    
    int ans=getmaxpoint(0,n+1,n);
    cout<<ans<<endl;
  }
  return 0;
  
  
}
	*/

		
		
		/*
		// GalaxyYesSix.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_N 100

char adjM[MAX_N + 1][MAX_N + 1];
char resM[MAX_N + 1][MAX_N + 1];
char visitedZ[MAX_N][MAX_N];
char visitedN[MAX_N][MAX_N];
char visitedRepZ[MAX_N][MAX_N];
char visitedRes[MAX_N][MAX_N];

#define TOP(i,j,x,y) (x=i-1,y=j);
#define LEFT(i,j,x,y) (x=i,y=j-1);
#define RIGHT(i,j,x,y) (x=i,y=j+1);
#define BOTTOM(i,j,x,y) (x=i+1,y=j);

#define DFS_Z_SUB_COND	if(( x >=0 && x < N ) && ( y >= 0 && y < N))\
{ \
if ((adjM[x][y] == 0) && (!visitedZ[x][y])) \
{\
	applyDFS_Z_Sub(x, y); \
}\
							else if ((adjM[x][y] != 0) && (!visitedN[x][y])) \
{\
	applyDFS_N(x, y, adjM[x][y]); \
}\
}

#define DFS_N_COND( adjMat, num, funcDFS, visited)	if(( x >=0 && x < N ) && ( y >= 0 && y < N))\
{\
if ((adjMat[x][y] == (num)) && (!visited[x][y]))\
{\
	funcDFS(x, y, (num)); \
}\
}

#define DFS_Z_REPLACE_COND(num, resMat)	if(( x >=0 && x < N ) && ( y >= 0 && y < N))\
{\
if ((resMat[x][y] == 0) && (!visitedRepZ[x][y]))\
{\
	applyDFS_Z_replace(x, y, (num)); \
}\
}

int maxArr[MAX_N + 1];
int N;
int boothCnt;

int findMaxElem()
{
	int i;
	int max = 0;
	int num;
	for (i = 1; i <= MAX_N; i++)
	{
		if (maxArr[i] >= max)
		{
			max = maxArr[i];
			num = i;
		}
	}

	return num;
}

void applyDFS_Z_replace(int i, int j, int num)
{
	int x, y;
	visitedRepZ[i][j] = 1;
	resM[i][j] = num;

	//Top
	TOP(i, j, x, y)
		DFS_Z_REPLACE_COND(num, resM)

		//Left
		LEFT(i, j, x, y)
		DFS_Z_REPLACE_COND(num, resM)

		//Right
		RIGHT(i, j, x, y)
		DFS_Z_REPLACE_COND(num, resM)

		//Bottom
		BOTTOM(i, j, x, y)
		DFS_Z_REPLACE_COND(num, resM)
}


void applyDFS_N(int i, int j, int elem)
{
	int x, y;

	visitedN[i][j] = 1;
	maxArr[elem]++;

	//Top
	TOP(i, j, x, y)
		DFS_N_COND(adjM, elem, applyDFS_N, visitedN)

		//Left
		LEFT(i, j, x, y)
		DFS_N_COND(adjM, elem, applyDFS_N, visitedN)

		//Right
		RIGHT(i, j, x, y)
		DFS_N_COND(adjM, elem, applyDFS_N, visitedN)

		//Bottom
		BOTTOM(i, j, x, y)
		DFS_N_COND(adjM, elem, applyDFS_N, visitedN)
}

void applyDFS_Z_Sub(int i, int j)
{
	int x, y;
	visitedZ[i][j] = 1;

	//Top
	TOP(i, j, x, y)
		DFS_Z_SUB_COND

		//Left
		LEFT(i, j, x, y)
		DFS_Z_SUB_COND

		//Right
		RIGHT(i, j, x, y)
		DFS_Z_SUB_COND

		//Bottom
		BOTTOM(i, j, x, y)
		DFS_Z_SUB_COND
}

void applyDFS_Z_Main()
{
	int i, j;
	int maxElem = 0;
	int p, q;

	for (i = 0; i<N; i++)
	{
		for (j = 0; j<N; j++)
		{
			if (adjM[i][j] == 0 && !visitedZ[i][j])
			{
				applyDFS_Z_Sub(i, j);
				maxElem = findMaxElem();
				applyDFS_Z_replace(i, j, maxElem);
				for (p = 0; p<N; p++)
				{
					for (q = 0; q<N; q++)
					{
						visitedN[p][q] = 0;
					}
				}

				for (p = 1; p <= N; p++)
					maxArr[p] = 0;

			}
		}
	}
}

void applyDFS_Count_Booths_Sub(int i, int j, int num)
{
	int x, y;
	visitedRes[i][j] = 1;

	//Top
	TOP(i, j, x, y)
		DFS_N_COND(resM, num, applyDFS_Count_Booths_Sub, visitedRes)

		//Left
		LEFT(i, j, x, y)
		DFS_N_COND(resM, num, applyDFS_Count_Booths_Sub, visitedRes)

		//Right
		RIGHT(i, j, x, y)
		DFS_N_COND(resM, num, applyDFS_Count_Booths_Sub, visitedRes)

		//Bottom
		BOTTOM(i, j, x, y)
		DFS_N_COND(resM, num, applyDFS_Count_Booths_Sub, visitedRes)
}

void applyDFS_Count_Booths()
{
	int i, j;
	int maxElem = 0;

	for (i = 0; i<N; i++)
	{
		for (j = 0; j<N; j++)
		{
			if (!visitedRes[i][j])
			{
				applyDFS_Count_Booths_Sub(i, j, resM[i][j]);
				boothCnt++;
			}
		}
	}
}


int main()
{
	int T;
	int testCase, i, j;
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for (testCase = 1; testCase <= T; testCase++)
	{
		scanf("%d", &N);

		for (i = 0; i<N; i++)
		{
			for (j = 0; j<N; j++)
			{
				scanf("%d", &adjM[i][j]);
				resM[i][j] = adjM[i][j];
				visitedN[i][j] = 0;
				visitedZ[i][j] = 0;
				visitedRepZ[i][j] = 0;
				visitedRes[i][j] = 0;
			}
			maxArr[i] = 0;
		}

		boothCnt = 0;

		applyDFS_Z_Main();
		applyDFS_Count_Booths();

		printf("\r\n #%d: %d", testCase, boothCnt);
	}
}
		*/
