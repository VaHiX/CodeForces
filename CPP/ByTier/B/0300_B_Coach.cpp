/*
 * Problem URL : https://codeforces.com/contest/300/problem/B
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
vector<int> V[20];
vector<int> ve;
int n, m, a, b, c, t[50];

bool add(int a, int b) {
  t[a] = b;
  V[b].push_back(a);
  return (V[b].size() >= 4);
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    if (!t[a] && !t[b])
      c++, add(a, c), add(b, c);
    if (c * 3 > n || t[a] && t[b] && t[a] != t[b] ||
        t[a] && !t[b] && add(b, t[a]) || t[b] && !t[a] && add(a, t[b])) {
      cout << -1;
      return 0;
    }
  }

  for (int i = 1; i <= n; i++)
    if (!t[i]) {
      ve.push_back(i);
    }
  int id = 0;
  for (int i = 1; i <= (n / 3); i++) {
    for (int j = 0; j < 3; j++) {
      cout << ((j < V[i].size()) ? V[i][j] : ve[id++]) << ' ';
    }
    cout << endl;
  }

  return 0;
}
