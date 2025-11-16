// Problem: CF 856 A - Set Theory
// https://codeforces.com/contest/856/problem/A

/*
 * Problem: Set Theory
 * 
 * Approach:
 * - For each test case, we need to construct a set B such that all sums a[i] + b[j] are unique.
 * - We use a greedy algorithm:
 *   1. Iterate through potential values for b[j] starting from 1.
 *   2. For each candidate value p, check if adding it to all elements of A results in new sums.
 *   3. If yes, include p in B and mark those sums as used (to avoid future conflicts).
 *   4. Continue until we've selected n values for B.
 * 
 * Time Complexity: O(N * n) where N is the maximum possible sum (2*10^6), and n is the size of A.
 * Space Complexity: O(N) for the boolean array to track available sums.
 */

#include <cstdio>
#include <vector>
int main() {
  int t;
  scanf("%d", &t);
  const long N = 2000000;  // Upper bound for sum values
  while (t--) {
    puts("YES");
    std::vector<bool> available(N, true);  // Tracks which sums are available
    int n;
    scanf("%d", &n);
    std::vector<long> a(n);
    for (int p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    int count(0);
    for (long p = 1; p < N && count < n; p++) {
      bool possible(true);
      for (long q = 0; q < n; q++) {
        if (!available[a[q] + p]) {  // If this sum is already taken, skip
          possible = false;
          break;
        }
      }
      if (possible) {
        printf("%ld ", p);
        ++count;
        for (long q = 0; q < n; q++) {
          available[a[q] + p] = false;  // Mark this sum as used
        }
      }
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/