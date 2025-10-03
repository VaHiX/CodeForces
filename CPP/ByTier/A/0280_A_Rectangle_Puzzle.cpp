/*
 * Problem URL : https://codeforces.com/contest/280/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  double x, y, t, z, a;
  cin >> x >> y >> t;
  z = min(x, y);
  a = t * 3.1415926535897932 / 180;
  if (t == 0) {
    cout << fixed << setprecision(9) << x * y;
  } else if (sin(a) > ((2 * x * y) / (x * x + y * y))) {
    cout << fixed << setprecision(9) << z * z / sin(a);
  } else {
    cout << fixed << setprecision(9)
         << 0.5 * (x * y) *
                    (abs(tan(a)) * sin(a) + abs(cos(a)) + (1 / (abs(cos(a))))) +
                (x * x + y * y) * ((abs(cos(a)) - 1) / abs(sin(2 * a)));
  }
}