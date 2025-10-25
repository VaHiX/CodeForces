/*
 * Problem URL : https://codeforces.com/contest/1076/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;

int n, i;
string s;

int main() {
  cin >> n >> s;
  while (i < n && s[i++] <= s[i])
    ;
  s.erase(s.begin() + i - 1);
  cout << s;
}