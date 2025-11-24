// Problem: CF 1445 A - Array Rearrangment
// https://codeforces.com/contest/1445/problem/A

/*
 * Problem: Array Rearrangement
 * Algorithm: Greedy approach with sorting
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the arrays
 *
 * Given two arrays a and b, determine if we can rearrange elements of b such that
 * a[i] + b[i] <= x for all i.
 * Strategy:
 *   - Sort array a in ascending order
 *   - Sort array b in descending order
 *   - For each i, check if a[i] + b[i] <= x
 *   - If all pairs satisfy the condition, return "Yes", otherwise "No"
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    sort(a.begin(), a.end());                    // Sort array a in ascending order
    sort(b.rbegin(), b.rend());                  // Sort array b in descending order
    bool res(true);
    for (long p = 0; p < n; p++) {
      if (a[p] + b[p] > x) {                     // Check if current pair violates constraint
        res = false;
        break;
      }
    }
    puts(res ? "Yes" : "No");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/