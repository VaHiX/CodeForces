// Problem: CF 2150 G - Counting Is Fun: The Finale
// https://codeforces.com/contest/2150/problem/G

/*
G. Counting Is Fun: The Finale
Problem Description:
Given x 0's, y 1's, and a binary string a of length x+y, count the number of binary strings b such that:
1. b has exactly x 0's and y 1's.
2. There exists an index i where min(f(b[1..i]), f(b[i+1..n])) >= k, where f(s) is the length of longest non-decreasing subsequence.
3. b is lexicographically larger than a.

Algorithms/Techniques:
- Preprocessing with modular arithmetic and combinatorics (factorials, inverse factorials, binomial coefficients).
- Dynamic programming with prefix sums for efficient range queries.
- Prefix sum optimizations to handle constraints efficiently in O(1) time per query.
- Binary search principles and sliding window techniques for identifying valid intervals.

Time Complexity: O(max(x,y)^2 + t*max(x,y)) where t is number of test cases. Preprocessing step dominates the cost.
Space Complexity: O(max(x,y)^2) for precomputed binomial coefficients and prefix sums.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 10005, mod = 998244353;
char s[N];
int fac[N], inv[N], sum[N], c0[N], c1[N];
int wow[N][N]; // Precomputed prefix sums of binomial coefficients

// Fast exponentiation with modulo
int qpow(int x, int y) {
  int ans = 1;
  while (y) {
    if (y & 1)
      ans = (ll)ans * x % mod;
    x = (ll)x * x % mod;
    y >>= 1;
  }
  return ans;
}

// Preprocessing function to initialize factorials, inverse factorials, and binomial coefficient prefix sums
void prep(int n) {
  int i, j;
  fac[0] = 1;
  for (i = 1; i <= n; i++)
    fac[i] = (ll)fac[i - 1] * i % mod;
  inv[n] = qpow(fac[n], mod - 2);
  for (i = n; i >= 1; i--)
    inv[i - 1] = (ll)inv[i] * i % mod;
  // Pascal's triangle generation with prefix sums
  for (i = 0; i <= n; i++) {
    wow[i][0] = 1;
    for (j = 1; j <= i; j++)
      wow[i][j] = (wow[i - 1][j] + wow[i - 1][j - 1]) % mod;
  }
  // Prefix sum over rows
  for (i = 0; i <= n; i++)
    for (j = 1; j <= i; j++)
      wow[i][j] = (wow[i][j] + wow[i][j - 1]) % mod;
}

// Compute binomial coefficient C(x,y) 
int C(int x, int y) {
  return (x < y || y < 0) ? 0 : ((ll)fac[x] * inv[y] % mod * inv[x - y] % mod);
}

// Compute range sum in wow table using prefix sums
int csum(int x, int l, int r) {
  l = max(l, 0);
  r = min(r, x);
  if (l > r)
    return 0;
  return (wow[x][r] + mod - wow[x][l - 1]) % mod;
}

int main() {
  prep(10000); // Initialize precomputation tables
  int t, x, y, k, i, j, ans, p, m, u, v, w, L, R, l, r, tmp;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d", &x, &y, &k);
    scanf("%s", s + 1); // Read input binary string
    ans = 0;
    
    // compute prefix sums of difference array and counts of 0's and 1's 
    for (i = 1; i <= x + y; i++) {
      sum[i] = sum[i - 1] + (s[i] == '0') - (s[i] == '1');
      c0[i] = c0[i - 1] + (s[i] == '0');
      c1[i] = c1[i - 1] + (s[i] == '1');
    }
    
    m = p = 0;
    // Determine a threshold index such that cumulative sum from start <= k 
    while (p <= x + y && (m = max(m, sum[p])) + c1[p] < k)
      p++;
    m = 0;
    // Iterate through valid points to compute contribution of 0's in final answer
    for (i = p + 1; i <= x + y; m = max(m, sum[i++] - sum[p]))
      if (s[i] == '0') {
        u = x - c0[p]; // Remaining 0's after prefix p
        v = y - c1[p]; // Remaining 1's after prefix p
        if (m + v >= k || u >= k)
          ans = (ans + C(u + v - i + p, u - c0[i - 1] + c0[p])) % mod;
        else
          ans = (ans + C(u + v - i + p, k - c0[i - 1] + c0[p])) % mod;
      }
    m = 0;
    // Handle all possible prefixes and calculate their contribution using combinatorics
    for (i = 1; i <= min(p, x + y); m = max(m, sum[i++]))
      if (s[i] == '0')
        for (j = i; j <= x + y; j++) {
          w = (C(x + y - j, k) + mod - 2 * C(x + y - j - 1, k) % mod) % mod;
          L = max(x - k, 0);
          R = min(k - y + j, j);
          l = max(m + j - k + 1, L);
          r = min(k - 1, R);
          tmp = csum(j - i, L - c0[i - 1], R - c0[i - 1]);
          tmp = (tmp + mod - csum(j - i, l - c0[i - 1], r - c0[i - 1])) % mod;
          tmp = (tmp + (ll)max(r - l + 1, 0) * C(j - i, k - c0[i - 1])) % mod;
          ans = (ans + (ll)tmp * w) % mod;
        }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/