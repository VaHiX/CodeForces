/*
 * Problem URL : https://codeforces.com/contest/1032/problem/B
 * Submit Date : 2025-09-11
 */

#include <bits/stdc++.h>
using namespace std;
int n, i, j, k, x, c, r;
string s;
int main() {
  cin >> s;
  n = s.size();
  for (c = 20; r = (n + c - 1) / c, x = r * c - n, x >= r; c--)
    ;
  cout << r << " " << c << endl;
  for (i = 0; i < r; cout << endl, i++)
    for (j = 0; j < c; j++)
      cout << (j == 0 && i < x ? '*' : s[k++]);
}