/*
 * Problem URL : https://codeforces.com/contest/633/problem/B
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  int a, x = 1, b;

  while (a < n) {
    b = x;
    while (b % 5 == 0) {
      a++;
      b /= 5;
    }
    x++;
  }
  if (a != n) {
    cout << 0;
    return 0;
  }

  cout << 5 << endl
       << x - 1 << " " << x << " " << x + 1 << " " << x + 2 << " " << x + 3;
}
