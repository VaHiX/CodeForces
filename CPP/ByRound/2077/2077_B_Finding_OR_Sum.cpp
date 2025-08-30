/*
 * Problem URL : https://codeforces.com/problemset/problem/2077/B
 * Submit Date : 2025-08-22
 */

#include <iostream>
using namespace std;
int main() {
  int t, a = 715827882, c, d, m;
  cin >> t;
  while (t--)
    cout << a / 2 << " " << a << " !\n", cin >> c >> d >> m,
        cout << ((a / 2 & ~m) * 3 & d - 2 * a) + 2 * m + ((a & ~m) * 3 & c - a)
             << '\n';
}
