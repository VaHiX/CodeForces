/*
 * Problem URL : https://codeforces.com/problemset/problem/2104/F
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h> //0xnnb
using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
const int N = 1000005;
int T, n, a[N], tot, now, las = 1;
bool check(int x) {
  int cnt0 = 0, cnt9 = 0;
  while (x) {
    int xx = x % 10;
    x /= 10;
    if (xx != 0 && xx != 9)
      return 1;
    if (!xx)
      cnt0++;
    else
      cnt9++;
  }
  return cnt0 != cnt9;
}
void dfs(int pos) {
  int xxx = 0;
  if (!now)
    xxx = -1;
  if (check(now))
    xxx = 8;
  for (int i = 0; i <= xxx; i++) {
    int tmp = now * 10 + i;
    if (tmp)
      a[++tot] = tmp;
    if (pos + 1 <= 9) {
      tmp = tmp * 10 + 9;
      a[++tot] = tmp;
    }
  }
  if (pos == 9)
    return;
  int tmp1 = now, tmp2 = las;
  for (int i = las; i <= 9; i++) {
    now = tmp1 * 10 + i;
    las = i;
    dfs(pos + 1);
    if (pos == 1) {
      for (int j = 2; j <= 8; j++) {
        now *= 10;
        dfs(j + 1);
      }
    }
  }
  now = tmp1, las = tmp2;
}
void init() {
  for (int i = 1; i <= 9; i++) {
    now = now * 10 + 9;
    a[++tot] = now;
  }
  for (int i = 1; i <= 8; i++) {
    now = i;
    a[++tot] = now;
    for (int j = 2; j <= 9; j++) {
      now = now * 10 + 9;
      a[++tot] = now;
    }
  }
  now = 0;
  dfs(1);
  sort(a + 1, a + tot + 1);
}
void solve() {
  n = read();
  int ans = upper_bound(a + 1, a + tot + 1, n) - a - 1;
  printf("%d\n", ans);
}
void clear() {}
int main() {
  init();
  T = read();
  for (int tt = 1; tt <= T; tt++) {
    solve();
    clear();
  }
  return 0;
}