/*
 * Problem URL : https://codeforces.com/problemset/problem/1967/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
int n, k, a[N];
void work() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  a[n + 1] = 2e13;
  for (int i = 1; i <= n; i++) {
    int cha = a[i + 1] - a[i];
    if (k - cha * i >= 0) {
      k -= cha * i;
    } else {
      int zj = a[i];
      zj += k / i;
      int zengj = (k % i + (n - i));
      cout << zj * n + zengj - n + 1 << endl;
      return;
    }
  }
  return;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    work();
  return 0;
}