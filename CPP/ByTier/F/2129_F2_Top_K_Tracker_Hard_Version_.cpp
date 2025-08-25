/*
 * Problem URL : https://codeforces.com/problemset/problem/2129/F2
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, a[895], pos[895];
bool type[450];
vector<vector<int>> p;
map<vector<int>, int> id;
int main() {
  srand(time(0)), p.push_back(vector<int>());
  for (int i = 1; i <= 29; i++)
    p.push_back(vector<int>(1, i));
  p.push_back(vector<int>());
  for (int i = 1; i <= 29; i++)
    for (int j = i + 1; j <= 29; j++)
      p.push_back((vector<int>){i, j});
  for (int k = 0; k < 9; k++)
    p.push_back((vector<int>){k + 1, k + 10, k + 19});
  for (int i = 1; i <= 445; i++)
    id[p[i]] = i;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> q[35], e[895];
    for (int i = 1; i <= n / 2; i++)
      for (int j = 0; j < p[i].size(); j++)
        q[p[i][j]].push_back(i), q[p[i][j]].push_back(n - i + 1);
    if (n & 1)
      for (int j = 0; j < p[n / 2 + 1].size(); j++)
        q[p[n / 2 + 1][j]].push_back(n / 2 + 1);
    for (int i = 1; i < 30; i++) {
      if (q[i].empty())
        continue;
      cout << 2 << ' ' << q[i].size() << ' ';
      for (int j = 0; j < q[i].size(); j++)
        cout << q[i][j] << (j == q[i].size() - 1 ? '\n' : ' ');
      fflush(stdout);
      for (int j = 0, t; j < q[i].size(); j++)
        cin >> t, e[t].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
      if (pos[id[e[i]]])
        pos[n - id[e[i]] + 1] = i;
      else
        pos[id[e[i]]] = i;
    }
    cout << 3 << ' ' << n / 2 << ' ';
    for (int i = 1; i <= n / 2; i++)
      type[i] = rand() & 1,
      cout << pos[type[i] ? n - i + 1 : i] << (i == n / 2 ? '\n' : ' ');
    fflush(stdout);
    set<int> temp;
    for (int i = 1, t; i <= min(n / 2, 300); i++)
      cin >> t, temp.insert(t);
    for (int i = 1; i <= n / 2; i++)
      if ((temp.find(n - i + 1) != temp.end()) ^ type[i])
        swap(pos[i], pos[n - i + 1]);
    for (int i = 1; i <= n; i++)
      a[pos[i]] = i, pos[i] = 0;
    cout << "! ";
    for (int i = 1; i <= n; i++)
      cout << a[i] << (i == n ? '\n' : ' ');
    fflush(stdout);
  }
  return 0;
}