/*
 * Problem URL : https://codeforces.com/contest/1210/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
int g[10][10];

int main() {
  int n, m, a, b;
  cin >> n >> m;
  if (n <= 6) {
    cout << m << endl;
    return 0;
  }
  for (int i = 0; i < m; i++)
    cin >> a >> b, g[a][b] = g[b][a] = 1;

  int mn = 1e9;
  for (int i = 1; i <= 7; i++)
    for (int j = 1; j <= 7; j++) {
      int x = 0;
      for (int k = 1; k <= 7; k++)
        if (g[i][k] && g[k][j])
          x++;
      mn = min(mn, x);
    }
  cout << m - mn;
}