/*
 * Problem URL : https://codeforces.com/problemset/problem/2068/J
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
int t, n, k, l, h;
string c;
void C() {
  cin >> n >> c;
  k = count(c.begin(), c.begin() + n, 'W');
  if (k % 2 == 0 && count(c.begin(), c.begin() + k / 2, 'R') == 0 &&
      count(c.end() - k / 2, c.end(), 'W') == 0)
    cout << "YES\n";
  else
    cout << "NO\n";
}
int main() {
  // ios::sync_with_stdio(0);
  // cin.tie(0);cout.tie(0);
  cin >> t;
  while (t--)
    C();
  return 0;
}
