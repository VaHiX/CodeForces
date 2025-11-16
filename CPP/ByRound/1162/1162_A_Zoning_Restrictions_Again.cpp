// Problem: CF 1162 A - Zoning Restrictions Again
// https://codeforces.com/contest/1162/problem/A

/*
 * Problem: A. Zoning Restrictions Again
 * Purpose: Maximize profit from building houses on a street under zoning restrictions.
 * Algorithm: Brute force simulation with updates to minimum heights in ranges.
 * Time Complexity: O(m * n), where m is number of restrictions and n is number of spots.
 * Space Complexity: O(n), for storing the heights of houses.
 */
#include <cstdio>
#include <vector>
int main() {
  long n, h, m;
  scanf("%ld %ld %ld", &n, &h, &m);
  std::vector<long> a(n, h); // Initialize all houses to maximum height h
  while (m--) { // Process each restriction
    long l, r, x;
    scanf("%ld %ld %ld", &l, &r, &x);
    for (long p = l - 1; p < r; p++) { // Adjust range to 0-based indexing
      a[p] = (a[p] < x) ? a[p] : x; // Update height to minimum of current and restriction
    }
  }
  long long total(0);
  for (long p = 0; p < n; p++) {
    total += a[p] * a[p]; // Sum up square of heights for profit
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/