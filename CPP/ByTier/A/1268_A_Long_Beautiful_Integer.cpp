/*
 * Problem URL : https://codeforces.com/contest/1268/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  int ls = s.size();
  for (int i = m; i < ls; i++) {
    if (s[i] > s[i % m]) {
      int j = 1;
      while (s[m - j] == '9') {
        s[m - j] = '0';
        j++;
      }
      ++s[m - j];
      break;
    }
    if (s[i] < s[i % m])
      break;
  }
  cout << n << '\n';
  for (int i = 0; i < n; i++)
    cout << s[i % m];
  cout << '\n';
  return 0;
}