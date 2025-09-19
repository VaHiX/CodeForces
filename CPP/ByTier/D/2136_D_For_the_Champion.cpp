/*
 * Problem URL : https://codeforces.com/contest/2136/problem/D
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
#define N 200009
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3fll
using namespace std;
int n;
ll a, b;
ll u, v;
void solve() {
  cin >> n;
  a = b = -INF;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    a = max(a, (ll)x + y);
    b = max(b, (ll)x - y);
  }
  cout << "? U 1000000000" << endl;
  cin >> u;
  cout << "? U 1000000000" << endl;
  cin >> u;
  cout << "? R 1000000000" << endl;
  cin >> u;
  cout << "? R 1000000000" << endl;
  cin >> u;
  cout << "? D 1000000000" << endl;
  cin >> v;
  cout << "? D 1000000000" << endl;
  cin >> v;
  cout << "? D 1000000000" << endl;
  cin >> v;
  cout << "? D 1000000000" << endl;
  cin >> v;
  u += a;
  v += b;
  u -= 4000000000ll;
  v -= 4000000000ll;
  cout << "!" << " " << (u + v) / 2 << " " << (u - v) / 2 << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}