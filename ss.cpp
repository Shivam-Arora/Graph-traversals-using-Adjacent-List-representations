
#include<iostream>
#include<vector>
using namespace std;

int mat[20][20];
int visited[20][20];
int n, m;

int even[6][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {-1, -1}, {-1, 1}};
int odd[6][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}, {1, -1}, {1, 1}};
int finalans;

vector<int>vec;

void init(){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			visited[i][j] = 0;
		}
	}
}
bool issafe(int row, int col){
	if(row >= 0 && row <= n - 1 && col >= 0 && col <= m - 1){
		return true;
	}
	else{
		return false;
	}
}

void solve(int x,int y,int curr_cost, int count){
	if(count == 4){
		if(curr_cost>finalans){
			finalans=curr_cost;
		}
		return;
	}

	if(y % 2 == 0)
	{
		int curr_row, curr_col;
		for(int i = 0; i < 6; i++){
			curr_row = x + even[i][0];
			curr_col = y + even[i][1];

			if(visited[curr_row][curr_col]==0 && issafe(curr_row, curr_col) == true){
				visited[curr_row][curr_col] = 1;
				solve(x, y, curr_cost + mat[curr_row][curr_col], count + 1);
				solve(curr_row, curr_col, curr_cost + mat[curr_row][curr_col], count + 1);
				visited[curr_row][curr_col] = 0;
			}
		}
	}
	else if(y%2==1)
	{
		int curr_row, curr_col;
		for(int i = 0; i < 6; i++)
		{
			curr_row = x + odd[i][0];
			curr_col = y + odd[i][1];


			if(visited[curr_row][curr_col] == 0 && issafe(curr_row, curr_col) == true)
			{
				visited[curr_row][curr_col] = 1;
				solve(x, y, curr_cost + mat[curr_row][curr_col], count + 1);
				solve(curr_row, curr_col, curr_cost + mat[curr_row][curr_col], count + 1);
				visited[curr_row][curr_col] = 0;
			}
		}
	}

}

int main(){
	int t;
	cin >> t;
	int f = t;
	while(t--) {
		cin >> n >> m;
		finalans = -1;

		

		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				cin >> mat[i][j];
			}
		}

		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				init();
				visited[i][j] = 1;
				solve(i,j,mat[i][j],1);
				//cout << finalans << " " << i << " " << j << endl;

			}
		}
		
		cout << "#" << f - t << " " << finalans << endl;


	}
}




//-----------------------------



#include<iostream>
using namespace std;

struct node
{
	int timeSec;
	int energy;
}paceinfo[8];

int h, d;
int finalans;
void solve(int curr_time, int rem_energy, int rem_dist, int index){
	if(curr_time > finalans){
		return;
	}
	if(rem_energy < 0){
		return;
	}
	if(rem_dist <= 0){
		if(curr_time < finalans){
			finalans = curr_time;
		}
		return;
	}

	if(rem_dist*paceinfo[5].energy > rem_energy){
		return;
	}

	if(index == 1){
		solve(curr_time + paceinfo[1].timeSec, rem_energy - paceinfo[1].energy, rem_dist - 1, 1);
	}
	if(index == 1 || index==2)
	{
		solve(curr_time + paceinfo[2].timeSec, rem_energy - paceinfo[2].energy, rem_dist - 1, 2);
	}
	if(index == 1 || index == 2 || index == 3)
	{
		solve(curr_time + paceinfo[3].timeSec, rem_energy - paceinfo[3].energy, rem_dist - 1, 3);
	}
	if(index == 1 || index == 2 || index == 3 || index == 4)
	{
		solve(curr_time + paceinfo[4].timeSec, rem_energy - paceinfo[4].energy, rem_dist - 1, 4);
	}
	if(index == 1 || index == 2 || index == 3 || index == 4 || index == 5)
	{
		solve(curr_time + paceinfo[5].timeSec, rem_energy - paceinfo[5].energy, rem_dist - 1, 5);
	}

}

