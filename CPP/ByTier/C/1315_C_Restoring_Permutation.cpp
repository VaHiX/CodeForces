// Problem: CF 1315 C - Restoring Permutation
// https://codeforces.com/contest/1315/problem/C

/*
C. Restoring Permutation
Algorithm: Greedy
Time Complexity: O(n^2) per test case due to nested loops for finding unused elements.
Space Complexity: O(n) for vectors of size up to 2*n.

The problem asks to find a lexicographically minimal permutation of numbers from 1 to 2n such that for each i, b[i] is the minimum of pair (a[2*i-1], a[2*i]).

Approach:
1. First, place each b[i] at position 2*i-1 in result array.
2. Then for each such placed element, greedily assign the smallest unused number to position 2*i.
3. If no unused number is available during assignment, it's impossible.
4. Print the result or -1 if impossible.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(2 * n, 0);           // Result array of size 2*n
    std::vector<bool> used(2 * n + 1, 0);    // Track which numbers from 1 to 2*n are used
    bool possible(true);
    for (long p = 0; p < n; p++) {
      long b;
      scanf("%ld", &b);
      a[2 * p] = b;                         // Place b at odd index (1-based)
      if (used[b]) {                        // Check if b was already used
        possible = false;
      }
      used[b] = true;                       // Mark b as used
    }
    for (long p = 0; possible && p < n; p++) {
      long x = a[2 * p];                    // Get the element we placed at odd index
      for (long q = x + 1; q <= 2 * n; q++) { // Start from x+1 to find next smallest unused number
        if (!used[q]) {
          used[q] = true;
          a[2 * p + 1] = q;               // Assign it at even index (1-based)
          break;
        }
      }
      if (!a[2 * p + 1]) {                  // If no suitable number found
        possible = false;
      }
    }
    if (possible) {
      for (long p = 0; p < 2 * n; p++) {
        printf("%ld ", a[p]);
      }
      puts("");
    } else {
      puts("-1");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/