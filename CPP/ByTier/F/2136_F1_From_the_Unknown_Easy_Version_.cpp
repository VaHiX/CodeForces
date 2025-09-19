/*
 * Problem URL : https://codeforces.com/contest/2136/problem/F1
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
#define lint long long
#define fi first
#define se second
using namespace std;
const int N = 2e5 + 5, INF = 1e9;
int mx = 100000;
void solve() {
  cout << "? " << mx << " ";
  for (int i = 1; i <= mx; ++i)
    cout << 1 << " ";
  cout << endl;
  cout.flush();
  int a;
  cin >> a;
  if (a == 1) {
    cout << "! " << mx << endl;
    return;
  }
  int s = (mx + a - 1) / a;
  int t = (mx + (a - 1) - 1) / (a - 1);
  if (s + 1 == t) {
    cout << "! " << s << endl;
    return;
  }
  cout << "? " << (t - s - 1) * 2 << " ";
  for (int i = 1; i <= t - s - 1; ++i) {
    cout << s << " " << i << " ";
  }
  cout << endl;
  cout.flush();
  int x;
  cin >> x;
  cout << "! " << s + (t - s - 1) * 2 - x << endl;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}
