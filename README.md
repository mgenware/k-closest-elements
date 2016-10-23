# k-closest-elements
Multiple algorithm implmentations for K-Closest Elements

# Given Array is Sorted
## Binary Search - O(log n) + O(k)
Use binary search to find the closest insert position, then find k closest elements starting from insert position.
```cpp
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

// runs a binary search in O(log n) and finds k closest elements of given target in O(k).
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
```

# Given Array is Unsorted
## Max-Heap - O(n log k)
Maintain a max-heap of size `k`, insert all elements with their absolute distances into the heap, when heap size exceeds `k`, run `ExtractMax` which is `O(1)`. Overrall time complexity is `O(n log k)`.

```cpp
// Comparer struct used by kClosestHeap, which determines equality by comparing pair<int, int>.first.
struct HeapPairComparer {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        return a.first < b.first;
    }
};

// uses a max-heap to find k closest elements of given target, O(n log k).
multiset<int> kClosestHeap(vector<int> nums, int target, int k) {
    priority_queue<int, vector<pair<int, int>>, HeapPairComparer> maxHeap;
    multiset<int> result;

    for (auto n: nums) {
        auto pair = make_pair(abs(n - target), n);
        maxHeap.push(pair);
        if (maxHeap.size() > k) {
            maxHeap.pop();
        }
    }

    while (maxHeap.size()) {
        result.insert(maxHeap.top().second);
        maxHeap.pop();
    }
    return result;
}
```
