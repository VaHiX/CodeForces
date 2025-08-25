/*
 * Problem URL : https://codeforces.com/problemset/problem/2132/C2
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
#define int long long
#define PII pair<int, int>
#define x first
#define y second
#define endl '\n'
#define mod 1000000007
using namespace std;
int c[25], thr[25];

void csh() {
  int x = 3;
  for (int i = 0; i < 25; i++) {
    c[i] = (x + i * x / 9);
    x *= 3;
  }
}

void sl() {
  int n, k, ans = 0;
  memset(thr, 0, sizeof(thr));
  cin >> n >> k;
  int w = 0;
  while (n) {
    thr[w] = (n % 3);
    k -= (n % 3);
    n /= 3;
    w++;
  }
  if (k < 0) {
    cout << -1 << endl;
    return;
  }
  for (int i = 24; i > 0; i--) {
    int now = min(k / 2, thr[i]);
    thr[i] -= now;
    thr[i - 1] += now * 3;
    k -= now * 2;
  }
  for (int i = 0; i < 25; i++) {
    ans += c[i] * thr[i];
  }
  cout << ans << endl;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int _ = 1;
  csh();
  cin >> _;
  while (_--)
    sl();
  return 0;
}