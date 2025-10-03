/*
 * Problem URL : https://codeforces.com/contest/559/problem/B
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
using I = int;
using S = string;
S dfs(S s) {
  if (s.size() % 2)
    return s;
  I n = s.size(), m = n / 2;
  S a = dfs(s.substr(0, m));
  S b = dfs(s.substr(m, n));
  return a > b ? b + a : a + b;
}
I main() {
  cin.tie(0)->sync_with_stdio(0);
  S a;
  cin >> a;
  S b;
  cin >> b;
  printf("%s\n", dfs(a) == dfs(b) ? "YES" : "NO");
}