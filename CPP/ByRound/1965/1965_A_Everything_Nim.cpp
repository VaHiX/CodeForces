/*
 * Problem URL : https://codeforces.com/problemset/problem/1965/A
 * Submit Date : 2025-08-20
 */

// LUOGU_RID: 157471744
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
int T, n, x, a[N];
void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  sort(a + 1, a + n + 1), n = unique(a + 1, a + n + 1) - a - 1, x = 0;
  for (int i = 1; i <= n; ++i)
    if (a[i] == i)
      x = i;
  cout << (((x == n) != (x & 1)) ? "Bob" : "Alice") << endl;
}
int main() {
  for (ios::sync_with_stdio(0), cin >> T; T--;)
    solve();
  return 0;
}