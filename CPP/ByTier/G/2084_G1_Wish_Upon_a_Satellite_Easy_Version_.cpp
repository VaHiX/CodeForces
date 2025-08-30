/*
 * Problem URL : https://codeforces.com/problemset/problem/2084/G1
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int maxn = 5005;
const ll inf = 1e18;

int vs[maxn], a[maxn];
ll f[maxn], g[maxn];

void work() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    vs[i] = -1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i])
      vs[a[i]] = (i & 1);
  }

  int x = (n + 1) / 2;
  for (int i = 1; i <= x; i++)
    f[i] = -inf;
  f[0] = 0;
  for (int i = n; i; i--) {
    for (int j = 0; j <= x && j <= n - i; j++)
      g[j] = f[j], f[j] = -inf;
    for (int j = 0; j <= x && j <= n - i; j++) {
      if (vs[i] != 0)
        f[j + 1] = max(f[j + 1], g[j] + 1ll * i * (x - j + n - i - j));
      if (vs[i] != 1)
        f[j] = max(f[j], g[j] + 1ll * i * (i + j + j - x));
    }
  }
  cout << f[x] << "\n";
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);

  int T = 1;
  cin >> T;
  while (T--)
    work();
  return 0;
}