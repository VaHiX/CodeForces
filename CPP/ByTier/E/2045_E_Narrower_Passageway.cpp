/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

// Author: Aquizahv
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int N = 1e5 + 5, MOD = 998244353;
int n, a[3][N], L[3][N], R[3][N], ans;
int P2[N], *p2 = P2 + 1;

int A(int x, int y) { return x + y >= MOD ? x + y - MOD : x + y; }
int A(initializer_list<int> t) {
  int res = 0;
  for (auto i : t)
    res = A(res, i);
  return res;
}
void SA(int &x, int y) { x = A(x, y); }
int S(int x, int y) { return A(x, MOD - y); }
int W(int x, int y) { return 1ll * x * y % MOD; }
int W(initializer_list<int> t) {
  int res = 1;
  for (auto i : t)
    res = W(res, i);
  return res;
}
void SW(int &x, int y) { x = W(x, y); }
int P(int x, int y) {
  int res = 1, t = x % MOD;
  while (y) {
    if (y & 1)
      res = W(res, t);
    t = W(t, t);
    y >>= 1;
  }
  return res;
}
int D(int x, int y) { return W(x, P(y, MOD - 2)); }
int Q(int x) { return W(x, x); }

int tp, stk[N];
void monostack(int *a, int *L, int *R, bool flag) {
  tp = 0, stk[0] = 0;
  for (int i = 1; i <= n; i++) {
    while (tp > 0 && a[stk[tp]] <= a[i])
      tp--;
    L[i] = stk[tp] + 1;
    stk[++tp] = i;
  }
  tp = 0, stk[0] = n + 1;
  for (int i = n; i >= 1; i--) {
    while (tp > 0 && a[stk[tp]] < a[i] + flag)
      tp--;
    R[i] = stk[tp] - 1;
    stk[++tp] = i;
  }
}

int main() {
#ifdef Aquizahv
  freopen("data.in", "r", stdin);
  freopen("data.out", "w", stdout);
#endif
  cin >> n;
  p2[0] = 1;
  for (int i = 1; i <= n; i++)
    p2[i] = W(p2[i - 1], 2);
  for (int i = 1; i <= n; i++)
    scanf("%d", a[0] + i);
  for (int i = 1; i <= n; i++)
    scanf("%d", a[1] + i), a[2][i] = max(a[0][i], a[1][i]);
  for (int i = 0; i <= 1; i++)
    monostack(a[i], L[i], R[i], 0);
  monostack(a[2], L[2], R[2], 1);
  for (int i = 1; i <= n; i++) {
    for (int k = 0; k <= 1; k++) {
      // cout << p2[i - 1] << ' ' << L[k][i] - 2 << ' ' << p2[L[k][i] - 2] << '
      // ' << p2[n - i] << ' ' << p2[n - R[k][i] - 1] << endl;
      SA(ans, W(a[k][i], W(S(p2[i - 1], p2[L[k][i] - 2]),
                           S(p2[n - i], p2[n - R[k][i] - 1]))));
      if (a[k][i] == a[2][i])
        ans = S(ans,
                W(a[k][i], W(S(p2[i - 1], p2[L[2][i] - 2]),
                             S(p2[n - i], p2[n - min(R[2][i], R[k][i]) - 1]))));
    }
  }
  cout << D(ans, p2[n]) << endl;
  return 0;
}