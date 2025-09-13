/*
 * Problem URL : https://codeforces.com/contest/2027/problem/C
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
#define int long long
int T, n;
const int maxn = 3e5 + 5;
pair<int, int> a[maxn];
void solve() {
  set<int> st;
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i].first, a[i].first += i - 1, a[i].second = i;
  sort(a + 1, a + n + 1);
  st.emplace(n);
  for (int i = 1; i <= n; ++i)
    if (st.count(a[i].first))
      st.emplace(a[i].first + a[i].second - 1);
  cout << *st.rbegin() << '\n';
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--)
    solve();
}