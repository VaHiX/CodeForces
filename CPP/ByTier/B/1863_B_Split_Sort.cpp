// Problem: CF 1863 B - Split Sort
// https://codeforces.com/contest/1863/problem/B

/*
B. Split Sort

Algorithm:
The problem involves transforming a permutation into the identity permutation [1, 2, ..., n] using "split" operations.
Each operation chooses a value x and splits the array into two parts: elements less than x, followed by elements >= x.
We simulate the process by sorting the elements with their original indices and counting how many times an element's index decreases after sorting, which indicates a necessary split operation.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the vector of pairs

Techniques:
- Sorting with index tracking
- Counting inversions in a specific sense
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<long, long>> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].first);   // Read the value
      v[p].second = p;             // Store original index
    }
    sort(v.begin(), v.end());      // Sort by value, maintaining original indices
    long cnt(0);
    for (long p = 1; p < n; p++) {
      cnt += (v[p].second < v[p - 1].second);   // If current index is less than previous, it means we need a split operation
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/