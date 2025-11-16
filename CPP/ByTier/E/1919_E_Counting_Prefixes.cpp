// Problem: CF 1919 E - Counting Prefixes
// https://codeforces.com/contest/1919/problem/E

/*
 * Problem: E. Counting Prefixes
 *
 * Algorithm: Dynamic Programming with Memoization and Combinatorics
 * 
 * Time Complexity: O(n^3), where n is the size of the array. The nested loops
 *                  and combinatorial calculations within contribute to this complexity.
 * Space Complexity: O(n^2), due to storage of DP states, maps, and factorial arrays.
 *
 * Description:
 * This code counts the number of valid arrays `a` of size `n` consisting of only 1 and -1,
 * such that when the prefix sum array `p` is computed and sorted in non-decreasing order,
 * it matches the given sorted prefix sum array.
 *
 * The approach uses dynamic programming to keep track of valid arrangements,
 * with combinatorics (factorials and inverse factorials) for calculating binomial coefficients.
 */

#include <stdio.h>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <utility>

using namespace std;
int main() {
  static const long long mod = 998244353;
  static const int maxn = 200010;
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    map<int, int> mp;
    int Mi = 0, Mx = 0;
    mp[0]++;
    for (int i = 1, p; i <= n; i++)
      scanf("%d", &p), Mi = min(Mi, p), Mx = max(Mx, p), mp[p]++;
    static long long fac[2][maxn];
    fac[0][0] = fac[0][1] = fac[1][0] = fac[1][1] = 1;
    for (int i = 2; i <= n + 1; i++)
      fac[1][i] = -mod / i * fac[1][mod % i] % mod;
    for (int i = 2; i <= n + 1; i++)
      fac[0][i] = fac[0][i - 1] * i % mod,
      fac[1][i] = fac[1][i - 1] * fac[1][i] % mod;
    auto C = [](const int n, const int k) {
      if (n < k || k < 0)
        return 0ll;
      return fac[0][n] * fac[1][k] % mod * fac[1][n - k] % mod;
    };
    int cur = 0;
    unordered_map<int, long long> f[2], gL[2], gR[2], h[2];
    f[cur][mp[Mi] + 1] = Mi != 0, gL[cur][mp[Mi]] = 1,
                    gR[cur][mp[Mi]] = Mi != 0, h[cur][mp[Mi] - 1] = 1;
    for (int i = Mi + 1; i <= Mx; i++) {
      cur ^= 1, f[cur].clear(), gL[cur].clear(), gR[cur].clear(),
          h[cur].clear();
      if (i == 0) {
        for (auto p : f[cur ^ 1])
          if (p.first <= mp[i]) {
            p.second %= mod;
            long long c = C(mp[i] - 1, p.first - 1);
            gL[cur][mp[i] - p.first + 1] += p.second * c % mod;
            h[cur][mp[i] - p.first] += p.second * c % mod;
          }
        for (auto p : gR[cur ^ 1])
          if (p.first <= mp[i]) {
            p.second %= mod;
            long long c = C(mp[i] - 1, p.first - 1);
            h[cur][mp[i] - p.first] += p.second * c % mod;
          }
        continue;
      }
      for (auto p : f[cur ^ 1])
        if (p.first <= mp[i]) {
          p.second %= mod;
          long long c = C(mp[i] - 1, p.first - 1);
          f[cur][mp[i] - p.first + 2] += p.second * c % mod;
          gL[cur][mp[i] - p.first + 1] += p.second * c % mod;
          gR[cur][mp[i] - p.first + 1] += p.second * c % mod;
          h[cur][mp[i] - p.first] += p.second * c % mod;
        }
      for (auto p : gL[cur ^ 1])
        if (p.first <= mp[i]) {
          p.second %= mod;
          long long c = C(mp[i] - 1, p.first - 1);
          gL[cur][mp[i] - p.first + 1] += p.second * c % mod;
          h[cur][mp[i] - p.first] += p.second * c % mod;
        }
      for (auto p : gR[cur ^ 1])
        if (p.first <= mp[i]) {
          p.second %= mod;
          long long c = C(mp[i] - 1, p.first - 1);
          gR[cur][mp[i] - p.first + 1] += p.second * c % mod;
          h[cur][mp[i] - p.first] += p.second * c % mod;
        }
      for (auto p : h[cur ^ 1])
        if (p.first <= mp[i]) {
          p.second %= mod;
          long long c = C(mp[i] - 1, p.first - 1);
          h[cur][mp[i] - p.first] += p.second * c % mod;
        }
    }
    long long ans = f[cur][0] + gL[cur][0] + gR[cur][0] + h[cur][0];
    printf("%lld\n", (ans % mod + mod) % mod);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/