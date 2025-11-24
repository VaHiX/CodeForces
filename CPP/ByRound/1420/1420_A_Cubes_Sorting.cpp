// Problem: CF 1420 A - Cubes Sorting
// https://codeforces.com/contest/1420/problem/A

/*
 * Problem: A. Cubes Sorting
 * Purpose: Determine if an array of cube volumes can be sorted using at most (n*(n-1)/2 - 1) adjacent swaps.
 * Algorithm: 
 *   - For each test case, we simulate checking if the array is already sorted.
 *   - If not, we check whether there exists any decreasing pair in the array (which would require swaps).
 *   - If such a pair is found and swaps count remains under limit, it's possible to sort.
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long last(-1);
    bool ans(false);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (p && (x >= last)) {  // If current element is greater than or equal to previous, a swap may be needed
        ans = true;
      }
      last = x;  // Update last seen value
    }
    puts(ans ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/