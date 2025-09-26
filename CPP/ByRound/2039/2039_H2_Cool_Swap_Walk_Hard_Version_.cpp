/*
 * Problem URL : https://codeforces.com/contest/2039/problem/H2
 * Submit Date : 2025-08-25
 */

// #define NDEBUG
#include <bits/stdc++.h>
#define For(i, j, k) for (int i = (j); i <= (k); i++)
#define ForD(i, j, k) for (int i = (j); i >= (k); i--)
#define int long long
#define endl '\n'
using namespace std;
bool Mbe;
const int N = 500;
int a[N], id[N];
void solve() {
  int n;
  cin >> n;
  For(i, 0, n - 1) cin >> a[i], id[i] = i;
  if (n <= 2) {
    if (a[0] > a[1])
      cout << 1 << endl << "RD" << endl;
    else
      cout << 0 << endl;
    return;
  }
  sort(id, id + n, [&](int x, int y) { return a[x] < a[y]; });
  For(i, 0, n - 1) a[id[i]] = (i + 4) % n;
  cout << n + 4 << endl;
  For(i, 0, n + 3) {
    for (int j = 2; j < n; j += 2) {
      int x = (i + j - 1) % n, y = (x + 1) % n;
      if (y && a[x] > a[y])
        swap(a[x], a[y]), cout << "RRDD";
      else
        cout << "RDRD";
    }
    if (!(n & 1))
      cout << "RD";
    cout << endl;
  }
}
bool Med;
signed main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int _ = 1;
  cin >> _;
  while (_--)
    solve();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}