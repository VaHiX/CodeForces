/*
 * Problem URL : https://codeforces.com/contest/524/problem/A
 * Submit Date : 2025-09-05
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  int m, k;
  cin >> m >> k;
  int g[m], q[m];
  for (int i = 0; i < m; i++)
    cin >> g[i] >> q[i];
  map<int, int> sp;
  vector<int> x;
  for (int i = 0; i < m; i++) {
    sp[g[i]] = sp[q[i]] = 1;
  }
  for (map<int, int>::iterator t = sp.begin(); t != sp.end(); t++) {
    t->second = x.size();
    x.push_back(t->first);
  }
  int n = x.size();
  vector<vector<int>> gq(n);
  for (int i = 0; i < m; i++) {
    gq[sp[g[i]]].push_back(sp[q[i]]);
    gq[sp[q[i]]].push_back(sp[g[i]]);
  }
  for (int i = 0; i < n; i++) {
    vector<bool> b(n);
    for (int g : gq[i])
      b[g] = 1;
    vector<int> pd;
    for (int j = 0; j < n; j++) {
      if (j != i && !b[j]) {
        int c = 0;
        for (int g : gq[j])
          c += b[g];
        if (c * 100 >= k * gq[i].size()) {
          pd.push_back(x[j]);
        }
      }
    }
    cout << x[i] << ": ";
    cout << pd.size();
    for (int t : pd)
      cout << ' ' << t;
    cout << '\n';
  }
  return 0;
}
