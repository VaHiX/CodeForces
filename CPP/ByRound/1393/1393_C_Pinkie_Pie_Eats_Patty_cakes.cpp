// Problem: CF 1393 C - Pinkie Pie Eats Patty-cakes
// https://codeforces.com/contest/1393/problem/C

/*
C. Pinkie Pie Eats Patty-cakes
Purpose: Given a list of patty-cakes with fillings, find the maximum possible minimum distance between two patty-cakes with the same filling when eaten in an optimal order.

Algorithm:
- For each test case:
  - Count frequency of each filling type.
  - Identify the maximum frequency (mx) and how many fillings have this frequency (rep).
  - Use formula: ans = (n - rep) / (mx - 1) - 1 to compute the result.

Time Complexity: O(n log n) per test case due to map operations.
Space Complexity: O(n) for storing counts in the map.

Note: This problem is about optimally arranging items to maximize minimum spacing between same elements.
*/

#include <cstdio>
#include <map>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> cnt; // Map to store frequency of each filling
    long mx(0), rep(0);       // mx: max frequency, rep: number of fillings with max frequency
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++cnt[x];                  // Increment count of filling x
      if (cnt[x] > mx) {         // If new maximum frequency found
        mx = cnt[x];
        rep = 1;                 // Reset counter for this frequency
      } else if (cnt[x] == mx) {
        ++rep;                   // Increment counter if same as current max
      }
    }
    long ans = (n - rep) / (mx - 1) - 1; // Compute result using derived formula
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/