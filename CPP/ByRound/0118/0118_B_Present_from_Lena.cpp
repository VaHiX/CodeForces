/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <iostream>
using namespace std;
int i, j, k, l, n;
main() {
  for (cin >> n; i++ < n + n + 1; cout << endl)
    for (j = 0; j++ < (l = n + n - (n + 1 > i ? n - i : i - n - 2));)
      (k = n + (n + 1 < i ? n + 1 - i : i - n - 1) +
           (n + 1 < j ? n + 1 - j : j - n - 1)) < 0
          ? cout << "  ",
          0 : (cout << k, j < l ? cout << ' ', 0 : 0);
}
