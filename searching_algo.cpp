#include <iostream>
#include <vector>

using namespace std;


int binarySearch(const vector<int>& nums, int n) {
    int l, r, mid;
    l = 0;
    r = nums.size()-1;
    while (l <= r) {
        mid = l + (r-l)/2;
        if (nums[mid] == n) {
            return mid;
        }
        else if (nums[mid] > n) {
            r = mid-1;
        }
        else {
            l = mid + 1;
        }
    }
    return -1;
}

int main() {
    vector<int> vec{10,15,20};
    cout << binarySearch(vec, 2) << endl;
}