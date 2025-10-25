/*
 * Problem URL : https://codeforces.com/contest/788/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
long long n, a1, a2, b, c, d, t, f;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> a1;
  while (--n) {
    cin >> a2;
    b = abs(a1 - a2);
    a1 = a2;
    t = c;
    c = max(b, d + b);
    f = max(f, c);
    d = t - b;
  }
  cout << f;
  return 0;
}
