/*
 * Problem URL : https://codeforces.com/contest/305/problem/B
 * Submit Date : 2025-09-09
 */

#include <algorithm>
#include <iostream>

using namespace std;
long long p, q, a, i, n;
int main() {
  cin >> p >> q >> n;
  for (i = 0; i < n; i++) {
    cin >> a;
    if (q == 0)
      break;
    if (a > p / q)
      break;
    p -= a * q;
    swap(p, q);
  }
  cout << (i < n || q != 0 ? "NO" : "YES");
}