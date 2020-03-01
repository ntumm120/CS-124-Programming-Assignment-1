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
    public:
        Graph(int n, int d);
        float rand_edge();
        float distance(float* p1, float* p2);
        float prims();
        
};

    Graph::Graph(int n, int d) {
        srand(time(NULL));
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

    float Graph::prims() {
        
        int S[v];
        for (int i = 0; i < v; i ++) {
            S[i] = 0;
        }
        Heap H = *(new Heap());
        
        if (d == 0 || d == 1) {
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
                        dist[j-1] = min(x, dist[j-1]);
                        node t = {j, x};
                        H.insert(t);
                    }
                }
            }
            for (int i = 0; i < v; i++) {
                mindist += dist[i];
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
                dist[i] = 2;
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
                        dist[j-1] = min(x, dist[j-1]);
                        node t = {j, x};
                        H.insert(t);
                    }
                }
            }
            for (int i = 0; i < v; i++) {
                mindist += dist[i];
            }
            return mindist;
            

        }
    }

    int main(int argc, char *argv[]) {
        int flag = atoi(argv[1]);
        int numpoints = atoi(argv[2]);
        int numtrials = atoi(argv[3]);
        int dimension = atoi(argv[4]);
        float sum = 0;
        
        for (int i = 0; i < numtrials; i++) {
            Graph* g = new Graph(numpoints, dimension);
            sum += (*g).prims();
        }

        cout << numpoints << " points " << dimension << " dimensions "<< numtrials << " trial average " << sum / numtrials << endl;
            
        
    }
