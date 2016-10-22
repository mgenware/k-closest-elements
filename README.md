# k-closest-elements
Multiple algorithm implmentations for K-Closest Elements

## Given Array is Sorted
`O(log n) + O(k)`: use binary search to find the closest insert position, then find k closest elements from insert position.
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

// runs a binary search in O(log n) and finds k closest elements in O(k).
multiset<int> binarySearch(vector<int> nums, int target, int k) {
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
