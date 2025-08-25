/*
 * Problem URL : https://codeforces.com/problemset/problem/2129/F1
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, a[850];
vector<vector<int>> p;
map<vector<int>, int> id;
int main() {
  p.push_back(vector<int>());
  for (int i = 1; i <= 30; i++)
    p.push_back(vector<int>(1, i));
  p.push_back(vector<int>());
  for (int i = 1; i <= 30; i++)
    for (int j = i + 1; j <= 30; j++)
      p.push_back((vector<int>){i, j});
  for (int i = 1; i <= 9; i++)
    for (int j = 0; j <= 28; j++)
      p.push_back((vector<int>){i * j % 29 + 1, i * (j + 1) % 29 + 1, 30});
  p.erase(find(p.begin(), p.end(), (vector<int>){1, 2, 30})),
      p.erase(find(p.begin(), p.end(), (vector<int>){3, 4, 30})),
      p.erase(find(p.begin(), p.end(), (vector<int>){5, 6, 30})),
      p.push_back((vector<int>){1, 2, 3}), p.push_back((vector<int>{4, 5, 6}));
  for (int i = 0; i <= 2; i++)
    for (int j = i; j <= i + 3; j++)
      for (int k = 0; k < 10; k++)
        p.push_back((vector<int>){k + 1, 11 + (k + i) % 10, 21 + (k + j) % 10});
  for (int i = 1; i <= 846; i++)
    sort(p[i].begin(), p[i].end()), id[p[i]] = i;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> q[35], pos[850];
    for (int i = 1; i <= n; i++)
      for (int j = 0; j < p[i].size(); j++)
        q[p[i][j]].push_back(i);
    for (int i = 1; i <= min(30, n); i++) {
      cout << (i == 30 ? 3 : 1) << ' ' << q[i].size() << ' ';
      for (int j = 0; j < q[i].size(); j++)
        cout << q[i][j] << (j == q[i].size() - 1 ? '\n' : ' ');
      fflush(stdout);
      for (int j = 0, t; j < q[i].size(); j++)
        cin >> t, pos[t].push_back(i);
    }
    for (int i = 1; i <= n; i++)
      a[id[pos[i]]] = i;
    cout << "! ";
    for (int i = 1; i <= n; i++)
      cout << a[i] << (i == n ? '\n' : ' ');
  }
  return 0;
}