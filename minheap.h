#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

struct node {
    int label;
    float dist;
};

class Heap {
    private:
        
        int parent(int i);
        int right(int i);
        int left(int i);
        void swap(int a, int b);
        void min_heapify(int i);

    public:
        unordered_map<int, int> location;
        vector<node> H;
        Heap();
        void insert(node i);
        node delete_min();
        int get_size() {
            return H.size();
        }
};

Heap::Heap() {
}


int Heap::parent(int i) {
    return (i - 1)/2;
}


int Heap::right(int i) {
    return 2*i + 2;
}


int Heap::left(int i) {
    return 2*i + 1;

}

void Heap::swap(int i, int j) {
    cout << "Fuck" << endl;
    node tmp = H[i];
    H[i] = H[j];
    H[j] = tmp;
}

void Heap::min_heapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < H.size() && H[l].dist < H[i].dist)
        smallest = l;
    if (r < H.size() && H[r].dist < H[smallest].dist)
        smallest = r;
    if (smallest != i) {
        swap(i, smallest);
        location[H[smallest].label] = smallest;
        location[H[i].label] = i;
        min_heapify(smallest);
    }
    
}

void Heap::insert(node i) {
    
    cout << endl;
    if (location[i.label] && H[location[i.label]].dist > i.dist) {
        cout << "Fuck" << endl;
        H[location[i.label]] = H[get_size()-1];
        location[H[location[i.label]].label] = location[i.label];
        location.erase(H[location[i.label]].label);
        H.pop_back();
        min_heapify(location[i.label]);
    }
    else if (location[i.label]) {
        return;
    }
    H.push_back(i);
    int n = H.size() - 1;
    while (n > 0 && (H[parent(n)].dist > H[n].dist)) {
        swap(parent(n), n);
        location[H[parent(n)].label] = parent(n);
        location[H[n].label] = n;
        n = parent(n);
    }
    location[H[n].label] = n;
    if (get_size() >= 1){
        cout << H[0].label << endl;
    }
    if (get_size() >= 2){
        cout << H[1].label << endl;
    }
    if (get_size() >= 3){
        cout << H[2].label << endl;
        
    }

}

node Heap::delete_min() {
    node min = H[0];
    H[0] = H[get_size()-1];
    location[H[0].label] = 0;
    location.erase(H[get_size()-1].label);
    H.pop_back();
    min_heapify(0);
    return min;
}
