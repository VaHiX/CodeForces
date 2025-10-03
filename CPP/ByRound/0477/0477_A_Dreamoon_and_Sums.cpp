/*
 * Problem URL : https://codeforces.com/contest/477/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  long long a, b;
  cin >> a >> b;
  cout << ((((b * (b - 1)) / 2) % 1000000007) *
           ((((a * (a + 1) / 2) % 1000000007) * b) % 1000000007 + a)) %
              1000000007;
  return 0;
} /*1691455360.0559719*/