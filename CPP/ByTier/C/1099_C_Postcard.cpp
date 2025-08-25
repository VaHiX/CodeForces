/*
 * Problem URL : https://codeforces.com/problemset/problem/1099/C
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
int i, k, c;
string s;
int main() {
  cin >> s >> k;
  for (auto e : s)
    c += e != '?' && e != '*';
  for (i = 0; i < s.size(); i++)
    if (s[i] == '*' && c < k)
      s.insert(i, k - c, s[i - 1]), c = k;
    else if (s[i] == '?' || s[i] == '*') {
      s.erase(i--, 1);
      if (c > k)
        s.erase(i--, 1), c--;
    }
  cout << (k == c ? s : "Impossible");
}