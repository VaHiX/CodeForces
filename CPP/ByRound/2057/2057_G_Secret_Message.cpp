/*
 * Problem URL : https://codeforces.com/problemset/problem/2057/G
 * Submit Date : 2025-08-24
 */

/* in the name of allah */
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define pb push_back
#define F first
#define S second
#define mk make_pair
typedef long long ll;

const int N = 2e6 + 7;
int n, m;
char a[N];
vector<int> vec[5];
int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};

int f(int i, int j) { return i * m + j; }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int q;
  cin >> q;
  while (q--) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> a[f(i, j)];
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int k = f(i, j);
        if (a[k] != '#')
          continue;
        vec[(i + 2 * j) % 5].pb(k);
        for (int h = 0; h < 4; h++) {
          int x = i + dx[h], y = j + dy[h];
          if ((x < 0 || x >= n || y < 0 || y >= m) || a[f(x, y)] == '.')
            vec[(x + 2 * y + 20) % 5].pb(k);
        }
      }
    }
    int sum = 0;
    for (int i = 0; i < 5; i++)
      sum += vec[i].size();
    for (int i = 0; i < 5; i++) {
      if (vec[i].size() <= sum / 5) {
        for (auto k : vec[i])
          a[k] = 'S';
        break;
      }
    }
    for (int i = 0; i < 5; i++)
      vec[i].clear();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << a[f(i, j)];
      }
      cout << endl;
    }
  }
}
