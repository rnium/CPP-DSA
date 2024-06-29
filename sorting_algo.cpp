#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

template <typename T>
void printVec(vector<T>& vec) {
    cout << "[";
    for (T i: vec) {
        cout << i << ",";
    }
    cout << "]" << endl;
}


typedef vector<vector<int>> adjacencyList;
typedef vector<vector<int>> matrix;


// Selection Sort
void selectionSort(vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n-1; ++i) {
        int j = i;
        for (int k = i+1; k < n; ++k) {
            if (vec[k] < vec[j]) {
                j = k;
            }
        }
        if (j != i) {
            int temp = vec[j];
            vec[j] = vec[i];
            vec[i] = temp;
        }
    }
}


//  Bubble Sort
void bubleSort(vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n; ++i) {
        bool switched = false;
        for (int j = 1; j < n-i; ++j) {
            if (vec[j-1] > vec[j]) {
                if (!switched) {
                    switched = true;
                }
                cout << vec[j-1] << " " << vec[j] << endl;
                int temp = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = temp;
            }
        }
        if (!switched) {
            break;
        }
    }
}


// Insertion Sort
void insertionSort(vector<int>& vec) {
    int n = vec.size();
    for (int i = 1; i < n; ++i) {
        int item = vec[i];
        int j = i-1;
        while (j >= 0 && vec[j] > item) {
            vec[j+1] = vec[j];
            j -= 1;
        }
        vec[j+1] = item;
    }
}

// Merge Sort
vector<int> mergeList(vector<int>& arr1, vector<int>& arr2) {
    vector<int> mergedList;
    int len_arr1 = arr1.size();
    int len_arr2 = arr2.size();
    mergedList.reserve(len_arr1+len_arr2);
    int idx_a1 = 0;
    int idx_a2 = 0;
    while (idx_a1 < len_arr1 && idx_a2 < len_arr2) {
        if (arr1[idx_a1] < arr2[idx_a2]) {
            mergedList.push_back(arr1[idx_a1++]);
        }
        else {
            mergedList.push_back(arr2[idx_a2++]);
        }
    }
    if (idx_a1 < len_arr1) {
        mergedList.insert(mergedList.end(), arr1.begin()+idx_a1, arr1.end());
    }
    else {
        mergedList.insert(mergedList.end(), arr2.begin()+idx_a2, arr2.end());
    }
    return mergedList;
}

vector<int> mergeSort(vector<int> vec) {
    if (vec.size() == 1) {
        return vec;
    }
    int mid = vec.size() / 2;
    vector<int> left = mergeSort(vector<int>(vec.begin(), vec.begin()+mid));
    vector<int> right = mergeSort(vector<int>(vec.begin()+mid, vec.end()));
    auto merged = mergeList(left, right);
    return merged;
}


// Quick Sort

int partition(vector<int>& arr, int low, int high) {
    int i = low-1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < arr[high]) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    i++;
    swap(arr[i], arr[high]);
    return i;
}

void quicksort(vector<int>& arr, int low, int high) {
    if (low >= high) {
        return;
    }
    int p = partition(arr, low, high);
    quicksort(arr, low, p-1);
    quicksort(arr, p+1, high);
}

// Counting Sort
vector<int> countSort(vector<int>& vec, int max) {
    vector<int> hash(max+1);
    for (int i: vec) {
        hash[i]++;
    }
    vector<int> res;
    res.reserve(vec.size());
    for (int i = 0; i < hash.size(); ++i) {
        if (hash[i]) {
            vector<int> same_nums(hash[i], i);
            res.insert(res.end(), same_nums.begin(), same_nums.end());
        }
    }
    return res;
}


int main() {
    vector<int> vec{7,7,2,5,22,6,4,2,7};
    auto res = countSort(vec, 22);
    // partition(vec, 0, 4);
    printVec(res);
}


