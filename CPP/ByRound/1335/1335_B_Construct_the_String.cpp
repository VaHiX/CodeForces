/*
 * Problem URL : https://codeforces.com/problemset/problem/1335/B
 * Submit Date : 2025-08-15
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t, n, a, b;
  for (cin >> t; t--; cout << endl)
    for (cin >> n >> a >> b; n--;)
      cout << (char)(122 - n % b);
}
