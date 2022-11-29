#include<iostream>
#include<list>
using namespace std;

class graph{
public:
    int v;
    list<int> *l;
    graph(int v){
    this->v=v;
    l = new list<int>[v];

    }
    void addedge(int x,int y){
        l[x].push_back(y);
        l[y].push_back(x);
    }

    void print(){

    }
    };

int main(){
    graph g(4);
    g.addedge(0,1);
    g.addedge(0,2);
    g.addedge(2,3);
    g.addedge(1,2);

    }
