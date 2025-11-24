// Problem: CF 1975 C - Chamo and Mocha's Array
// https://codeforces.com/contest/1975/problem/C

/*
C. Chamo and Mocha's Array
Algorithm: Sliding window with multiset to efficiently find median of subarrays.
Time Complexity: O(n log n) per test case due to multiset operations.
Space Complexity: O(n) for storing the array and the multiset.

The problem asks to find the maximum possible value that can be obtained after performing
operations on an array where we replace a subarray with its median. 
We use a sliding window approach over all possible subarrays of size 3, maintaining a multiset
to efficiently compute the median. For each step, we remove the leftmost element and add the
new rightmost element, then find the median (middle element in sorted order).
The maximum among these medians across all valid windows is our answer.
*/

#include <algorithm>
#include <cstdio>
#include <iterator>
#include <set>
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
    if (n == 2) {
      // For two elements, the minimum is always the final value
      printf("%ld\n", v[0] < v[1] ? v[0] : v[1]);
      continue;
    }
    std::multiset<long> s;
    s.insert(v[0]);
    s.insert(v[1]);
    s.insert(v[2]);
    // Initialize result with the median of first 3 elements
    long res(*std::next(s.begin(), 1));
    for (long p = 3; p < n; p++) {
      // Remove the oldest element from window
      s.erase(s.find(v[p - 3]));
      // Add new element to window
      s.insert(v[p]);
      // Get median of current 3-element window
      long cand = *(std::next(s.begin(), 1));
      // Keep track of maximum median seen so far
      res = (res > cand ? res : cand);
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/