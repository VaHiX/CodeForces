/*
 * Problem URL : https://codeforces.com/contest/883/problem/M
 * Submit Date : 2025-09-08
 */

#import <bits/stdc++.h>
using namespace std;
int a, b, c, d;
main() {
  cin >> a >> b >> c >> d;
  a = abs(a - c), b = abs(b - d);
  cout << 2 * (a + !a + b + !b + 2);
}
