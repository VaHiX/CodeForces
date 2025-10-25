/*
 * Problem URL : https://codeforces.com/contest/474/problem/B
 * Submit Date : 2025-09-06
 */

#include <iostream>
using namespace std;
int n, arr[1000003], i, x = 1, m, t;
int main() {
  cin >> n;
  for (i = 1; i <= n; i++) {
    cin >> t;
    while (t--)
      arr[x] = i, x++;
  }
  cin >> m;
  while (m--)
    cin >> t, cout << arr[t] << endl;
}
