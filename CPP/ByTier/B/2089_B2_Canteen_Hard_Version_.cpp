/*
 * Problem URL : https://codeforces.com/problemset/problem/2089/B2
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define F(i, f, t) for (int i = (f), _end = (t); i <= _end; i++)
#define D(i, f, t) for (int i = (f), _end = (t); i >= _end; i--)
#define dbg(x) cerr << #x << '=' << x << endl
#define mems(x, y) memset(x, y, sizeof x)
#define memc(x, y) memcpy(x, y, sizeof x)

using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using d128 = long double;

const int N = 3e5, M = 5000;
const i64 MOD = 998244353;
using intn = int[N];
using i64n = i64[N];

i64 n, k;
i64n a, b, sm;
void Sol() {
  cin >> n >> k;
  F(i, 1, n) cin >> a[i];
  F(i, 1, n) cin >> b[i];
  F(i, 1, n) sm[i] = 0;
  stack<pair<i64, i64>> S;
  i64 Ans = n;
  F(i, 1, 2 * n) {
    i64 I = (i - 1) % n + 1;
    if (a[I])
      S.push({a[I], i}), a[I] = 0;
    if (b[I])
      while (!S.empty() && b[I]) {
        i64 x = min(S.top().first, b[I]);
        S.top().first -= x, b[I] -= x;
        sm[i - S.top().second + 1] += x;
        if (S.top().first == 0)
          S.pop();
      }
  }
  D(i, n, 1) {
    if (k - sm[i] < 0) {
      cout << i << endl;
      return;
    } else
      k -= sm[i];
  }
  cout << 0 << endl;
}

int main() {

  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--)
    Sol();
  // while(T--) puts(Sol()?"yes":"no");
  // Sol();
  return 0;
}