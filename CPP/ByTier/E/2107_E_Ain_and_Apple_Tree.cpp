/*
 * Problem URL : https://codeforces.com/problemset/problem/2107/E
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
int n;
ll k;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    vector<int> ans;
    ll tmp, val;
    for (int i = n - 1; i >= 1; i--) {
      tmp = 1ll * (i - 1) * i / 2;
      if (k >= tmp)
        k -= tmp, ans.push_back(i);
    }
    if (k > 1) {
      cout << "No\n";
      continue;
    }
    cout << "Yes\n";
    int id = 1, siz = n, tot = n;
    for (int cur : ans) {
      for (int i = 1; i <= siz - cur - 1; i++)
        cout << id << " " << (tot--) << "\n";
      cout << id << " " << (++id) << "\n";
      siz = cur;
    }
  }
  return 0;
}