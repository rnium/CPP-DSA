// #include <bits/stdc++.h>
#include <iostream>
using namespace std;

int leftIdx(int i) {
    return 2*i;
}

int rightIdx(int i) {
    return 2*i + 1;
}
// MaxHeap
void maxHeapify(int heap[], int heapsize, int i) {
    int l, r;
    int largest = i; // assumption
    l = leftIdx(i);
    r = rightIdx(i);

    if (l <= heapsize && heap[l] > heap[i]) {
        largest = l;
    }
    if (r <= heapsize && heap[r] > heap[largest]) {
        largest = r;
    }

    if (i != largest) {
        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        maxHeapify(heap, heapsize, largest);
    }
}

void buildMaxHeap(int arr[], int heapsize) {
    for (int i = heapsize/2; i >= 1; --i) {
        maxHeapify(arr, heapsize, i);
    }
}

// Minheap
void minHeapify(int heap[], int heapsize, int i) {
    int l, r;
    l = leftIdx(i);
    r = rightIdx(i);
    int lowest = i;
    if (l <= heapsize && heap[l] < heap[lowest]) {
        lowest = l;
    }
    if (r <= heapsize && heap[r] < heap[lowest]) {
        lowest = r;
    }
    if (i != lowest) {
        int temp = heap[i];
        heap[i] = heap[lowest];
        heap[lowest] = temp;
        minHeapify(heap, heapsize, lowest);
    }
}

void buildMinHeap(int heap[], int heapsize) {
    for (int i = heapsize/2; i >= 1; --i) {
        minHeapify(heap, heapsize, i);
    }
}

void heapSort(int heap[], int heapsize) {
    for (int i = heapsize; i > 1; --i) {
        int t = heap[1];
        heap[1] = heap[heapsize];
        heap[heapsize] = t;
        heapsize--;
        maxHeapify(heap, heapsize, 1);
    }
}

int main() {
    const int heapsize = 5;
    int heap[] = {0, 7, 1, 2,3,5,11,21,4,6}; // zero index should be null
    buildMaxHeap(heap, heapsize);
    // minHeapify(heap, 5, 2);
    heapSort(heap, heapsize);
    for (int i = 0; i <= heapsize; i++) {
        cout << heap[i] << " ";
    }
}