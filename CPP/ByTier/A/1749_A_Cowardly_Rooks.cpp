/*
 * Problem URL : https://codeforces.com/problemset/problem/1749/A
 * Submit Date : 2025-08-21
 */

#include <iostream>
using namespace std;
int main() {
  int t, n, m, tt;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
      cin >> tt >> tt;
    if (n > m)
      puts("YES");
    else
      puts("NO");
  }
}
