// Problem: CF 1784 F - Minimums or Medians
// https://codeforces.com/contest/1784/problem/F

/*
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves determining the number of distinct sets Vika can obtain after k operations, 
where each operation removes either two smallest or two median elements from a set of integers.

The approach uses dynamic programming where we track how many ways we can reach a certain state 
by choosing which operations to perform. It calculates the number of valid sequences of operations 
that result in different final sets.

The key idea is to compute the combinations of choosing which operations (remove min or remove median) 
to perform at each step, and combine this with combinatorics.

The use of precomputed factorials and inverse factorials allows for fast computation of binomial coefficients.
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
using ull = unsigned long long;
constexpr int N = 2e6 + 5;
constexpr int mod = 998244353;
void add(int &x, int y) { x += y, x >= mod && (x -= mod); }
int ksm(int a, int b) {
  int s = 1;
  while (b) {
    if (b & 1)
      s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}
int n, k, ans, fc[N], ifc[N];
int bin(int n, int m) {
  if (n < m || n < 0)
    return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  // Precompute factorials and inverse factorials
  for (int i = fc[0] = 1; i < N; i++)
    fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[N - 1] = ksm(fc[N - 1], mod - 2);
  for (int i = N - 2; ~i; i--)
    ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
  cin >> n >> k;
  if (n == k)
    puts("1"), exit(0);
  int l = 0, r = 0, sum = ans = 1;
  for (int p = 1; p <= k; p++) {
    int lim = min(k - p, n - p - p - 1);
    int nl = max(0, k - p - lim), nr = min(p, k - p);
    if (nl > nr)
      break;
    add(sum, sum);
    add(sum, mod - bin(p - 1, r));
    add(sum, bin(p - 1, l - 1));
    while (l > nl)
      add(sum, bin(p, --l));
    while (r < nr)
      add(sum, bin(p, ++r));
    while (l < nl)
      add(sum, mod - bin(p, l++));
    while (r > nr)
      add(sum, mod - bin(p, r--));
    add(ans, sum);
  }
  for (int p = n + 1 >> 1; p <= k; p++)
    add(ans, bin(n - p - 1, k - p));
  cout << ans << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/