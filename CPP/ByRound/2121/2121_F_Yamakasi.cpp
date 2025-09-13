/*
 * Problem URL : https://codeforces.com/problemset/problem/2121/F
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N];
long long sum[N];
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, x;
    long long s;
    cin >> n >> s >> x;
    for (int i = 1; i <= n; i++)
      cin >> a[i], sum[i] = sum[i - 1] + a[i];
    long long ans = 0;
    map<long long, int> cnt;
    int l = 1;
    for (int r = 1; r <= n; r++) {
      if (a[r] > x)
        cnt.clear(), l = r + 1;
      else if (a[r] == x) {
        for (; l <= r; l++)
          cnt[sum[l - 1]]++;
      }
      ans += cnt[sum[r] - s];
    }
    cout << ans << "\n";
  }
  return 0;
}