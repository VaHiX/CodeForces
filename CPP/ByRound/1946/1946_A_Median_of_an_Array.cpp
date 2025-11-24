// Problem: CF 1946 A - Median of an Array
// https://codeforces.com/contest/1946/problem/A

/*
Problem: Find minimum operations to increase the median of an array.
Algorithm: Sorting + Greedy
Time Complexity: O(n log n) per test case due to sorting, where n is the size of array.
Space Complexity: O(n) for storing the vector.

Approach:
- Sort the array.
- The median index is (n - 1) / 2.
- Count how many elements are equal to the median element starting from that index.
- The number of operations needed equals the count of these median elements that are less than or equal to the desired new median value, which is determined by the elements at the median position after sorting.

This approach works because:
1. We sort the array to easily determine the current median.
2. To increase the median, we must ensure that the element at index (n-1)/2 increases to a higher value.
3. All elements in the sorted array that are equal to the current median and lie before or at the median position can be increased to match the next larger value in order.
4. The minimum number of operations is simply counting how many elements are equal to the existing median element from the middle onward.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    sort(v.begin(), v.end()); // Sort the array to easily find median
    long idx = (n - 1) / 2;   // Index of the median element in sorted array
    long cnt(0);
    for (long p = idx; p < n && v[p] == v[idx]; p++, cnt++) // Count same elements from median onwards
      ;
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/