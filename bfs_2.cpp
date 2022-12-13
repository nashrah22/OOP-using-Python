#include <iostream>
#include <queue>
using namespace std;

#define MX 110


class Node
{public:
    int data;
     Node* next;
};

/*
 * Adjacency List
 */
class AdjList
{ public:

 Node *head;
};

/*
 * Class Graph
 */
class Graph
{
    public:
        //
        bool vis[MX];
        int dist[MX];
        int colour[MX];

        //
        int v;
        AdjList* a;
        bool directed;
     //Initialization
        Graph(int v)
        {
        this->v = v;
        a = new AdjList [v];

        for (int i = 0; i < v; ++i){

        a[i].head = NULL;
                }
        }


        void addEdge(int src, int dest)
        {
            Node * n1 = new Node;
            Node * n2 = new Node;
            n1->data = dest;
            n2->data = src;

            //n->data = src;
            n1->next = NULL;
            n2->next = NULL;

            if (a[src].head == NULL && a[dest].head == NULL)
            { a[src].head = n1;
              a[dest].head= n2;
            }

            else if( a[src].head != NULL && a[dest].head == NULL ){

            n1->next= a[src].head;
            a[src].head= n1;
           // As a[dest].head is NULL
            a[dest].head = n2;

            }		// 0--->NULL

            else if(a[src].head == NULL && a[dest].head != NULL){

             a[src].head = n1;
             n2->next= a[dest].head;
             a[dest].head= n2;
           // As a[dest].head is NULL

            }


            else {
             n1->next= a[src].head;
             a[src].head= n1;

             n2->next= a[dest].head;
             a[dest].head= n2;


        	}

        }



    bool bfs(int source){
    queue < int > Q;
//Initialization
    for(int i=0;i< v; ++i){
        vis[i]= 0;
        dist[i]= MX;
        colour[i] = 0;
        //distance infinity
    }

    colour[source]=1;
    vis[source]= 1; // gray
    dist[source] =0;
    Q.push(source);

    while(!Q.empty()){
        int node = Q.front();
        cout << node << " ";
        Q.pop();

        // have to traverse the adjacency list of node
        Node * tmp= a[node].head;

        while(tmp != NULL){
              int next = tmp->data;
              if (vis[next] == 0){
                vis[next] = 1; // visit
                if(colour[node]==1){
                    colour[next]=0;
                }
                else{
                    colour[next]= 1;
                }
                dist[next] = dist[node] + 1; // update
                Q.push(next); // push to queue

            }
            else{
                if(colour[next]== colour[node])
                    return false;

            }
            tmp= tmp->next;
        }
         //
    }
    return true;
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
     bool n;

   // bool dir;
   //cout<<"enter no of vetices: "<<endl;
   //cin>>v;
    Graph g(v=8);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(3, 5);

    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(4, 7);
    g.addEdge(6, 7);
    //g.addEdge(5, 6);
    //g.addEdge(6, 7);
    //g.addEdge(8, 9);

    g.printGraph();

    cout<<"\nEnter source: ";
    cin >> s;
    cout << "\nBreadth First Traversal :\n"<<endl;
   n= g.bfs(s);

    cout << "\nFrom node " << s << "\n" << endl;
    for (int i = 0; i < v; i++){
        cout << "Distance of " << i << " is : " << g.dist[i]<<" "<< "colour is "<< g.colour[i] << endl;
    }
if(n){
    cout<<"Bipertite"<<endl;
}
else {

    cout<<"Not bipertite"<<endl;
}

    return 0;
}
