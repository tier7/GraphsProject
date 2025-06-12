//
// Created by wiktor on 06.06.2025.
//

#ifndef HEAP_H
#define HEAP_H
#include <climits>
#include <utility>

struct HeapNode {
    int key;
    int vertex;
};
// kopiec minimalny
struct MinHeap {
    HeapNode* data;
    int size;
    int capacity;

    MinHeap(int cap) {
        capacity = cap;
        data = new HeapNode[capacity];
        size = 0;
    }
    ~MinHeap() {
        delete[] data;
    }

    bool empty() const {
        return size == 0;
    }

    void swapNodes(int a, int b) {
        std::swap(data[a], data[b]);
    }

    // przywracanie wlasnosci kopca
    void heapify(int i) {
        int left  = i * 2 + 1;
        int right = i * 2 + 2;
        int smallest = i;

        if (left < size && data[left].key < data[smallest].key) {
            smallest = left;
        }
        if (right < size && data[right].key < data[smallest].key) {
            smallest = right;
        }
        if (smallest != i) {
            swapNodes(i, smallest);
            heapify(smallest);
        }
    }

    //zwiekszanie jak brakuje miejsca
    void grow() {
        int newCap = capacity * 2;
        HeapNode* newData = new HeapNode[newCap];
        int idx;
        for (idx = 0; idx < size; idx++) {
            newData[idx] = data[idx];
        }
        delete[] data;
        data = newData;
        capacity = newCap;
    }
    // dodawanie elementu do kopca
    void push(int key, int vertex) {
        if (size == capacity) {
            grow();
        }
        // wstawianie na koniec
        data[size].key = key;
        data[size].vertex = vertex;
        int idx = size;
        size = size + 1;

        // przesiewanie w gore
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (data[parent].key <= data[idx].key) {
                break;
            }
            swapNodes(parent, idx);
            idx = parent;
        }
    }

    HeapNode popMin() {
        HeapNode root = data[0];
        size = size - 1;
        data[0] = data[size];
        heapify(0);
        return root;
    }
};



#endif //HEAP_H
