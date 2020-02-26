#include <iostream>
#include <vector>
#include <unordered_map> 
#include <time.h>
#include "minheap.h"

using namespace std;

class Graph{
    private:
        int v;
        int d;
        unordered_map<int, float*> coords;
    public:
        Graph(int n, int d);
        float rand_edge();
        float* rand_coords();
        float prims();
        
};

    Graph::Graph(int n, int d) {
        (*this).v = n;
        (*this).d = d;
    }
    float Graph::rand_edge() {
        return ((float) rand() / (RAND_MAX));
    }

    float* Graph::rand_coords() {
        float arr[d];
        for (int i = 0; i < d; i++) {
            arr[i] = rand() / RAND_MAX;
        }
        return arr;
    }

    float Graph::prims() {
        srand(time(NULL));
        vector<int> S;
        Heap H = *(new Heap());
        
        if (d == 0) {
            float mindist = 0;
            float dist[v];
            dist[0] = 0;
            for (int i = 0; i < v; i++) {
                dist[i] = 1.000000001;
            }
            node s = {1, 0};
            dist[0] = 0;
            H.insert(s);
            while(H.get_size()) {
                node tmp = H.delete_min();
                S.push_back(tmp.label);
                for (int j = 1; j < v + 1; j++) {
                    if (std::count(S.begin(), S.end(), j)) {
                        continue;
                    }
                    else {
                        float x = rand_edge();
                        dist[j-1] = min(x, dist[j-1]);
                        node t = {j, x};
                        H.insert(t);
                    }
                }
            }
            for (float weights: dist) {
                mindist += weights;
            }
            return mindist;
        }
    }
    int main() {
        Graph* g = new Graph(4, 0);
        cout << (*g).prims() << endl;
    }
