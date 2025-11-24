// Problem: CF 809 A - Do you want a date?
// https://codeforces.com/contest/809/problem/A

/*
 * Problem: Calculate the sum of maximum distances between all pairs of computers
 * in all non-empty subsets of hacked computers.
 * 
 * Algorithm:
 * - Sort the computers by their coordinates.
 * - For each computer at position `i`, calculate how many times its contribution
 *   to the maximum distance is counted across all subsets.
 * - Use inclusion-exclusion principle: for a sorted array, the contribution of
 *   element at index `i` is (2^i - 2^(n-1-i)) * a[i].
 * 
 * Time Complexity: O(n log n) due to sorting; the rest is O(n)
 * Space Complexity: O(n) for storing the array and powers of 2
 */

#include <stdint.h>
#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  const int64_t MOD = 1000000007;
  int64_t n;
  scanf("%lld", &n);
  std::vector<int64_t> a(n);
  for (int64_t p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  sort(a.begin(), a.end());
  std::vector<int64_t> pow(n);
  int64_t u(1);
  for (int64_t p = 0; p < n; p++) {
    pow[p] = u % MOD;
    u *= 2;
    u %= MOD;
  }
  u = 1;
  for (int64_t p = n - 1; p >= 0; p--) {
    pow[p] -= u % MOD;
    u *= 2;
    u %= MOD;
  }
  int64_t total(0);
  for (long p = 0; p < n; p++) {
    total += (pow[p] * a[p]) % MOD;
    total %= MOD;
  }
  printf("%lld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/