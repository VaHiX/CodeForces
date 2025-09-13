/*
 * Problem URL : https://codeforces.com/contest/2148/problem/G
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
vector<int> fac[N];
int n, a[N], cnt[N];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  for (int i = 2; i <= N - 5; i++) {
    if (fac[i].empty()) {
      for (int j = i; j <= N - 5; j += i) {
        fac[j].push_back(i);
      }
    }
  }
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    int gc = 0, lst = 0, ans;
    for (int i = 1; i <= n; i++) {
      gc = __gcd(gc, a[i]);
      if (gc != lst) {
        fill(cnt + 1, cnt + n + 1, 0);
        ans = 0;
        for (int j = 1; j <= i; j++) {
          for (int k : fac[a[j] / gc]) {
            cnt[k]++;
            ans = max(ans, cnt[k]);
          }
        }
      } else {
        for (int k : fac[a[i] / gc]) {
          cnt[k]++;
          ans = max(ans, cnt[k]);
        }
      }
      lst = gc;
      cout << ans << ' ';
    }
    cout << endl;
  }
  return 0;
}