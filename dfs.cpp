#include <iostream>
#include <queue>
using namespace std;

#define Max 110

//vector < int > graph[MX];
//bool vis[MX];
//int dist[MX];


class Node
{ public:
      int data;
      Node* next;
};

/*
 * Adjacency List
 */
class AdjList
{  public:

      Node *head;
};

/*
 * Class Graph
 */
class Graph
{
    public:
        //
        bool vis[Max];
        int time, prev[Max], dist[Max],f[Max];
        int v;
        AdjList* a;
        bool directed;
//**************** Initialization*****************
        Graph(int v)
        {
         this->v = v;
         a = new AdjList [v];

         for (int i = 0; i < v; ++i){
             a[i].head = NULL;
           }
        }
// add edge
        void addEdge(int src, int dest)
        {
            Node * n = new Node;
            n->data = dest;
            n->next = NULL;

         if (a[src].head == NULL)
            { a[src].head = n;
            }

        	else {
            Node* tmp = a[src].head; // code logic not working because of insert at last in the linked list
            while(tmp->next != NULL){
                tmp=tmp->next;
            }
            tmp->next=n;
            }

        }
//DFS implementation

      void dfs(int source){
        for(int i=0;i< v; ++i){
           vis[i]= 0;
           prev[i]= NULL;
           dist[i]= Max;   //distance infinity
           f[i]=Max;
        }
            time = 0;

          dfs_visit(source,vis);

   // For unvisited vertices which are not adjacent of any visited nodes

      for(int i=0;i< v; ++i)
        { if(vis[i]==0){

         dfs_visit(i,vis);
        }
   }

}

    void dfs_visit(int source, bool vis[]){

        vis[source]= 1; // grey
        cout<<source<<" ";
        time=time+1;
        dist[source] = time;

        Node * tmp = a[source].head;
        while(tmp != NULL){
         int next = tmp->data;
          if (vis[next] == 0){
           prev[next]= source;
           dfs_visit(next,vis);
         } tmp= tmp->next;
 }

    //vis[next] = 1; // visit
        time=time+ 1;
        f[source]=time;
}

   void printGraph()
   {
    int i;
    for (i = 0; i < v; ++i)
    {
        Node* tmp = a[i].head;
        cout<<"\n Adjacency list of vertex "<<i<<"\n head ";
        while (tmp)
         {
            cout<<"-> "<<tmp->data;
            tmp = tmp->next;
         }
            cout<<endl;
            }
 }
};


int main()
{
     int s,v;

    Graph g(v=8);

    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
    g.addEdge(3, 2);
    g.addEdge(2, 0);
    g.addEdge(4, 3);
    g.addEdge(6, 4);
    g.addEdge(6, 5);
    g.addEdge(6, 7);
    g.addEdge(7, 3);

    g.printGraph();

    cout<<"\nEnter source: ";
    cin >> s;
    cout << "\nDepth First Traversal :\n"<<endl;
    g.dfs(s);

    cout << "\nFrom node " << s << "\n" << endl;
    for (int i = 0; i < v; i++){
        cout << "Distance of " << i << " is : " << g.dist[i] << " , "<<"Finish time : "<< g.f[i] << endl;
    }

    return 0;
}
