//
//  main.cpp
//  CPP
//
//  Created by Mgen on 8/27/16.
//  Copyright © 2016 Mgen. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// runs a binary search on a given array, returns the insert position of a given integer
int findInsertPosition(vector<int>& nums, int target) {
    int i = 0, j = nums.size() - 1;
    while (i < j) {
        int mid = i + (j - i) / 2;
        if (target <= nums[mid]) {
            j = mid;
        } else {
            i = mid + 1;
        }
    }
    return i;
}

// runs a binary search in O(log n) and finds k closest elements in O(k).
multiset<int> kClosestBinarySearch(vector<int> nums, int target, int k) {
    multiset<int> result;
    // sort the array
    sort(nums.begin(), nums.end());
    
    // assume target exists and k <= nums.size()
    int idx = findInsertPosition(nums, target);
    // insert the most closest element into the set
    result.insert(nums[idx]);
    int i = idx - 1, j = idx + 1;
    // find the other k - 1 closest elements
    while (result.size() < k) {
        if (j >= nums.size() - 1 || target - nums[i] < nums[j] - target) {
            result.insert(nums[i--]);
        } else {
            result.insert(nums[j++]);
        }
    }
    return result;
}

void printSet(multiset<int>& set) {
    for (auto n: set) {
        cout << n << " ";
    }
    cout << endl;
}

int main() {
    cout << "--- Sorted Array, Binary Search, O(log n) + O(k)" << endl;
    vector<int> sortedNums = {1, 2, 3, 4, 6, 6, 10};
    multiset<int> result;
    
    // find 4 closest element to 6
    result = kClosestBinarySearch(sortedNums, 6, 4);
    printSet(result);
    // find 5 closest element to 5
    result = kClosestBinarySearch(sortedNums, 5, 5);
    printSet(result);
    return 0;
}
