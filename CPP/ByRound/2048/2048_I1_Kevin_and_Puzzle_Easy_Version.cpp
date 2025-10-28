#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
const int MAXN = 2e5 + 5;
int n, a[MAXN], ok;
char s[MAXN];
int dfs(int l, int r, int d, int x) {
  if (l > r)
    return 0;
  if (l == r)
    return a[l] = x;
  if (s[l] == s[r]) {
    a[l] = x, a[r] = max(x, dfs(l + 1, r - 1, 1, x + 1)) + 1;
    if (s[r] == 'R')
      swap(a[l], a[r]);
    return max(a[l], a[r]);
  }
  if (s[l] == 'L')
    return a[l] = a[r] = x, max(x, dfs(l + 1, r - 1, d, x + 1));
  ok &= d != 1, fill(a + l, a + r + 1, x + 1);
  return x + 1;
}
void solve() {
  cin >> n, ok = 1;
  for (int i = 1; i <= n; ++i)
    cin >> s[i], a[i] = 0;
  dfs(1, n, -1, 0);
  if (!ok)
    cout << "-1\n";
  else
    for (int i = 1; i <= n; ++i)
      cout << a[i] << " \n"[i == n];
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int _;
  cin >> _;
  while (_--)
    solve();
  return 0;
}