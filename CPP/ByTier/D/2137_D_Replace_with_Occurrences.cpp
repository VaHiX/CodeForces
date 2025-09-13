/*
 * Problem URL : https://codeforces.com/contest/2137/problem/D
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int x;
    cin >> x;
    vector<int> y(x);
    for (int i = 0; i < x; i++)
      cin >> y[i];
    unordered_map<int, vector<int>> z;
    for (int i = 0; i < x; i++)
      z[y[i]].push_back(i);
    vector<int> w(x, -1);
    int p = 1, q = 1;
    for (auto u = z.begin(); u != z.end(); ++u) {
      int v = u->first;
      auto &r = u->second;
      if ((int)r.size() % v) {
        q = 0;
        break;
      }
      for (int i = 0; i < (int)r.size(); i += v) {
        for (int j = 0; j < v; j++)
          w[r[i + j]] = p;
        p++;
      }
    }
    if (!q)
      cout << "-1\n";
    else {
      for (int i = 0; i < x; i++)
        cout << w[i] << " ";
      cout << "\n";
    }
  }
}
