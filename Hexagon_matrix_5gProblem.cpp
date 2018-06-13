#include<iostream>
#include<vector>
using namespace std;

#define N 16
int cells[N][N];
int visited[N][N];
int maxct;

int n,m;
int odd_ord[2][6]={{0,0,-1,1,1,1},{-1,1,0,0,1,-1}};
int even_ord[2][6]={{0,0,-1,1,-1,-1},{-1,1,0,0,1,1}};

vector<int> path;

int isSafe(int x,int y){
	if(x<n && x>=0 && y<m && y>=0){
		return 1;
	}
	else{
		return 0;
	}
}

void dfs(int x,int y,int count,int curr_sum){
	if(count==4){
		if(curr_sum > maxct){
			maxct=curr_sum;
			for(int k=0;k<path.size();k++){
				cout << path[k] << " ";
			}
			cout << " - " <<  maxct <<endl << endl;
			return;
		}
	}
	else{
		int nx,ny;
		for(int i=0;i<6;i++){
			if(x%2==0){
				nx=x+even_ord[0][i];
				ny=y+even_ord[1][i];
			}
			else{
				nx=x+odd_ord[0][i];
				ny=x+odd_ord[1][i];
			}
			
			if(isSafe(nx,ny) && visited[nx][ny]==0 ){
				visited[nx][ny]=1;
				path.push_back(cells[nx][ny]);
				dfs(nx,ny,count+1,curr_sum+cells[nx][ny]);
				path.pop_back();
				visited[nx][ny]=0;
			}
			
		}
	}
}

int main(){
	int i, j, k, l;
	scanf("%d %d", &n, &m);

	for (i = 0; i < n; i++){
		for (j = 0; j < m; j++){
			scanf("%d", &cells[i][j]);
		}
	}
	maxct=0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			visited[i][j]=1;
			path.push_back(cells[i][j]);
			dfs(i,j,1,cells[i][j]);
			visited[i][j]=0;
			path.clear();
		}
	}
	cout << maxct << endl;
}
