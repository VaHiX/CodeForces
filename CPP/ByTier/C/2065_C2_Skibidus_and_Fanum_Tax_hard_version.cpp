// Problem: CF 2065 C2 - Skibidus and Fanum Tax (hard version)
// https://codeforces.com/contest/2065/problem/C2

/*
C2. Skibidus and Fanum Tax (hard version)
Algorithm: Greedy with binary search
Time Complexity: O((n + m) * log(m)) per test case
Space Complexity: O(n + m)

This problem involves checking whether we can sort an array 'a' in non-decreasing order
by optionally performing one operation on each element. The operation allows us to 
replace a[i] with b[j] - a[i] for some j. After applying operations, the resulting array
must be sorted.

Approach:
1. Sort the array 'b' to enable binary search.
2. Process elements of 'a' from left to right:
   - For each element, determine how much it can be reduced (if at all) to maintain
     non-decreasing order with previous elements.
   - Use binary search on sorted 'b' to find the smallest valid value that can be used
     for transformation such that the resulting sequence remains non-decreasing.
3. If we ever face an impossible condition (i.e., an element is too large to satisfy order),
   return "NO".

The solution uses greedy strategy where at each step, we try to make the smallest possible
adjustment to maintain sorting property, and uses binary search for efficiency.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> a(n);
    for (size_t p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(m);
    for (size_t p = 0; p < m; p++) {
      scanf("%ld", &b[p]);
    }
    sort(b.begin(), b.end());
    bool res(true);
    a[0] = std::min(a[0], b[0] - a[0]); // First element can be optimized with smallest value in b
    for (size_t p = 1; res && p < n; p++) {
      // Find the first element in b that satisfies: a[p-1] + a[p] <= b[j]
      std::vector<long>::iterator fb =
          std::lower_bound(b.begin(), b.end(), a[p - 1] + a[p]);
      if (fb == b.end()) {
        // No such element exists => we must ensure current a[p] doesn't violate order
        if (a[p - 1] > a[p]) {
          res = false;
          break;
        }
        continue;
      }
      // Try to assign the minimal possible value to a[p] to maintain non-decreasing order
      if (a[p - 1] <= a[p] && a[p - 1] <= *fb - a[p]) {
        a[p] = std::min(a[p], *fb - a[p]);
      } else if (a[p - 1] <= a[p]) {
        // Do nothing since order is already maintained
      } else if (a[p - 1] <= *fb - a[p]) {
        a[p] = *fb - a[p];
      } else {
        res = false; // Impossible to maintain non-decreasing order
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/