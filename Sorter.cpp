//
// Created by wiktor on 21.04.2025.
//

#include "Sorter.h"
#include <iostream>

void quickSort(Edge* tab, int left, int right) {
    if (left >= right) return;

    int i = left - 1;
    int j = right + 1;
    Edge pivot = tab[(left + right) / 2];

    while (true) {
        do { i++; } while (tab[i].weight < pivot.weight);
        do { j--; } while (tab[j].weight > pivot.weight);
        if (i <= j) {
            std::swap(tab[i], tab[j]);
        } else {
            break;
        }
    }
    quickSort(tab, left, j);
    quickSort(tab, i, right);
}

void sort(Edge* tab, int n) {
    quickSort(tab, 0, n - 1);
}
