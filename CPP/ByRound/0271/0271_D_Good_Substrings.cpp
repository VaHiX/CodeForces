/*
 * Problem URL : https://codeforces.com/problemset/problem/271/D
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
long long a[3000000], k, c;
char s[1520], v[30];
int main() {
  cin >> s >> v >> k;
  for (int i = 0; s[i]; i++)
    for (long long j = i, kk = k, h = 0; s[j] && (v[s[j] - 'a'] > '0' || kk--);
         j++)
      a[c++] = h = (h * 131) ^ s[j];
  sort(a, a + c);
  cout << unique(a, a + c) - a;
}