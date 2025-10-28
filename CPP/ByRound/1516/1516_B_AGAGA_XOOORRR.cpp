// Problem: CF 1516 B - AGAGA XOOORRR
// https://codeforces.com/contest/1516/problem/B

/*
 * Problem: AGAGA XOOORRR
 * Purpose: Determine if we can reduce an array to at least 2 equal elements 
 *          by repeatedly replacing two adjacent elements with their XOR.
 * Algorithm:
 *   - Precompute prefix XORs for efficient subarray XOR queries.
 *   - Check if the total XOR of the array is 0.
 *   - If it's 0, check if there exists a split point such that both parts have equal XOR.
 * Time Complexity: O(n^2) per test case
 * Space Complexity: O(n) for prefix XOR storage
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n, 0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // Compute prefix XORs: v[p] = a[0]^a[1]^...^a[p]
      v[p] = (p ? v[p - 1] : 0) ^ x;
    }
    // If total XOR is 0, it's potentially possible to make all elements equal
    bool possible(!v.back());
    for (long p = 0; !possible && p < n; p++) {
      for (long q = p + 1; !possible && q < n; q++) {
        // Check if we can split the array into two parts with equal XOR
        // Left part: v[p] (a[0]^...^a[p])
        // Right part: v[q] ^ v[p] (a[p+1]^...^a[q])
        // Total: v.back() ^ v[q] (a[q+1]^...^a[n-1])
        possible |= (v[p] == (v[q] ^ v[p])) && (v[p] == (v.back() ^ v[q]));
      }
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/