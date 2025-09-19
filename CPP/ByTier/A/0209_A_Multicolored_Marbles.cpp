/*
 * Problem URL : https://codeforces.com/contest/209/problem/A
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
int f[1000005];
int main() {
  int n;
  cin >> n;
  f[0] = f[1] = 1;
  for (int i = 2; i <= n + 2; ++i)
    f[i] = (f[i - 1] + f[i - 2]) % 1000000007;
  cout << f[n + 2] - 2;
  return 0;
}