int main(){
	int t;
	cin >> t;

	while(t--){
		cin >> h >> d;
		finalans = 1000000;
		int tempmin, tempsec;
		for(int i = 1; i <= 5; i++)
		{
			cin >> tempmin >> tempsec;
			paceinfo[i].timeSec = (tempmin * 60) + tempsec;
			cin >> paceinfo[i].energy;
		}

		solve(0, h, d, 1);

		cout << finalans << endl;

	}
}


//----
#include<iostream>
using namespace std;

int mat[22][22];
int visited[22][22];
int location[5][2];
int finalans = 99999;
int n, c;

int rear;
int front;
struct queue
{
	int row;
	int col;
}q[10000];

void init()
{
	rear = -1;
	front = -1;
	for(int i = 0; i < 22; i++)
	{
		for(int j = 0; j < 22; j++)
		{
			visited[i][j] = 0;
		}
	}

	for(int i = 0; i < 10000; i++)
	{
		q[i].row = 0;
		q[i].col = 0;
	}
}

void solve(int row, int col, int val)
{

	int cnt = 0;
	for(int i = 0; i < c; i++)
	{
		if(visited[location[i][0]][location[i][1]]>0)
		{
			cnt++;
		}
	}
	if(cnt >= c)
	{
		return;
	}

	if((row - 1) >= 1 && visited[row - 1][col] == 0 && (mat[row - 1][col] == 1 || mat[row - 1][col] == 3))
	{
		visited[row - 1][col] = val + 1;
		rear++;
		q[rear].row = row - 1;
		q[rear].col = col;
	}
	if((row + 1) <= n && visited[row + 1][col] == 0 && (mat[row + 1][col] == 1 || mat[row + 1][col] == 3))
	{
		visited[row + 1][col] = val + 1;
		rear++;
		q[rear].row = row + 1;
		q[rear].col = col;
	}
	if((col - 1) >= 1 && visited[row][col - 1] == 0 && (mat[row][col - 1] == 1 || mat[row][col - 1] == 3))
	{
		visited[row][col - 1] = val + 1;
		rear++;
		q[rear].row = row;
		q[rear].col = col - 1;
	}
	if((col + 1) <= n && visited[row][col + 1] == 0 && (mat[row][col + 1] == 1 || mat[row][col + 1] == 3))
	{
		visited[row][col + 1] = val + 1;
		rear++;
		q[rear].row = row;
		q[rear].col = col + 1;
	}

	while(front < rear)
	{
		front += 1;
		solve(q[front].row, q[front].col, visited[q[front].row][q[front].col]);
	}
}

int main()
{
	int t;
	cin >> t;

	while(t--)
	{

		cin >> n >> c;
		int x, y;
		for(int i = 0; i < c; i++)
		{
			cin >> x >> y;
			location[i][0] = x;
			location[i][1] = y;
		}
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				cin >> mat[i][j];
			}
		}
		for(int i = 0; i < c; i++)
		{
			mat[location[i][0]][location[i][1]] = 3;
		}

		init();

		finalans = 999999;
		int temp;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				init();
				temp = 0;
				if(mat[i][j] == 1)
				{
					visited[i][j] = 1;
					solve(i, j, 1);

					for(int k = 0; k < c; k++)
					{
						if(visited[location[k][0]][location[k][1]] > temp)
						{
							temp = visited[location[k][0]][location[k][1]];
						}
					}
					if(temp < finalans)
					{
						finalans = temp;
					}
				}


			}
		}

		cout << finalans -1<< endl;
	}
}

