/*
 * Problem URL : https://codeforces.com/problemset/problem/2055/E
 * Submit Date : 2025-08-24
 */

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF 0x3f3f3f3f
#define INFL 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
typedef long long ll;

const int N = 5e5 + 2;
struct ab {
  int a, b;
  bool operator<(const ab &o) const {
    int x = (b > a) + (b >= a);
    int y = (o.b > o.a) + (o.b >= o.a);
    if (x != y)
      return x > y;

    if (x == 2)
      return a < o.a;
    return b > o.b;
  }
};
int t, n;
ab p[N];
ll a[N], b[N], pm[N], sm[N];
ll oa[N], ob[N];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> p[i].a >> p[i].b;
    }
    sort(p + 1, p + 1 + n);
    for (int i = 1; i <= n; i++) {
      a[i] = a[i - 1] + p[i].a;
      b[i] = b[i - 1] + p[i].b;
    }

    for (int i = 1; i <= n; i++) {
      pm[i] = max(pm[i - 1], a[i] - b[i - 1]);
    }

    sm[n] = 0;
    for (int i = n - 1; i >= 1; i--) {
      ll as = a[n] - a[i];
      ll bs = b[n - 1] - b[i - 1];
      sm[i] = max(sm[i + 1], -as + bs);
    }

    ll ans = INFL;
    for (int i = 1; i <= n; i++) {
      if (a[n] <= b[n] - p[i].b) {
        ll cur = pm[i - 1];
        if (i != n) {
          cur = max(cur, sm[i + 1] + (a[n] - p[i].a) - (b[n - 1] - p[i].b));
        }
        ans = min(ans, cur);
      }
    }
    if (ans == INFL)
      cout << -1 << endl;
    else
      cout << ans + a[n] << endl;
  }
}