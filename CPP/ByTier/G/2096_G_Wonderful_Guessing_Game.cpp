/*
 * Problem URL : https://codeforces.com/problemset/problem/2096/G
 * Submit Date : 2025-08-20
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

const int N = 2e5 + 7;

int a[20][N];

void f(int l, int r, int d) {
  if (l >= r)
    return;
  int m = (r - l + 2) / 3;
  for (int i = l; i < l + m; i++)
    a[d][i] = 1;
  for (int i = r - m + 1; i <= r; i++)
    a[d][i] = 2;
  f(l, l + m - 1, d + 1);
  f(l + m, r - m, d + 1);
  f(r - m + 1, r, d + 1);
}

void task() {
  int n;
  cin >> n;
  for (int i = 0; i < 20; i++)
    fill(a[i], a[i] + n, 0);
  int q = 0, qq = 1;
  while (qq < n)
    qq *= 3, q++;
  f(0, n - 1, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < q; j++)
      a[q][i] += a[j][i];
    a[q][i] = (3 - a[q][i] % 3) % 3;
  }
  cout << q + 1 << endl;
  vector<int> ok(n, 1);
  for (int i = 0; i <= q; i++) {
    vector<int> u, v;
    for (int j = 0; j < n; j++) {
      if (a[i][j] == 1)
        u.pb(j + 1);
      if (a[i][j] == 2)
        v.pb(j + 1);
    }
    cout << u.size() + v.size() << " ";
    for (int x : u)
      cout << x << " ";
    for (int x : v)
      cout << x << " ";
    cout << endl;
  }
  string s;
  cin >> s;
  for (int i = 0; i <= q; i++) {
    if (s[i] == 'L') {
      for (int j = 0; j < n; j++)
        if (a[i][j] != 1)
          ok[j] = 0;
    } else if (s[i] == 'R') {
      for (int j = 0; j < n; j++)
        if (a[i][j] != 2)
          ok[j] = 0;
    } else if (s[i] == 'N') {
      for (int j = 0; j < n; j++)
        if (a[i][j])
          ok[j] = 0;
    }
  }
  for (int i = 0; i < n; i++)
    if (ok[i]) {
      cout << i + 1 << endl;
      break;
    }
}

int main() {
  FIO;
  int tt;
  cin >> tt;
  while (tt--)
    task();

  return 0;
}
