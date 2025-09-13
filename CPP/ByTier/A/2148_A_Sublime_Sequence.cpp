/*
 * Problem URL : https://codeforces.com/contest/2148/problem/A
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int tt;
  cin >> tt;
  while (tt--) {
    int n, x;
    cin >> x >> n;
    if (n % 2 == 0)
      cout << '0' << endl;
    else
      cout << x << endl;
  }
}