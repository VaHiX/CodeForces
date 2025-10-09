// Problem: CF 2031 B - Penchick and Satay Sticks
// https://codeforces.com/contest/2031/problem/B

/*
B. Penchick and Satay Sticks
time limit per test1.5 seconds
memory limit per test256 megabytes

Algorithm:
This problem involves determining whether a given permutation can be sorted using only swaps of adjacent elements whose values differ by exactly 1.

Key Insight:
We can perform swaps between adjacent elements if their difference is exactly 1. This means we are essentially performing bubble-sort-like operations, but restricted to certain pairs.

Approach:
- Iterate through the array from left to right.
- For each element at index i, check:
    - If v[i] == i: it's already in correct place.
    - Else if v[i] == i+1 and v[i+1] == i: we can swap these two elements (they are adjacent and differ by 1).
    - Otherwise: impossible to arrange them correctly via allowed moves.
- If any invalid condition occurs during iteration, return "NO".

Time Complexity: O(n) per test case due to single pass over the array per element.
Space Complexity: O(n) for storing the vector.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n + 1); // Use 1-based indexing
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &v[p]);
    }
    bool ans(true);
    for (long p = 1; p <= n && ans; p++) {
      if (v[p] == p) {
        continue; // Already in correct position
      } else if (v[p] == p + 1 && p < n && v[p + 1] == p) {
        // Swap adjacent elements differing by exactly 1
        long tmp = v[p];
        v[p] = v[p + 1];
        v[p + 1] = tmp;
      } else {
        ans = false; // Cannot proceed further with valid operations
      }
    }
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/