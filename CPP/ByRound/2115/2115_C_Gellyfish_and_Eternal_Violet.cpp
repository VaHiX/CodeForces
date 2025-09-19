/*
 * Problem URL : https://codeforces.com/problemset/problem/2115/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
#define fi first
#define endl '\n'
#define il inline
#define se second
#define pb push_back
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
const int N = 4e3 + 10;
int n, m, S, x, T;
double p, Q, f[N][N], g[N << 1];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int mi = 1000;
    cin >> n >> m >> p, p *= 0.01, Q = 1 - p, S = 0;
    for (int i = 1; i <= n; i++)
      cin >> x, mi = min(mi, --x), S += x;
    if ((S -= x = mi * n) > m) {
      cout << 0 << endl;
      continue;
    }
    f[0][0] = g[0] = 1, memset(g + 1, 0, x << 3);
    for (int i = 1, j; i <= m; i++)
      for (j = 1; j <= S && j <= i; j++)
        f[i][j] = p * f[i - 1][j] + Q * f[i - 1][j - 1];
    double res = f[m][S] * (m - S >= mi);
    for (int i = 1, j; i <= m - S; i++) {
      for (j = x; j >= 1; j--)
        g[j] = p * (j >= n ? g[j - n] : g[j]) + Q * max(g[j], g[j - 1]);
      res += f[m - i][S] * g[max(mi - m + i + S, 0) * n];
    }
    cout << fixed << setprecision(7) << res << endl;
  }
  return 0;
}