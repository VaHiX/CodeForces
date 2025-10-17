/*
 * Problem URL : https://codeforces.com/contest/370/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
int a, b, c, d;
int main() {
  cin >> a >> b >> c >> d;
  cout << 2 - (a == c || b == d) << ' '
       << ((a + b) % 2 == (c + d) % 2) *
              (2 - (a - b == c - d || a + b == c + d))
       << ' ' << max(abs(c - a), abs(d - b));
}