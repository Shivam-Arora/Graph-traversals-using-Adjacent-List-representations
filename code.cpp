#include<bits/stdc++.h>
using namespace std;


int fruits[100];
int parent[100];
vector<int> H[100];
int dp[100][20];

void fill(vector<int> tree[],int s,int par,int ht){
    parent[s]=par;
    H[ht].push_back(s);
    
    for(int i=0;i<tree[s].size();i++){
        int v=tree[s][i];
        
        if(v!=par){
            fill(tree,v,s,ht+1);
        }
        
    }
    
}

int dfs(vector<int> tree[],int k,int s,int par,int ht){
    if(dp[s][k]!=-1){
        return(dp[s][k]);
    }
    
    int ans=0;
    
    //case1
    if(k>0){
        for(int i=0;i<H[ht].size();i++){
            int v=H[ht][i];
            if(v!=s){
                ans=max(ans,dfs(tree,k-1,v,s,ht));
            }
        }    
    }
    
    
    //case2
    for(int i=0;i<tree[s].size();i++){
        int v=tree[s][i];
        if(v!=par){
            ans=max(ans,dfs(tree,k,v,s,ht+1));
        }
    }    
    
    if(fruits[s]==1){   
        ans+=1;
    }
    dp[s][k]=ans;
    
    return(ans);
    
}
int solve(vector<int> tree[],int n,int m,int k,int f[]){
    
    for(int i=0;i<100;i++){
        for(int j=0;j<20;j++){
            dp[i][j]=-1;
        }
        fruits[i]=0;
    }
    
    for(int i=0;i<m;i++){
        int val=f[i];
        //cout << val << endl;
        fruits[val]=1;
    }
    
    fill(tree,1,-1,0);
    
    int ans= dfs(tree,k,1,-1,0);
    
    return(ans);
    
}

#Driver code
int main()
{
    int t;
    cin>>t;
    
    while(t--)
    {
        int n,k,e,m;
        cin >> n >> e >> k >> m;
        
        vector<int> tree[100];
        
        int a,b;
        for(int i=0;i<e;i++){
            cin >> a >> b;
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
        
        int f[m];
        for(int i=0;i<m;i++){
            cin >> f[i];
        }
        
        
        int ans=solve(tree,n,m,k,f);
        cout << ans << endl;
        
        
    }
	
	return 0;
}

/*
1
12 11 2 8
1 2
1 3
2 4
2 5
5 9
9 10
9 11
11 12
3 7
7 6
7 8
2 4 5 7 8 9 11 12


*/
