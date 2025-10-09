/*
 * Problem URL : https://codeforces.com/contest/2035/problem/C
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    if (n & 1) {
      cout << n << "\n";
      for (int i = 4; i < n - 1; i++)
        cout << i << " ";
      cout << "2 1 3 " << n - 1 << " " << n << "\n";
    } else if (n == 6)
      cout << "7\n1 2 4 6 5 3\n";
    else {
      int k = 2147483648LL >> __builtin_clz(n);
      cout << (k << 1) - 1 << "\n";
      for (int i = 4; i < k - 2; i++)
        cout << i << " ";
      for (int i = k; i < n; i++)
        cout << i << " ";
      cout << "2 1 3 " << k - 2 << " " << k - 1 << " " << n << "\n";
    }
  }
}