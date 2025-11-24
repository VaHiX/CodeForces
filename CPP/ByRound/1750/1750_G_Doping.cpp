// Problem: CF 1750 G - Doping
// https://codeforces.com/contest/1750/problem/G

/*
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n^3)
Space Complexity: O(n^2)

This solution computes the number of k-special permutations for each k from 1 to n.
A k-special permutation is a permutation that is lexicographically smaller than the given permutation p,
and requires exactly k subarrays to be partitioned such that each subarray is "fancy" (i.e., consecutive integers).

The approach uses:
1. Precomputation of combinations C[n][k] modulo m
2. Dynamic programming table f[i][j] representing the number of ways to form j partitions from first i elements
3. Iterating through each position in the permutation and calculating how many valid permutations exist with specific partition counts
4. Using inclusion-exclusion principle and combinatorics to count valid configurations

The key insight is that for each position i in the permutation p, we analyze how elements before position i affect
the number of ways to partition the remaining elements into fancy subarrays.
*/
#include <cstdio>
#include <iosfwd>

using namespace std;
const int o = 2010;
int n, m, p[o], f[o][o], C[o][o], ans[o];
bool S[o];
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &p[i]);
  // Precompute combinations C[i][j] = C(i,j) mod m
  for (int i = C[0][0] = 1; i <= n; ++i)
    for (int j = C[i][0] = 1; j <= i; ++j)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % m;
  // Precompute f[i][j] = number of ways to partition first i elements into j subarrays
  for (int i = f[0][0] = 1, j; i <= n; ++i)
    for (f[i][0] = f[i - 1][0] * 1ll * i % m, j = 1; j <= i; ++j)
      f[i][j] = (f[i][j - 1] + m - f[i - 1][j - 1]) % m;
  // Main algorithm: iterate through permutation positions
  for (int i = 1, t = n, c, c1, c2; i <= n;
       t -= (i > 1 && p[i - 1] + 1 == p[i]), c = c1 = c2 = 0, ++i) {
    // Mark which elements are present from position i onwards
    for (int j = 1; j <= n; ++j)
      S[j] = 0;
    for (int j = i; j <= n; ++j)
      S[p[j]] = 1;
    // Count consecutive pairs in the suffix
    for (int j = 1; j < n; ++j)
      c += (S[j] && S[j + 1]);
    // Count valid positions where we can place a number smaller than p[i]
    for (int j = 1; j < p[i]; ++j)
      if (S[j] && (i == 1 || p[i - 1] + 1 - j)) {
        if (S[j - 1])
          ++c1;
        else
          ++c2;
      }
    // Update answer for cases where we extend existing partitions
    for (int j = 0; j < c; ++j)
      ans[t - j] =
          (ans[t - j] + C[c - 1][j] * 1ll * f[n - i - j][c - 1 - j] % m * c1) %
          m;
    // Update answer for cases where we start a new partition
    for (int j = 0; j <= c; ++j)
      ans[t - j] =
          (ans[t - j] + C[c][j] * 1ll * f[n - i - j][c - j] % m * c2) % m;
    // Special case: when we add a number such that the new element is one more than previous
    if (i > 1 && S[p[i - 1] + 1] && p[i - 1] + 1 < p[i])
      for (int j = 0; j <= c; ++j)
        ans[t - j - 1] =
            (ans[t - j - 1] + C[c][j] * 1ll * f[n - i - j][c - j]) % m;
  }
  for (int i = 1; i <= n; ++i)
    printf("%d ", ans[i]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/