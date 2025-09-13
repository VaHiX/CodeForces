/*
 * Problem URL : https://codeforces.com/problemset/problem/2074/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n, q;
  cin >> n;
  int x = 1, y = n / 2 + 1, z = n;
  printf("? %d %d %d\n", x, y, z);
  cin >> q;
  while (q != 0) {
    x = y;
    y = z;
    z = q;
    printf("? %d %d %d\n", x, y, z);
    cin >> q;
  }
  printf("! %d %d %d\n", x, y, z);

  return;
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}