/*



5
5 2
4 3
3 4
1 1 0 0 0
1 1 0 0 0
1 1 1 1 1
1 1 1 0 1
1 1 1 1 1
8 2
5 6
6 4
1 1 1 1 1 1 0 0
1 1 1 1 1 1 1 0
1 1 0 1 0 1 1 0
1 1 1 1 0 1 1 0
1 1 1 1 1 1 1 0
1 1 1 1 1 1 1 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
10 3
8 2
5 3
7 1
0 0 0 1 1 1 1 1 1 0
1 1 1 1 1 1 1 1 1 0
1 0 0 1 0 0 0 0 1 0
1 1 1 1 1 1 1 1 1 1
1 1 1 1 0 1 0 0 1 1
1 1 1 1 0 1 0 0 1 1
1 1 1 1 0 1 0 0 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 0 0 1 0 0 1 1
1 1 1 1 1 1 1 1 1 1
15 4
11 15
15 9
1 2
14 3
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1 1 1 1 1 1 0 1
1 0 1 0 0 0 1 0 0 0 0 1 1 0 1
1 0 1 0 0 0 1 0 0 0 0 1 1 0 1
1 0 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 0 0 1 0 0 0 0 1 1 0 1
1 0 1 0 0 0 1 1 1 1 1 1 1 1 1
1 0 1 0 0 0 1 0 0 0 0 1 1 0 1
1 0 1 0 0 0 1 0 0 0 0 1 1 0 1
1 0 1 0 0 0 1 0 0 0 0 1 1 0 1
1 0 1 0 0 0 1 0 0 0 0 1 1 0 1
1 0 1 0 0 0 1 0 0 0 0 1 1 0 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
0 0 1 0 0 0 1 1 1 1 1 1 1 0 1
0 0 1 1 1 1 1 1 1 1 1 1 1 1 1
20 4
13 6
20 4
1 2
17 16
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0
1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0
1 0 1 0 0 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0
1 0 1 0 0 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0
1 0 1 0 0 0 0 0 0 0 1 0 0 1 1 1 0 0 0 0
1 0 1 0 0 0 0 0 0 0 1 0 0 1 1 1 0 0 0 0
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 0 0 0 0 0 0 1 0 0 1 1 1 0 0 1 1
1 0 1 0 0 0 0 0 0 0 1 0 0 1 1 1 0 0 1 1
1 0 1 0 0 0 0 0 0 0 1 0 0 1 1 1 0 0 1 1
1 0 1 0 0 0 0 0 0 0 1 0 0 1 1 1 0 0 1 1
1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 1 1
1 0 1 0 0 0 0 0 0 0 1 0 0 0 1 1 0 0 1 1
1 0 1 0 0 0 0 0 0 0 1 0 0 0 1 1 0 0 1 1
1 0 1 0 0 0 0 0 0 0 1 0 0 0 1 1 0 0 1 1
1 0 1 0 0 0 0 0 0 0 1 0 0 0 1 1 0 0 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0

Output
#1 1
#2 2
#3 2
#4 12
#5 15
*/

//------------
#include<iostream>
using namespace std;

int n;
int arr[12];
int finalans;
int visited[12];

void solve(int curr_dist, int rem_fuel, int index, int count, int ins, int g_or_d){
	
	if(curr_dist > finalans) {
		return;
	}

	if(count == n) {
		if(curr_dist < finalans) {
			finalans = curr_dist;
			cout << finalans << endl;
		}
		return;
	}

	if(rem_fuel <= 0) {
		return;
	}

	if(ins == 0 && g_or_d == 0) {
		for(int k = 1; k <= n; k++) {
			if(visited[k] == 0 && arr[k]==1){
				visited[k] = 1;
				
				int temp;
				if(k > index) {
					temp = (k - index);
				}
				else {
					temp = (index - k);
				}
				solve(curr_dist + temp, rem_fuel - 1, k, count + 1, 0, 0);

				solve(curr_dist + temp, 2, k, count + 1, 1, 0);
				solve(curr_dist + temp, 2, k, count + 1, 2, 0);

				visited[k] = 0;
			}
		}
	}
	if(ins == 0 && g_or_d == 1) {
		for(int k = 1; k <= n; k++) {
			if(visited[k] == 0 && arr[k]==2) {
				visited[k] = 1;

				int temp;
				if(k > index) {
					temp = k - index;
				}
				else {
					temp = index - k;
				}

				solve(curr_dist + temp, rem_fuel - 1, k, count + 1, 0, 1);
				solve(curr_dist + temp, 2, k, count + 1, 1, 1);
				solve(curr_dist + temp, 2, k, count + 1, 2, 1);

				visited[k] = 0;
			}
		}
	}
	if(ins == 1) {
		solve(curr_dist + (index - 0) , 2, 0, count , 0, 0);
	}
	if(ins == 2) {
		solve(curr_dist + (n + 1) - index , 2, n + 1, count , 0, 1);
	}
}

