#include<iostream>
#include<list>
using namespace std;

class Graph{
    int v;
    list <int> *adj; //pointer to an array containing adj lists

    public:
        Graph(int v){
            this->v=v;
            adj = new list<int>[v];
        }
        void addEdge(int src,int dest){
            adj[src].push_back(dest);
        }

        void BFS(int s){
            bool *visited=new bool[v];
            for(int i=0;i<v;i++){
                visited[i]=false;
            }
            list<int> queue_q;
            visited[s]=true;
            queue_q.push_back(s);

            list<int> ::iterator i;

            while(!queue_q.empty()){
                s=queue_q.front();
                cout << s << " ";
                queue_q.pop_front();


                for(i=adj[s].begin();i!=adj[s].end();i++){
                    if(!visited[*i]){
                        visited[*i]=true;
                        queue_q.push_back(*i);
                    }
                }
            }

        }
        void DFSutil(int v,bool visited[]){
            visited[v]=true;
            cout << v << " ";

            list<int> :: iterator i;
            for(i=adj[v].begin();i!=adj[v].end();i++){
                if(!visited[*i]){
                    DFSutil(*i,visited);
                }
            }

        }

        void DFS(int s){
            bool *visited=new bool[v];
            for(int i=0;i<v;i++){
                visited[i]=false;
            }
            DFSutil(s,visited);

        }


};

int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 2);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.BFS(2);
    cout<<endl;
    g.DFS(2);

    return 0;
}
