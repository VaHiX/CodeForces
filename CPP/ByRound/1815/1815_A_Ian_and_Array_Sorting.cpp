// Problem: CF 1815 A - Ian and Array Sorting
// https://codeforces.com/contest/1815/problem/A

/*
Problem: Ian and Array Sorting

Purpose:
This code determines whether an array can be made non-decreasing by performing operations where two adjacent elements are either both increased or both decreased by 1.

Algorithms/Techniques:
- Greedy approach with difference analysis
- Key insight: we only need to check if it's possible to transform the array into a sorted one using allowed operations

Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(n) due to storing the input array.

The algorithm works by:
1. If the array length is odd, it's always possible (since we can adjust the middle element)
2. For even-length arrays, we compute the sum of differences between adjacent pairs
3. If the sum of differences is non-negative, then it's possible to make the array sorted

*/

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
    bool ans(n % 2); // If length is odd, it's always possible
    long long sumdiff(0); // Sum of differences between adjacent pairs
    for (long p = 1; !ans && p < n; p += 2) {
      sumdiff += (v[p] - v[p - 1]); // Accumulate differences
    }
    ans = ans || (sumdiff >= 0); // If sum is non-negative, it's possible
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/