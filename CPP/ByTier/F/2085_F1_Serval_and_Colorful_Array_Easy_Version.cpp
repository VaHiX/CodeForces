#include <bits/std_abs.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define int long long
const int mzhxi = 1e18;
const int nn = 4e5 + 5;
int n, k, s, d, ans;
int a[nn], lst[nn], sum[nn];
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    s = 0, ans = mzhxi;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
      lst[i] = sum[i] = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      if (!lst[a[i]])
        s += i - 1;
      else {
        int pre = lst[a[i]], mid = (pre + i) / 2;
        if ((pre + i) & 1)
          sum[mid]--, sum[mid + 1]--;
        else
          sum[mid] -= 2;
      }
      sum[i] += 2;
      lst[a[i]] = i;
    }
    d -= k;
    for (int i = 1; i <= n; i++) {
      ans = min(ans, s);
      d += sum[i], s += d;
    }
    for (int i = 1; i <= k; i++)
      ans -= abs(i - (k + 1) / 2);
    cout << ans << endl;
    n = k = d = s = ans = 0;
  }
  return 0;
}