// Problem: CF 1789 E - Serval and Music Game
// https://codeforces.com/contest/1789/problem/E

/*
 * Problem: E. Serval and Music Game
 * 
 * Purpose:
 * This code calculates the sum of x * f(x) for all x from 1 to s_n, where f(x)
 * is the number of s_i such that there exist non-negative integers p_i and q_i
 * with s_i = p_i * floor(s_n / x) + q_i * ceil(s_n / x).
 *
 * The problem involves:
 * - For each x, compute floor(s_n / x) and ceil(s_n / x)
 * - For each s_i, determine if it can be expressed as p * floor + q * ceil
 * - Count how many such s_i exist (f(x))
 * - Sum x * f(x) for all valid x values
 *
 * Algorithms:
 * - Preprocessing using prefix sums to quickly calculate ranges of valid s_i
 * - Analytic approach for computing f(x) in different cases to avoid O(n) check per x
 * 
 * Time Complexity:
 * O(s_n * log(s_n)) due to iteration over x up to s_n and operations involving
 * prefix sums and bounded inner loops.
 *
 * Space Complexity:
 * O(s_n) for prefix_count array and auxiliary data structures.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
const ll mod = 998244353;

void init() {}

void solve() {
  int n = 0;
  cin >> n;
  vi s(n);
  for (int i = 0; i != n; ++i) {
    cin >> s[i];
  }
  // prefix_count[i] counts how many s values are <= i
  vi prefix_count(s[n - 1] + 2);
  for (int i = 0; i != n; ++i) {
    prefix_count[s[i]] = 1;
  }
  // Build prefix sum
  for (int i = 1; i != prefix_count.size(); ++i) {
    prefix_count[i] += prefix_count[i - 1];
  }
  ll res = 0;
  for (int x = 1; x <= s[n - 1]; ++x) {
    int n1 = s[n - 1] / x;        // floor(s_n / x)
    int n2 = (s[n - 1] + x - 1) / x; // ceil(s_n / x)
    ll f = 0;
    int x_ub = x;
    if (n1 < n2) {
      x_ub = (s[n - 1] + n1 - 1) / n1 - 1;  // Upper bound for x values in this range
    }
    if (n1 < n2) {
      // Case when n1 < n2: iterate over valid p_i values
      for (int p = 1; p <= n1 - 1 && p * n1 - 1 <= s[n - 1]; ++p) {
        f += prefix_count[min(p * n1 + p, s[n - 1])] - prefix_count[p * n1 - 1];
      }
      if ((ll)n1 * n1 - 1 <= s[n - 1]) {
        f += prefix_count.back() - prefix_count[n1 * n1 - 1];
      }
    } else {
      if (n1 == 1) {
        f = n;  // If n1 = n2 = 1, all s_i are valid
      } else {
        // Case when n1 = n2: iterate over valid p_i values
        for (int p = 1; p * n1 <= s[n - 1]; ++p) {
          f += prefix_count[p * n1] - prefix_count[p * n1 - 1];
        }
      }
    }
    // Compute sum of x values in range [x, x_ub]
    ll sumx = (ll)(x + x_ub) * (x_ub - x + 1) / 2;
    sumx %= mod;
    x = x_ub;
    res += f * sumx;
    res %= mod;
  }
  cout << res << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init();
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/