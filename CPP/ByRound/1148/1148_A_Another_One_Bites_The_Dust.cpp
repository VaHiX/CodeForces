/*
 * Problem URL : https://codeforces.com/contest/1148/problem/A
 * Submit Date : 2025-08-28
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  long long a, b, c;
  cin >> a >> b >> c;
  cout << (2 * min(a, b) + 2 * c + (a != b));
}