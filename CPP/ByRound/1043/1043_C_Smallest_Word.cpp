/*
 * Problem URL : https://codeforces.com/problemset/problem/1043/C
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
string s;
void solve() {
  s += 'b';
  for (int i = 0; i < s.size() - 1; i++) {
    cout << (s[i] != s[i + 1]) << " ";
  }
}
int main() {
  cin >> s;
  solve();
}