#include <bits/stdc++.h>
using namespace std;
int n, m, ans, now, l;
signed main() {
  scanf("%d%d", &n, &m);
  for (int x, i = 1; i <= n; i++, l = x)
    scanf("%d", &x), x == l ? now = 1 : ans = max(ans, ++now);
  cout << ans;
}