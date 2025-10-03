/*
 * Problem URL : https://codeforces.com/contest/240/problem/A
 * Submit Date : 2025-09-06
 */

#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAXN = 128;

bool fav[MAXN];
int g_max[MAXN], g_min[MAXN];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n, m, k, d, x, ans_min = 0;
  scanf("%d%d", &m, &k);
  for (int i = 0; i < k; ++i) {
    scanf("%d", &x);
    fav[x] = true;
  }
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%*s%d", &d);
    for (int j = 0; j < d; ++j) {
      scanf("%d", &x);
      if (!x || fav[x])
        ++g_max[i];
      if (fav[x])
        ++g_min[i];
    }
    if (d - g_min[i] > m - k)
      g_min[i] = d - m + k;
    if (g_max[i] > k)
      g_max[i] = k;
    ans_min = std::max(ans_min, g_min[i]);
  }
  for (int i = 0; i < n; ++i) {
    bool ma = true;
    for (int j = 0; j < n; ++j) {
      if (i == j)
        continue;
      if (g_max[j] > g_min[i])
        ma = false;
    }
    if (ma)
      puts("0");
    else if (g_max[i] < ans_min)
      puts("1");
    else
      puts("2");
  }
  return 0;
}