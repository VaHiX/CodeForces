/*
 * Problem URL : https://codeforces.com/problemset/problem/2094/H
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>

#define F first
#define S second
#define all(x) x.begin(), x.end()
#define pb push_back
#define FIO                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0)

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 1e5 + 7;
vector<int> d[N], p[N];
vector<pii> qu[N];

void task() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n), ri(q);
  vector<ll> res(q);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < q; i++) {
    int x, l;
    cin >> x >> l >> ri[i];
    l--;
    ri[i]--;
    qu[l].pb({i, x});
  }
  for (int i = n - 1; i >= 0; i--)
    p[a[i]].pb(i);
  for (int i = 0; i < n; i++) {
    p[a[i]].pop_back();
    for (auto x : qu[i]) {
      while (x.S % a[i] == 0)
        x.S /= a[i];
      int r = ri[x.F] + 1;
      for (int y : d[x.S])
        if (!p[y].empty())
          r = min(r, p[y].back());
      res[x.F] += x.S * (r - i);
      if (r <= ri[x.F])
        qu[r].pb(x);
    }
    qu[i].clear();
  }
  for (int i = 0; i < q; i++)
    cout << res[i] << "\n";
}

int main() {
  FIO;
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i)
      d[j].pb(i);
  }
  int tt;
  cin >> tt;
  while (tt--)
    task();

  return 0;
}
