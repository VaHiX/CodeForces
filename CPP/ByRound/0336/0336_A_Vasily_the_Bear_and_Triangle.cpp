/*
 * Problem URL : https://codeforces.com/problemset/problem/336/A
 * Submit Date : 2025-08-09
 */

#include <cmath>
#include <iostream>

using namespace std;

int main() {
  int x, y;
  cin >> x >> y;
  if (x > 0) {
    if (y > 0) {
      cout << 0 << " " << x + y << " " << x + y << " " << 0 << endl;
    } else {
      cout << 0 << " " << y - x << " " << x - y << " " << 0 << endl;
      ;
    }
  } else {
    if (y > 0) {
      cout << x - y << " " << 0 << " " << 0 << " " << y - x << endl;
      ;
    } else {
      cout << x + y << " " << 0 << " " << 0 << " " << x + y << endl;
      ;
    }
  }
  return 0;
}
