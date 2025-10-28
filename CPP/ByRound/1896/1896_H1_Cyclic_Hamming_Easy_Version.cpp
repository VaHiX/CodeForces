// Problem: CF 1896 H1 - Cyclic Hamming (Easy Version)
// https://codeforces.com/contest/1896/problem/H1

/*
Algorithm: Dynamic Programming with Bitmask and FFT-like approach
Time Complexity: O(2^k * k * 2^k) ~ O(2^(2k) * k) where k <= 7
Space Complexity: O(2^k) for DP arrays

The problem involves counting valid assignments of '?' characters in two binary strings,
such that each string has exactly 2^k zeros and 2^k ones, and for all cyclic shifts of
the second string, the Hamming distance to the first string is at least 2^k.

The algorithm uses a recursive approach with bitmask DP to calculate valid configurations
for each string. Then, it combines results to count valid pairs of strings satisfying the constraints.
*/

#include <assert.h>
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define mod 998244353
vector<int> mult(vector<int> &a, vector<int> &b) {
  int n = a.size();
  int m = b.size();
  vector<int> res(n + m - 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      res[i + j] = (res[i + j] + 1LL * a[i] * b[j]) % mod;
    }
  }
  return res;
}
vector<int> mult2(vector<int> &a, vector<int> &b) {
  assert(a.size() == b.size());
  int n = a.size();
  vector<int> res(n);
  for (int i = 0; i < n; i++) {
    res[i] = (1LL * a[i] * b[i]) % mod;
  }
  return res;
}
vector<int> calc(int k, string &s) {
  int k2 = 1 << (k + 1);
  vector<int> res(k2);
  vector<vector<int>> dp(k2, vector<int>(2));
  for (int i = 0; i < k2; i++) {
    if (s[i] != '0') {
      dp[i][1] = 1;
    }
    if (s[i] != '1') {
      dp[i][0] = 1;
    }
  }
  auto dfs = [&](auto &&self, int i, vector<vector<int>> &dp, int mask) {
    if (i == k + 1) {
      if (mask != k2 - 1) {
        res[mask] = dp[0][k2 >> (__builtin_popcount(mask) + 1)];
      }
      return;
    }
    int z = dp.size() / 2;
    for (int b : {0, 1}) {
      vector<vector<int>> ndp(z);
      for (int j = 0; j < z; j++) {
        if (b == 0) {
          ndp[j] = mult(dp[j], dp[j + z]);
        } else {
          ndp[j] = mult2(dp[j], dp[j + z]);
        }
      }
      self(self, i + 1, ndp, mask | (b << (k - i)));
    }
  };
  dfs(dfs, 0, dp, 0);
  return res;
}
int main() {
  int k;
  string s, t;
  cin >> k;
  cin >> s;
  cin >> t;
  vector<int> dps = calc(k, s);
  vector<int> dpt = calc(k, t);
  int k2 = 1 << (k + 1);
  int sum = 0;
  for (int i = 0; i < k2; i++) {
    for (int j = 0; j < k2; j++) {
      if ((i | j) == k2 - 1) {
        int cnt = (1LL * dps[i] * dpt[j]) % mod;
        int cnt2 = __builtin_popcount(i & j) % 2 ? (-1) : 1;
        sum = (sum + 1LL * cnt * cnt2) % mod;
      }
    }
  }
  if (sum < 0) {
    sum = sum + mod;
  }
  cout << sum << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/