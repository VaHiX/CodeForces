/*
 * Problem URL : https://codeforces.com/problemset/problem/2068/F
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

vector<string> s;
vector<char> c[202020];

int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  s.resize(n);
  for (int i = 0; i < n; i++)
    cin >> s[i];
  string t;
  cin >> t;
  string ans = "";
  for (int i = 0; i < n; i++) {
    int r = 0;
    for (int j = 0; j < s[i].size(); j++) {
      if (s[i][j] == t[r]) {
        r++;
        if (r == t.size())
          return !(cout << "NO");
      } else
        c[r].push_back(s[i][j]);
    }
  }
  cout << "YES\n";
  for (int i = 0; i < t.size(); i++) {
    for (auto x : c[i])
      cout << x;
    if (i != t.size() - 1)
      cout << t[i];
  }
}