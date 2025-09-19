/*
 * Problem URL : https://codeforces.com/problemset/problem/245/A
 * Submit Date : 2025-08-09
 */

#include <iostream>

using namespace std;

int main() {
  int n, t, x, y, xa(0), ya(0), xb(0), yb(0);
  cin >> n;
  while (n--) {
    cin >> t >> x >> y;
    if (t == 1) {
      xa += x;
      ya += y;
    } else {
      xb += x;
      yb += y;
    }
  }
  cout << (xa >= ya ? "LIVE" : "DEAD") << endl;
  cout << (xb >= yb ? "LIVE" : "DEAD") << endl;
  return 0;
}
