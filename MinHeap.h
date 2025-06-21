#ifndef HEAP_H
#define HEAP_H

#include <utility>

struct HeapNode {
    int key;
    int vertex;
};

// kopiec minimalny
struct MinHeap {
    HeapNode* data;
    int* pos;
    int size;
    int capacity;
    int vCap;

    MinHeap(int cap, int vcap) {
        size = 0;
        capacity = cap;
        vCap = vcap;

        data = new HeapNode[capacity];
        pos = new int[vCap];
        for (int i = 0; i < vCap; ++i) {
            pos[i] = -1;
        }
    }

    ~MinHeap() {
        delete[] data;
        delete[] pos;
    }

    bool empty() const {
        return size == 0;
    }


    // przywracanie własności kopca
    void heapify(int i) {
        int left  = i * 2 + 1;
        int right = i * 2 + 2;
        int smallest = i;

        if (left  < size && data[left].key < data[smallest].key) {
            smallest = left;
        }
        if (right < size && data[right].key < data[smallest].key) {
            smallest = right;
        }

        if (smallest != i) {
            std::swap(data[i], data[smallest]);
            // aaktualizacja pozycji obydwu wierzcholkow
            pos[data[i].vertex] = i;
            pos[data[smallest].vertex] = smallest;
            heapify(smallest);
        }
    }

    // dodawanie elementu do kopca
    void push(int key, int vertex) {
        if (vertex >= vCap || size == capacity) return;

        if (pos[vertex] != -1) {
            if (key < data[pos[vertex]].key)
                decreaseKey(vertex, key);
            return;
        }

        data[size] = {key, vertex};
        pos[vertex] = size;
        int idx = size;
        size++;

        // przesiewanie w górę
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (data[parent].key <= data[idx].key) break;

            std::swap(data[parent], data[idx]);
            pos[data[parent].vertex] = parent;
            pos[data[idx].vertex] = idx;

            idx = parent;
        }
    }

    void decreaseKey(int vertex, int newKey) {
        int i = pos[vertex];
        if (i == -1 || data[i].key <= newKey) return;

        data[i].key = newKey;

        while (i > 0) {
            int parent = (i - 1) / 2;
            if (data[parent].key <= data[i].key) break;

            std::swap(data[parent], data[i]);
            pos[data[parent].vertex] = parent;
            pos[data[i].vertex]= i;

            i = parent;
        }
    }


    HeapNode popMin() {
        HeapNode root = data[0];
        pos[root.vertex] = -1;

        if (--size > 0) {
            data[0] = data[size];
            pos[data[0].vertex] = 0;
            heapify(0);
        }
        return root;
    }
};

#endif // HEAP_H
