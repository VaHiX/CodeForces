/*
 * Problem URL : https://codeforces.com/contest/2138/problem/D
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7, N = 5010, maxn = 5000;

int mi(int x, int t) {
  int d = 1;
  while (t) {
    if (t & 1)
      d = (ll)d * x % mod;
    x = (ll)x * x % mod;
    t /= 2;
  }
  return d;
}
int ni(int x) { return mi(x, mod - 2); }

struct node {
  int id, x, y;
};
int fl[N];

int main() {
  cin.sync_with_stdio(false);
  cin.tie(0);
  fl[0] = 1;
  for (int i = 1; i <= maxn; i++)
    fl[i] = (ll)fl[i - 1] * i % mod;

  int T;
  cin >> T;
  while (T--) {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    vector<node> b(q + 1);
    for (int i = 1; i <= q; i++)
      cin >> b[i].id >> b[i].x;
    sort(b.begin() + 1, b.end(),
         [&](auto n1, auto n2) { return (n1.x - n1.id < n2.x - n2.id); });

    vector<int> Ni(q + 1);
    for (int i = 1; i <= q; i++)
      Ni[i] = ni(i);
    for (int i = 1; i <= n; i++) {
      int good = 0, bad = 0, zero = 0;
      for (int j = 1; j <= q; j++) {
        if (b[j].id <= i)
          good++;
        else
          zero++;
        b[j].y = b[j].x - b[j].id + i;
      }
      int ans;
      if (good) {
        ans = (ll)fl[q] * b[1].y % mod;
        for (int j = 1; j <= q; j++) {
          if (b[j].id <= i)
            good--;
          else
            zero--;
          if (b[j].id >= i)
            bad++;
          else
            zero++;
          if (j == q)
            break;
          // cout << good << ' ' << bad << ' ' << b[j + 1].y - b[j].y << ' ' <<
          // ans << '\n';
          if (!good && !bad) {
            if (a[i] > b[j].y) {
              ans = (ans + (ll)fl[q] * (min(a[i], b[j + 1].y) - b[j].y)) % mod;
            }
          } else {
            int res = (ll)fl[q] * Ni[good + bad] % mod * good % mod;
            ans = (ans + (ll)res * (b[j + 1].y - b[j].y)) % mod;
          }
        }
        if (!bad)
          ans = (ans + (ll)fl[q] * max(0, a[i] - b[q].y)) % mod;
      } else
        ans = (ll)fl[q] * min(a[i], b[1].y) % mod;
      cout << ans << ' ';
    }
    cout << '\n';
  }

  return 0;
}