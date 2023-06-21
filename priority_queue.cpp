#include <iostream>
#include <vector>
using namespace std;


void printHeap(vector<int>& heap) {
    for (int i: heap) {
        cout << i << " ";
    }
    cout << "\n";
}

int leftIdx(int i) {
    return 2*i;
}

int rightIdx(int i) {
    return 2*i + 1;
}

int parentIdx(int i) {
    return i/2;
}

void maxHeapify(vector<int>& heap, int heapsize, int i) {
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


int extractMax(vector<int>& heap) {
    int heapsize = heap.size()-1;
    if (heapsize < 1) return -1;
    int maxItem = heap[1];
    heap[1] = heap[heapsize];
    heap.erase(heap.end()-1);
    maxHeapify(heap, heapsize-1, 1);
    return maxItem;
}

void insertNode(vector<int>& heap, int data) {
    heap.push_back(data);
    int i = heap.size()-1, parent = parentIdx(i), temp;
    while (i > 1 && heap[i] > heap[parent]) {
        temp = heap[parent];
        heap[parent] = data;
        heap[i] = temp;
        i = parent;
        parent = parentIdx(i);
    }
}

int main() {
    vector<int> heap = {0, 7, 5, 2, 3, 1};
    // cout << extractMax(heap) << endl;
    // cout << extractMax(heap) << endl;
    // extractMax(heap);
    insertNode(heap, 20);
    insertNode(heap, 3);
    insertNode(heap, 11);
    printHeap(heap);
}