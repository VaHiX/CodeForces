/*
 * Problem URL : https://codeforces.com/problemset/problem/2116/E
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define _                                                                      \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define f first
#define s second
#define pb push_back

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

double f[4005][8005], g[4005][4005];
int n, m;
double p;
int a[405];

void solve() {
  cin >> n >> m >> p;
  p /= 100;

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i]--;
  }

  sort(a + 1, a + n + 1);

  int k = 0;
  for (int i = 1; i <= n; i++)
    k += a[i] - a[1];

  for (int i = 0; i <= m; i++)
    for (int j = 0; j <= a[1] * n; j++)
      f[i][j] = 0;
  f[0][0] = 1;

  for (int i = 1; i <= m; i++) {
    f[i][0] = 1;
    for (int j = 1; j <= a[1] * n; j++) {
      f[i][j] = (1 - p) * max(f[i - 1][j], f[i - 1][j - 1]);
      if (j >= n)
        f[i][j] += p * max(f[i - 1][j], f[i - 1][j - n]);
      else
        f[i][j] += p * f[i - 1][j];
    }
  }

  for (int i = 0; i <= m; i++)
    for (int j = 0; j <= k; j++)
      g[i][j] = 0;
  g[0][0] = 1;

  for (int i = 1; i <= m; i++)
    for (int j = 0; j <= k; j++) {
      if (!j)
        g[i][j] = p * g[i - 1][j];
      else
        g[i][j] = p * g[i - 1][j] + (1 - p) * g[i - 1][j - 1];
    }

  double ans = 0;
  for (int i = k; i <= m; i++) {
    double q = 0;
    if (!i)
      q = 1;
    else {
      if (!k)
        q = 0;
      else
        q = g[i - 1][k - 1] * (1 - p);
    }
    ans += q * f[m - i][max(a[1] - (i - k), 0) * n];
  }

  cout << fixed << setprecision(10) << ans << "\n";
}

int main() {
  _ ll t;
  cin >> t;
  while (t--) {
    solve();
  }
}