#include<iostream>
using namespace std;

#define MAX 100

int adjMat[MAX+1][MAX+1];
int resMat[MAX + 1][MAX + 1];
int visitedZ[MAX][MAX];
int visitedN[MAX][MAX];

int visitedRes[MAX][MAX];
int visitedRepZ[MAX][MAX];
int maxarr[MAX+1];
int n,boothcnt;

//functions
void dfs_func1(int i, int j, int x, int y);
void apply_DFS_Z_sub(int i, int j);
void apply_DFS_Z_main();
void apply_DFS_N(int i, int j, int elem);
void apply_DFS_REPLACE(int i, int j, int elem);

int find_max_elem()
{
	int index, num;
	num = 0;
	for(int i = 1; i <= MAX; i++)
	{
		if(maxarr[i] >= num)
		{
			num = maxarr[i];
			index = i;
		}
	}
	return(index);
}





//void dfs_func1(int i, int j, int x, int y){
//	if(x >= 0 && x < n && y >= 0 && y < n){
//		if(adjMat[x][y] == 0 && visitedZ[x][y] == 0){
//			apply_DFS_Z_sub(x, y);
//		}
//		else if(adjMat[x][y]!=0 && visitedN[x][y]==0){
//			apply_DFS_N(x, y, adjMat[x][y]);
//		}
//	}
//}

void apply_DFS_N(int i, int j, int elem){
	maxarr[elem]++;
	visitedN[i][j] = 1;

	int x, y;
	//Checking in all directions.
	//top
	x = i - 1, y = j;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(adjMat[x][y] == elem && visitedN[x][y] == 0){
			apply_DFS_N(x, y, elem);
		}
	}
	//left
	x = i, y = j-1;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(adjMat[x][y] == elem && visitedN[x][y] == 0){
			apply_DFS_N(x, y, elem);
		}
	}
	//right
	x = i , y = j+1;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(adjMat[x][y] == elem && visitedN[x][y] == 0){
			apply_DFS_N(x, y, elem);
		}
	}
	//bottom
	x = i + 1, y = j;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(adjMat[x][y] == elem && visitedN[x][y] == 0){
			apply_DFS_N(x, y, elem);
		}
	}
}

//void apply_DFS_Z_sub(int i, int j){
//	
//	visitedZ[i][j] = 1;
//
//	//top
//	dfs_func1(i, j, i - 1, j);
//	//left
//	dfs_func1(i, j, i, j - 1);
//	//right
//	dfs_func1(i, j, i, j + 1);
//	//bottom
//	dfs_func1(i, j, i + 1, j);
//
//}

void apply_DFS_Z_sub(int i, int j){
	int x, y;
	visitedZ[i][j] = 1;

	//top
	x = i - 1, y = j;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(adjMat[x][y] == 0 && visitedZ[x][y] == 0){
			apply_DFS_Z_sub(x, y);
		}
		else if(adjMat[x][y] != 0 && visitedN[x][y] == 0){
			apply_DFS_N(x, y, adjMat[x][y]);
		}
	}
	//left
	x = i, y = j - 1;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(adjMat[x][y] == 0 && visitedZ[x][y] == 0){
			apply_DFS_Z_sub(x, y);
		}
		else if(adjMat[x][y] != 0 && visitedN[x][y] == 0){
			apply_DFS_N(x, y, adjMat[x][y]);
		}
	}
	//right
	x = i, y = j + 1;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(adjMat[x][y] == 0 && visitedZ[x][y] == 0){
			apply_DFS_Z_sub(x, y);
		}
		else if(adjMat[x][y] != 0 && visitedN[x][y] == 0){
			apply_DFS_N(x, y, adjMat[x][y]);
		}
	}
	//bottom
	x = i + 1, y = j;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(adjMat[x][y] == 0 && visitedZ[x][y] == 0){
			apply_DFS_Z_sub(x, y);
		}
		else if(adjMat[x][y] != 0 && visitedN[x][y] == 0){
			apply_DFS_N(x, y, adjMat[x][y]);
		}
	}
}


void apply_DFS_REPLACE(int i, int j, int elem){
	int x, y;
	visitedRepZ[i][j] = 1;
	resMat[i][j] = elem;
	//top
	x = i - 1;
	y = j;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(resMat[x][y] == 0 && visitedRepZ[i][j] == 0){
			apply_DFS_REPLACE(x, y, elem);
		}
	}
	//left
	x = i;
	y = j - 1;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(resMat[x][y] == 0 && visitedRepZ[i][j] == 0){
			apply_DFS_REPLACE(x, y, elem);
		}
	}
	//right
	x = i;
	y = j + 1;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(resMat[x][y] == 0 && visitedRepZ[i][j] == 0){
			apply_DFS_REPLACE(x, y, elem);
		}
	}
	//bottom
	x = i + 1;
	y = j;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(resMat[x][y] == 0 && visitedRepZ[i][j] == 0){
			apply_DFS_REPLACE(x, y, elem);
		}
	}

}

void apply_DFS_Z_main(){
	int maxelem = 0;

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(adjMat[i][j] == 0 && visitedZ[i][j] == 0){
				apply_DFS_Z_sub(i, j);
				maxelem = find_max_elem();

				apply_DFS_REPLACE(i, j, maxelem);

				for(int p = 0; p < n; p++){
					for(int q = 0; q < n; q++){
						visitedN[p][q] = 0;
					}
				}
				for(int p = 1; p <= n; p++){
					maxarr[p] = 0;
				}
			}
		}
	}

}

void apply_booth_count_SUB(int i, int j, int elem){
	int x, y;
	visitedRes[i][j] = 1;
	//top
	x = i - 1;
	y = j;
	if(x >= 0 && x < n && y >= 0 && y < n){
		if(resMat[x][y] == elem && visitedRes[x][y] == 0){
			apply_booth_count_SUB(x, y, elem);
		}
	}
	//left
	x = i;
	y = j - 1;
	if(x >= 0 && x < n && y >= 0 && y < n)
	{
		if(resMat[x][y] == elem && visitedRes[x][y] == 0)
		{
			apply_booth_count_SUB(x, y, elem);
		}
	}
	//right
	x = i ;
	y = j + 1;
	if(x >= 0 && x < n && y >= 0 && y < n)
	{
		if(resMat[x][y] == elem && visitedRes[x][y] == 0)
		{
			apply_booth_count_SUB(x, y, elem);
		}
	}
	//bottom
	x = i + 1;
	y = j;
	if(x >= 0 && x < n && y >= 0 && y < n)
	{
		if(resMat[x][y] == elem && visitedRes[x][y] == 0)
		{
			apply_booth_count_SUB(x, y, elem);
		}
	}
}


void apply_booth_count(){
	int maxelem = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(visitedRes[i][j] == 0){
				apply_booth_count_SUB(i,j,resMat[i][j]);
				boothcnt++;
			}
		}
	}
}

int main(){
	int t;
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin >> adjMat[i][j];

				resMat[i][j] = adjMat[i][j];
				visitedZ[i][j] = 0;
				visitedN[i][j] = 0;
				visitedRes[i][j] = 0;
				visitedRepZ[i][j] = 0;


			}
			maxarr[i] = 0;
		}
		boothcnt = 0;

		apply_DFS_Z_main();
		apply_booth_count();


	}
}
