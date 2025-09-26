/*
 * Problem URL : https://codeforces.com/problemset/problem/2068/D
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int n, f[207];
int dp[207][207][207];
int v[207];
int leaf[207];
int p[207];
std::vector<std::string> dep[407];
std::string ans[407];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    double d;
    std::cin >> d;
    f[i] = v[i] = std::round(d * 10000);
    p[i] = i;
  }
  std::sort(v + 1, v + n + 1);
  std::sort(p + 1, p + n + 1, [](int lhs, int rhs) { return f[lhs] > f[rhs]; });
  for (int i = 1; i <= n; ++i) {
    v[i] += v[i - 1];
  }
  for (int ijk = n; ijk >= 1; --ijk) {
    for (int j = 0; j <= ijk; ++j) {
      int min = +0x3b9aca00;
      for (int i = 0; i + j <= ijk; ++i) {
        int k = ijk - i - j;
        dp[i][j][k] = +0x3b9aca00;
        if (i == 0 && j == 0) {
          if (k == n) {
            dp[i][j][k] = 0;
          }
          if (ijk + i <= n) {
            min = std::min(min, dp[j + i][i][k]);
          }
          continue;
        }
        if (ijk + i <= n) {
          min = std::min(min, dp[j + i][i][k]);
        }
        dp[i][j][k] = min + v[n - k];
      }
    }
  }
  int i = 1, j = 0, k = 0, top = 0;
  while (i != 0 || j != 0 || k != n) {
    for (int l = 0; l <= i; ++l) {
      if (i + j + k + i - l <= n &&
          dp[i][j][k] == dp[j + i - l][i - l][k + l] + v[n - k]) {
        int _i = j + i - l, _j = i - l, _k = k + l;
        i = _i, j = _j, k = _k, leaf[++top] = l;
        break;
      }
    }
  }
  dep[1].push_back("");
  int c = 0;
  for (int i = 1; i <= top; ++i) {
    while (leaf[i]--) {
      ans[p[++c]] = dep[i].back();
      dep[i].pop_back();
    }
    for (auto j : dep[i]) {
      dep[i + 1].push_back(j + ".");
      dep[i + 2].push_back(j + "-");
    }
  }
  for (int i = 1; i <= n; ++i) {
    std::cout << ans[i] << '\n';
  }
  return 0;
}