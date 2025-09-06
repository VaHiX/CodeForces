/*
 * Problem URL : https://codeforces.com/problemset/problem/1177/A
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int k, i;
  string a;
  for (i = 0; i < 10000; i++) {
    a += to_string(i);
  }
  cin >> k;
  cout << a[k];
}
