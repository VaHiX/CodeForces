/*
 * Problem URL : https://codeforces.com/contest/1415/problem/A
 * Submit Date : 2025-09-01
 */

#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, T;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &m, &a, &b);
    cout << max(a - 1, n - a) + max(b - 1, m - b) << "\n";
  }
  return 0;
}
