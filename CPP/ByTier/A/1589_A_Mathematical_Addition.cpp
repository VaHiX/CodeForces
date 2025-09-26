/*
 * Problem URL : https://codeforces.com/contest/1589/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int T, u, v;
  for (cin >> T; T--;)
    cin >> u >> v, cout << 1ll * u * u << ' ' << -1ll * v * v << '\n';
}