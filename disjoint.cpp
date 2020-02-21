#include <iostream>
#include <vector>
using namespace std

class Disjoint {
private:
    vector<int> parent,
    vector<int> rank;
    int n;

public:
    DisjointSet(int n);
    int Find(int n);
    void Union(int m, int n);
    int Link(int m, int n);

};

Disjoint::DisjointSet(int n){
    (*this).n = n;
    parent.resize(n+1);
    rank.resize(n+1);

    for(int i=0;i<n+1;i++){
        parent.insert(i, i);
        rank.insert(0, i);
    }
}

Disjoint::int Find(int x){
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

Disjoint::int Link(int x, int y){
    if(rank[x] > rank[y]){
        rank[x] += rank[y];
        parent[y] = x;
    }
    else if(rank[y] > rank[x]){
        rank[y] += rank[x];
        parent[x] = y;
    }
    else if (rank[x] = rank[y]){
        rank[y] = rank[y] + 1;
        parent[x] = y;
    }
    return y;

}

Disjoint::void Union(int x,int y){
    Link(Find(x), Find(y));
}
