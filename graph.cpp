#include <iostream>
#include <vector>
#include <unordered_map> 
#include <time.h>
#include <math.h>
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
        float distance(float* p1, float* p2);
        float prims();
        
};

    Graph::Graph(int n, int d) {
        (*this).v = n;
        (*this).d = d;
    }
    float Graph::rand_edge() {
        return ((float) rand() / (RAND_MAX));
    }

    float Graph::distance(float* p1, float* p2) {
        float difference = 0;
        for (int i = 0; i < d; i ++) {
            difference = difference + (p1[i] - p2[i]) * (p1[i] - p2[i]);
        }
        return sqrt(difference);
    }

    float* Graph::rand_coords() {
        float arr[d];
        for (int i = 0; i < d; i++) {
            arr[i] = (float) rand() / (RAND_MAX);
        }
        return arr;
    }

    float Graph::prims() {
        srand(time(NULL));
        int S[v];
        for (int i = 0; i < v; i ++) {
            S[i] = 0;
        }
        Heap H = *(new Heap());
        
        if (d == 0) {
            float mindist = 0;
            float dist[v];
            dist[0] = 0;
            for (int i = 0; i < v; i++) {
                dist[i] = 1.000000002;
            }
            node s = {1, 0};
            dist[0] = 0;
            H.insert(s);
            while(H.get_size()) {
                node tmp = H.delete_min();
                S[tmp.label - 1] = 1;
                for (int j = 1; j < v + 1; j++) {
                    if (S[j-1]) {
                        continue;
                    }
                    else {
                        float x = rand_edge();
                        if (x > 0.05) {
                            continue;
                        }
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
        else {
            float coords[v][d];
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < d; j++) {
                    coords[i][j] = rand_edge();
                }
            }
            float mindist = 0;
            float dist[v];
            dist[0] = 0;
            for (int i = 0; i < v; i++) {
                dist[i] = 1.000000002;
            }
            node s = {1, 0};
            dist[0] = 0;
            H.insert(s);
            while(H.get_size()) {
                node tmp = H.delete_min();
                S[tmp.label - 1] = 1;
                for (int j = 1; j < v + 1; j++) {
                    if (S[j-1]) {
                        continue;
                    }
                    else {
                        float x = distance(coords[tmp.label], coords[j]);
                        cout << x << endl;
                        dist[j-1] = min(x, dist[j-1]);
                        node t = {j, x};
                        H.insert(t);
                    }
                }
                cout << endl;
            }
            for (float weights: dist) {
                mindist += weights;
            }
            return mindist;
            

        }
    }
    // 128 points 1.13549
    // 256 points 1.30461
    // 512 points 1.21668
    // 1024 points 1.14358
    // 2048 points 1.23614
    // 4096 points 1.18798
    // 8192 points 1.1997
    // 16384 points 1.20106
    // 32768 points 1.20264
    // 65536 points 1.20089
    // 131072 points 1.2022
    // 262144 points 1.20188
    int main(int argc, char *argv[]) {
        int flag = atoi(argv[1]);
        int numpoints = atoi(argv[2]);
        int numtrials = atoi(argv[3]);
        int dimension = atoi(argv[4]);
        float sum = 0;
        
        for (int i = 0; i < 1; i++) {
            Graph* g = new Graph(numpoints, dimension);
            sum += (*g).prims();
        }

        cout << numpoints << " points " << sum / numtrials << endl;
            
        
    }
