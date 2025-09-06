/*
 * Problem URL : https://codeforces.com/contest/606/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/606/problem/A
 * Submit Date : 2025-09-02
 */



#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b, c;
  int x, y, z;
  int beshi = 0, kom = 0;

  cin >> a >> b >> c;
  cin >> x >> y >> z;

  if (a > x)
    beshi = beshi + (a - x) / 2;
  else
    kom = kom + x - a;

  if (b > y)
    beshi = beshi + (b - y) / 2;
  else
    kom = kom + y - b;

  if (c > z)
    beshi = beshi + (c - z) / 2;
  else
    kom = kom + z - c;

  if (beshi >= kom)
    cout << "YES";
  else
    cout << "NO";

  return 0;
}
