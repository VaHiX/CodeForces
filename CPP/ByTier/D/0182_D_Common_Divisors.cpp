/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
int ans = 0;
string a, b;
bool check(string s, int m) {
  for (int i = 0; i < s.size(); i++)
    if (s[i] != a[i % m])
      return 0;
  return 1;
}
int main() {
  cin >> a >> b;
  for (int i = 1; i < a.size() + b.size(); i++)
    if (a.size() % i == 0 && b.size() % i == 0)
      ans += (check(a, i) & check(b, i));
  cout << ans << endl;
}