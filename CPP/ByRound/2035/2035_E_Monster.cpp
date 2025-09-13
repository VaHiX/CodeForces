/*
 * Problem URL : https://codeforces.com/contest/2035/problem/E
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define endl '\n'
typedef pair<int, int> PII;
void solve() {
  int x, y, z, k;
  cin >> x >> y >> z >> k;
  int ans = x + y * z;
  int z1 = z, sum = 0, sq = sqrt(z), d;
  for (int i = 1; i <= sq; i++) {
    sum += x;
    if (i % k == 0) {
      sum += y;
      z1 -= i;
    }
    d = z1 / i;
    if (z1 % i != 0)
      d++;
    ans = min(ans, sum + d * y);
  }
  int ind = sq / k * k;
  sum -= (sq - ind) * x;
  if (ind != 0) {
    d = z1 / ind;
    if (z1 % ind != 0)
      d++;
  }
  while (d > 0) {
    int a = z1 / d;
    if (z1 % d != 0)
      a++;
    if (a - ind > k) {
      ind += k;
      z1 -= ind;
      sum += y + x * k;
      d--;
      continue;
    }
    ans = min(ans, max(a - ind, 0ll) * x + d * y + sum);
    d--;
  }
  cout << ans << endl;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}