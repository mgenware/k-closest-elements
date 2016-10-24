Given an array of `n` elements, find `k` closest elements to a `target` value.

There are various ways to solve this problem:
| Ordering | Algorithm               | Time Complexity |
|----------|-------------------------|-----------------|
| Sorted   | Binary Search           | O(k + log n)    |
| Unsorted | Max-Heap                | O(n log k)      |
| Unsorted | Quickselect + Quicksort | O(n + k log k)  |

Full source code could be downloaded [here](https://github.com/mgenware/k-closest-elements/blob/master/main.cpp).

## The Given Array is Sorted
### Binary Search: O(log n)
Apply a binary search to find the closest insert position of given target value, then we could find k closest elements starting from the insert position.
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

## The Given Array is Unsorted
### Max-Heap: O(n log k)
Maintain a max-heap of size `k`, insert all elements with their absolute distances into the heap, when heap size exceeds `k`, run `ExtractMax` which takes `O(1)` time, resulting in `O(n log k)` time overall.

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


### Quickselect + Quicksort: O(n + k log k)
Use a combination of quicksort and quickselect algorithm. Initially, a pivot would be chosen randomly from `0` to `n - 1`, then each time a pivot is chosen, determine if the pivot index falls within the range of `0` to `k - 1`, if so, apply quicksort respectively on 2 subarrays divided by the pivot. Otherwise, apply quickselect within `0` to `pivotIndex - 1`.

The practical runtime of the algorithm is largely dependent on the pivot selection(the `partition` function).

```cpp
// partition function used by quickselect
int quickselectPartition(vector<pair<int, int>>& nums, int start, int end) {
    int pivot = nums[end].first;
    int i = start, j = start;
    for (; j < end; j++) {
        if (nums[j].first <= pivot) {
            swap(nums[i], nums[j]);
            i++;
        }
    }
    swap(nums[end], nums[i]);
    return i;
}

// a combination of quickselect and quicksort
void quickselect(vector<pair<int, int>>& nums, int start, int end, int k) {
    if (start >= end) {
        return;
    }
    int pivotIndex = quickselectPartition(nums, start, end);
    if (pivotIndex < k - 1) {
        quickselect(nums, start, pivotIndex - 1, k);
        quickselect(nums, pivotIndex + 1, end, k);
    } else {
        quickselect(nums, start, pivotIndex - 1, k);
    }
}

// uses a combination of quickselect and quicksort to find k closest elements in O(n + k log k).
multiset<int> kClosestQuickselect(vector<int> nums, int target, int k) {
    vector<pair<int, int>> distances(nums.size());
    for (int i = 0; i < nums.size(); i++) {
        distances[i] = make_pair(abs(nums[i] - target), nums[i]);
    }

    quickselect(distances, 0, distances.size() - 1, k);
    multiset<int> result;
    for (int i = 0; i < k; i++) {
        result.insert(distances[i].second);
    }
    return result;
}
```
