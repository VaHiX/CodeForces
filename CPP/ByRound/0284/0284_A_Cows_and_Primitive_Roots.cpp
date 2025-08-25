/*
 * Problem URL : https://codeforces.com/problemset/problem/284/A
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int a, b = 0, i;
main() {
  cin >> a;
  for (i = 1; i < a; i++)
    if (__gcd(a - 1, i) == 1)
      b++;
  cout << b;
}