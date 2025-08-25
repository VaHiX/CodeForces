/*
 * Problem URL : https://codeforces.com/problemset/problem/858/D
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
#define IOS                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define endl "\n"
#define Max(x, y, z) max(x, max(y, z))
#define Min(x, y, z) min(x, min(y, z))
unordered_map<string, int> P;
string s[70001];
int n, i, j, k;
int main() {
  for (cin >> n, i = 1; i <= n; i++)
    for (cin >> s[i], j = 1; j <= 9; j++)
      for (k = 0; j + k <= 9; k++) {
        int &x = P[s[i].substr(k, j)];
        x = x == 0 || x == i ? i : -1;
      }
  for (auto &p : P) {
    i = p.second;
    if (i > 0 && s[i].size() > p.first.size())
      s[i] = p.first;
  }
  for (i = 1; i <= n; i++)
    cout << s[i] << "\n";
}