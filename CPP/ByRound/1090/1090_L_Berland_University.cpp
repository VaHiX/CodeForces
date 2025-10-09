/*
 * Problem URL : https://codeforces.com/contest/1090/problem/L
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
long long n, m, a, b, k, l, r, ans;
int main() {
  cin >> n >> m >> a >> b >> k;
  l = 1;
  r = n;
  while (l <= r) {
    long long mid = (l + r) / 2;
    long long sum =
        ((m / 2 + m % 2) * min(a, mid) + (m / 2) * min(b, mid)) / mid;
    if (sum >= k) {
      ans = mid;
      l = mid + 1;
    } else
      r = mid - 1;
  }
  cout << ans;
  return 0;
}