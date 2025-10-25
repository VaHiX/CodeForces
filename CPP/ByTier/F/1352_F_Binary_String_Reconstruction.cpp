/*
 * Problem URL : https://codeforces.com/contest/1352/problem/F
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
// not my code
int main() {
  int t, a, b, c;
  cin >> t;
  while (t--) {
    cin >> a >> b >> c;
    cout << (!a || b || c);
    while (c--)
      cout << 1;
    while (a--)
      cout << 0;
    while (++a < b)
      cout << a % 2;
    puts("");
  }
}
