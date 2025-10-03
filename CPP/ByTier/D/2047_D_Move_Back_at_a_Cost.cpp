/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, a[100005], mn, mnn, f[100005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    mn = mnn = 2e9;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      f[i] = 0;
    }
    for (int i = n - 1; i >= 0; i--) {
      if (mn > a[i])
        mn = a[i];
      if (a[i] > mn) {
        a[i]++;
        f[i] = 1;
        mnn = min(mnn, a[i]);
      }
    }
    for (int i = n - 1; i >= 0; i--)
      if (f[i] == 0 && a[i] > mnn)
        a[i]++;
    sort(a, a + n);
    for (int i = 0; i < n; i++)
      cout << a[i] << " ";
    cout << "\n";
  }
  return 0;
}