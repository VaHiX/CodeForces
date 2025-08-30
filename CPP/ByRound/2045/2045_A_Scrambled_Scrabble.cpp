/*
 * Problem URL : https://codeforces.com/problemset/problem/2045/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  string a;
  cin >> a;
  int y = 0, g = 0, n = 0, e = 0, b = 0;
  for (const char &i : a) {
    if (i == 'A' || i == 'E' || i == 'O' || i == 'U' || i == 'I')
      ++e;
    else if (i == 'Y')
      ++y;
    else
      ++b;
    n += i == 'N';
    g += i == 'G';
  }
  const int y1 = max(min((2 * e + 2 * y - b + 2) / 3, y), 0);
  b += y1;
  e += y - y1;
  g = min({g, n, e * 2, max(b - e * 2, b & 1)});
  cout << g + 3 * min((b - g) / 2, e);
  return 0;
}