int main(){
	int t;
	cin >> t;

	while(t--){
		cin >> n;
		finalans = 1000000;
		for(int i = 0; i < 12; i++){
			arr[i] = 0;
			visited[i] = 0;
		}

		for(int i = 1; i <= n; i++) {
			cin >> arr[i];
		}

		solve(0,2,0,0,0,0);
		if(finalans == 1000000) {
			solve(n + 1, 2, n + 1, 0, 0, 1);
		}

		cout << "#" << t << " " << finalans << endl;
	}

	system("pause");
}

//----

#include<iostream>
using namespace std;

int mat[50][50];
int visited[50][50];

int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, -1}};
int m, n;
int start_x,start_y;


void init(){
	for(int i = 0; i < 50; i++){
		for(int j = 0; j < 50; j++)
		{
			visited[i][j] = 0;
		}
	}
}

bool check_for_last_row(int x, int y, int level){
	if(x == m - 1){
		return true;
	}
	int curr_x, curr_y;
	for(int k = 0; k < 2 + 2 * level; k++){
		if(k < 4){
			curr_x = x + moves[k][0];
			curr_y = y + moves[k][1];
		}
		else{
			curr_x = x + (k / 2)*moves[k % 2][0];
			curr_y = y;
		}

		if(curr_x >= 0 && curr_x < m && curr_y >= 0 && curr_y < n)
		{
			if(mat[curr_x][curr_y] == 1 && visited[curr_x][curr_y] == 0)
			{
				visited[curr_x][curr_y] = 1;
				if(check_for_last_row(curr_x, curr_y, level) == true)
				{
					return true;
				}
			}
		}
	}
	return(false);
}

int check_for_level(int x, int y){
	int level = 1;

	while(true){
		init();
		visited[x][y] = 0;

		if(check_for_last_row(x,y,level) == true){
			return level;
		}
		level += 1;
	}
}


int main(){
	int t;
	cin >> t;
	int ans;
	while(t--){
		cin >> m >> n;
		cin >> start_x >> start_y;

		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				cin >> mat[i][j];
			}
		}

		mat[m - 1][0] = 2;
		for(int i = 1; i < n; i++){
			mat[m - 1][i] = 1;
		}

		ans = check_for_level(start_x, start_y);

		cout << ans << endl;

	}
}

/*
x:17 y:6
m:31 n:29
0 0 1 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0
0 0 1 0 0 1 0 0 0 0 0 0 0 0 1 0 0 1 1 1 0 0 0 0 0 1 0 0 1
0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1
0 0 1 0 0 0 0 0 0 0 1 0 0 0 1 1 0 1 0 0 0 0 1 0 0 0 0 0 1
0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 1 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 1 0 0 0 1 0 0
0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0
0 1 1 0 0 0 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 1 0
0 0 0 0 0 0 0 0 0 1 0 1 1 0 1 0 0 0 1 0 0 0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 1 0 0 0 1 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 0 1 0 0 0 0 0 0 0 0 1 0 1 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 1
0 0 0 0 0 1 0 0 1 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0
0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 0
0 0 0 0 0 0 3 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 1 0 0 1
0 0 1 1 0 1 0 0 0 1 1 0 0 0 0 0 1 0 1 1 0 1 0 0 1 0 0 0 1
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0
0 0 0 0 0 0 0 1 1 1 0 0 0 0 1 0 0 0 0 1 0 0 0 1 0 0 0 0 0
0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 0 0 0 0 0 0
0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 0 0 0 1 0 0 0
0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 1 0 0 1 1 0 1 0 0 1 0 0
0 0 0 1 1 0 1 0 0 0 0 0 0 0 0 1 0 1 0 1 0 0 0 0 0 0 0 0 0
1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1
0 0 0 0 0 1 1 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0 1 1 0 0 0 0 0 1 0 0 1 0 0 0 0 1 0 1 0
2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
Case#0: 9


x:5 y:16
m:49 n:32
0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0
0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
Case#1: 43
251.000000

*/
//---
#include<iostream>
using namespace std;

int t_cost[22];
int t_hire[22];
int n;
int finalans;

