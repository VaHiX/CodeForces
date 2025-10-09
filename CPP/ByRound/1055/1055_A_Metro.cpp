/*
 * Problem URL : https://codeforces.com/problemset/problem/1055/A
 * Submit Date : 2025-08-18
 */

#include <iostream>
using namespace std;
int main() {
  int n, s, t = 0;
  cin >> n >> s;
  int a[n + 1], b[n + 1];
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
    if (i >= s && a[i] && b[i])
      t = 1;
  }
  if (a[1] && a[s])
    cout << "YES";
  else if (a[1] && b[s] && t)
    cout << "YES";
  else
    cout << "NO";
}