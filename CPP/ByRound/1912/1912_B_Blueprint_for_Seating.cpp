// Problem: CF 1912 B - Blueprint for Seating
// https://codeforces.com/contest/1912/problem/B

/*
 * Problem: Blueprint for Seating
 * 
 * Purpose:
 *   This code solves a problem related to minimizing the inconvenience of seating layouts
 *   in aircraft rows with k aisles. The inconvenience is defined as the sum of distances
 *   from each seat to the nearest aisle. The goal is to compute both the minimum possible
 *   inconvenience and the number of layouts that achieve this minimum.
 *
 * Algorithm:
 *   - Precompute factorials and inverse factorials for combinatorics.
 *   - For given n seats and k aisles:
 *     - Compute optimal layout distribution of seats.
 *     - Calculate minimum inconvenience based on distribution.
 *     - Count number of layouts that achieve this inconvenience using combinatorics.
 *
 * Time Complexity:
 *   O(N) preprocessing for factorials and inverse factorials, where N = 1e5.
 *   Each test case is processed in O(k) time due to loop over cnt values.
 *   Total time complexity for all test cases is O(N + sum_k) where sum_k is the sum of k over all test cases.
 *
 * Space Complexity:
 *   O(N) for storing factorials and inverse factorials.
 *   O(1) additional space for other variables.
 */

#include <stdio.h>
#include <iostream>

#define mod 998244353
#define N 100000
using namespace std;
int inv[N + 5], fact[N + 5], ifact[N + 5];
inline int qmod(int x) { return x + (x >> 31 & mod); }
inline void add(int &x, int y) { x = qmod(x + y - mod); }
void init() {
  inv[1] = 1;
  for (int i = 2; i <= N; i++)
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
  fact[0] = ifact[0] = 1;
  for (int i = 1; i <= N; i++) {
    fact[i] = 1ll * i * fact[i - 1] % mod;
    ifact[i] = 1ll * inv[i] * ifact[i - 1] % mod;
  }
}
inline int C(int a, int b) {
  if (a < b || b < 0)
    return 0;
  return 1ll * fact[a] * ifact[b] % mod * ifact[a - b] % mod;
}
inline long long f(int x) {
  if (x & 1) {
    x >>= 1;
    return 1ll * x * x;
  }
  x >>= 1;
  return 1ll * x * (x - 1);
}
int k, n;
void solve() {
  cin >> n >> k;
  int res = 0, cnt[3] = {0};
  if (n / k == 1)
    res = C(k - 1, n % k - 1);
  else {
    if (n / k & 1) {
      cnt[1] = k - n % k;
      cnt[2] = n % k;
    } else {
      cnt[1] = n % k;
      cnt[2] = k - n % k;
    }
    while (cnt[1] >= 0) {
      if (cnt[0])
        add(res, 1ll * C(k - 1, cnt[1]) * C(k - 1 - cnt[1], cnt[2]) % mod);
      if (cnt[1])
        add(res, 2ll * C(k - 1, cnt[0]) * C(k - 1 - cnt[0], cnt[2]) % mod);
      if (cnt[2])
        add(res, 1ll * C(k - 1, cnt[1]) * C(k - 1 - cnt[1], cnt[0]) % mod);
      cnt[1] -= 2;
      cnt[0]++;
      cnt[2]++;
    }
  }
  long long sum = f(n / k + 1) * (n % k) + f(n / k) * (k - n % k);
  printf("%lld %d\n", sum, res);
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  init();
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/