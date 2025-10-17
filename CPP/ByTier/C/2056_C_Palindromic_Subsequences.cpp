/*
 * Problem URL : https://codeforces.com/problemset/problem/2056/C
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
int T, n;
int main() {
  cin >> T;
  while (T--) {
    cin >> n;
    cout << "1 1 ";
    for (int i = 2; i <= n - 2; i++)
      cout << i << " ";
    cout << "1\n";
  }
  return 0;
}