void dfs(int pos, int bpool3,int bpool2,int bpool1, int curr_cost){

	//cout << curr_cost << endl;

	int total_pool = bpool1 + bpool2 + bpool3;
	if(curr_cost > finalans) {
		return;
	}
	
	if(pos == n - 1) {
		if(total_pool < t_hire[pos]) {
			curr_cost += t_cost[pos];
		}

		if(curr_cost < finalans) {
			finalans = curr_cost;
		}
		return;

	}

	//1
	dfs(pos + 1, bpool3, bpool2, bpool1, curr_cost + t_cost[pos]);
	//2
	dfs(pos + 1, bpool3 + t_hire[pos], bpool2, bpool1, curr_cost + (2 * t_cost[pos]));
	//3
	if(total_pool >= t_hire[pos]) {
		if(t_hire[pos]>bpool1+bpool2) {
			bpool3 = total_pool - t_hire[pos];
			bpool2 = 0;
			bpool1 = 0;
		}
		else if(t_hire[pos] > bpool1) {
			bpool2 = (bpool1 + bpool2) - t_hire[pos];
			bpool1 = 0;
		}

		dfs(pos + 1, 0, bpool3, bpool2, curr_cost);

	}
}

int main(){

	int t;
	cin >> t;

	while(t--) {
		finalans = 1000000;
		cin >> n;

		for(int i = 0; i <= n-1; i++) {
			cin >> t_hire[i] >> t_cost[i];
		}

		dfs(0,0,0,0,0);


		cout << finalans << endl;
	}
	system("pause");
}
//------------------
#include<iostream>
using namespace std;

int CPU;
int MEM;
int BRD;
int price_cpu,price_mem;
int n;
int maxnum[12];

struct product{
	int cpu;
	int mem;
	int board;
	int price;
}p[10];

int findmax(int index){
	if( p[index].cpu * CPU + p[index].mem * MEM >=p[index].price ){
		return 0;
	}
	else{
		return(min(min(BRD/p[index].board,CPU/p[index].cpu),MEM/p[index].mem));
	}
}


bool canproceed(int remaining[]){
	if(remaining[0]<0 || remaining[1]<0 || remaining[2]<0){
		return false;
	}
	return true;
}

int decrease(int remaining[],int index,int i){
	if(i!=0){
		remaining[0] -= p[index].cpu;
		remaining[1] -= p[index].mem;
		remaining[2] -= p[index].board;
	}
	return(canproceed(remaining));
}
int increase(int remaining[],int index,int x){
	remaining[0] += (p[index].cpu)*x;
	remaining[1] += (p[index].mem)*x;
	remaining[2] += (p[index].board)*x;
}


int main(){
	int t;
	cin >> t;
	
	while(t--){
		

		cin >> CPU >> MEM >> BRD >> price_cpu >> price_mem;
		cin >> n;

		for(int i=0;i<n;i++){
			cin >> p[i].cpu >> p[i].mem >> p[i].board >> p[i].price;
		}
		for(int i=0;i<n;i++){
			maxnum[i]=findmax(i);
		}

		int max_ans=-99999;
		int remaining[3];
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				for(int k=0;k<n;k++){
					remaining[0]=CPU;
					remaining[1]=MEM;
					remaining[2]=BRD;

					for(int x=0;x<=maxnum[i];x++){
						if(decrease(remaining,i,x)==0){
							break;
						}
						int y=0;
						for(;y<=maxnum[j];y++){
							if(decrease(remaining,j,y)==0){
								y++;
								break;
							}
							int z=0;
							for(;z<=maxnum[k];z++){
								if(decrease(remaining,k,z)==0){
									z++;
									break;
								}
								int curr = x*p[i].price + y*p[j].price + z*p[k].price + remaining[0]*price_cpu + remaining[1].price_mem ;
								max_ans=max(max_ans,curr);

								if(k<2){
									z++;
									break;
								}
							}
							increase(remaining,k,z-1);
							if(j<1){
								y++;
								break;
							}
						}
						increase(remaining,j,y-1);
					}
					

				}
				if(j>=n-1){
					break;
				}
			}
			if(i>=n-2){
				break;
			}
		}


		cout << max_ans << endl;




  
	}
}

