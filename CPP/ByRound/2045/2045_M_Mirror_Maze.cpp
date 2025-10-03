/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
#define FOR(i, l, r) for (int i = l; i <= r; ++i)
#define el '\n'
using namespace std;

vector<vector<char>> m;

int R, C, mir = 0, id = 0;

vector<string> v;

int kt[210][210];

bool sol(int u, int v, int x, int y) {
  int cnt = 0;
  while (true) {
    if (x < 1 || x > R || y < 1 || y > C)
      return false;
    if (m[x][y] != '.') {
      swap(u, v);
      if (kt[x][y] != id)
        ++cnt, kt[x][y] = id;
      if (m[x][y] == '/')
        u = -u, v = -v;
    }
    if (cnt == mir)
      return true;
    x += u;
    y += v;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(false);
  cin >> R >> C;
  m.resize(R + 1, vector<char>(C + 1));
  memset(kt, 0, sizeof(kt));
  FOR(i, 1, R)
  FOR(j, 1, C) {
    cin >> m[i][j];
    if (m[i][j] != '.')
      ++mir;
  }

  FOR(j, 1, C) {
    id++;
    if (sol(1, 0, 1, j))
      v.push_back("N" + to_string(j));
    id++;
    if (sol(-1, 0, R, j))
      v.push_back("S" + to_string(j));
  }
  FOR(i, 1, R) {
    id++;
    if (sol(0, 1, i, 1))
      v.push_back("W" + to_string(i));
    id++;
    if (sol(0, -1, i, C))
      v.push_back("E" + to_string(i));
  }

  cout << v.size() << el;
  for (auto &e : v)
    cout << e << ' ';
}
