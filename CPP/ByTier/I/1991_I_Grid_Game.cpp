/*
 * Problem URL : https://codeforces.com/contest/1991/problem/I
 * Submit Date : 2025-09-07
 */

// LUOGU_RID: 169423309
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

pii pos[105], key[5], ot[5][4];
int a[15][15], d[15][15];
int c[15][15], ind, nw, n, m;
bool b[15][15];

void add(int sx, int sy, int x1, int y1, int x2, int y2, int x3, int y3) {
  c[sx][sy] = c[x1][y1] = c[x2][y2] = c[x3][y3] = ++ind;
  a[sx][sy] = ind, a[x1][y1] = ++nw, a[x2][y2] = ++nw, a[x3][y3] = ++nw;
  key[ind] = make_pair(sx, sy);
  ot[ind][1] = make_pair(x1, y1);
  ot[ind][2] = make_pair(x2, y2);
  ot[ind][3] = make_pair(x3, y3);
}

inline int id(int x, int y) { return (x - 1) * m + y; }
vector<int> g[105];

int n1, n2, tmpk;
int used[105], ans[105];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int found(int u) {
  for (int v : g[u])
    if (!used[v]) {
      used[v] = 1;
      if (!ans[v] || found(ans[v]))
        return ans[v] = u, 1;
    }
  return 0;
}

void match() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      if (!c[i][j])
        d[i][j] = (i + j) & 1;
      else
        d[i][j] = -1;
    }
  n1 = n2 = 0;
  for (int i = 1; i <= n * m; i++)
    g[i].clear(), ans[i] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      if (d[i][j] == -1)
        continue;
      if (d[i][j] == 1) {
        n1++;
        for (int k = 0; k < 4; k++) {
          int x = i + dx[k], y = j + dy[k];
          if (x <= 0 || x > n || y <= 0 || y > m || d[x][y] == -1)
            continue;
          g[id(i, j)].emplace_back(id(x, y));
        }
      } else
        n2++;
    }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (d[i][j] == 1)
        memset(used, 0, sizeof(used)), found(id(i, j));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (d[i][j] == 0) {
        int nw = ans[id(i, j)];
        int y = (nw - 1) % m + 1, x = (nw - y) / m + 1;
        pos[a[i][j] = ++tmpk] = make_pair(x, y);
        pos[a[x][y] = ++tmpk] = make_pair(i, j);
      }
}

void print(int x, int y) {
  cout << x << " " << y << "\n";
  cout.flush();
  b[x][y] = 1;
}
void print(pii nw) { print(nw.first, nw.second); }

bool adjacent(int x, int y) {
  return b[x - 1][y] || b[x][y - 1] || b[x][y + 1] || b[x + 1][y];
}

void work() {
  cin >> n >> m;
  ind = 0, nw = n * m - 12, tmpk = 4;
  for (int i = 1; i <= n + 1; i++)
    for (int j = 1; j <= m + 1; j++)
      a[i][j] = b[i][j] = c[i][j] = 0;
  if ((n & 1) && (m & 1)) {
    int k = 0;
    for (int i = 1; i <= n; i++) {
      if (i & 1)
        for (int j = 1; j <= m; j++)
          cout << (a[i][j] = ++k) << " ";
      else {
        int nw = k + m;
        k += m;
        for (int j = 1; j <= m; j++)
          cout << (a[i][j] = nw--) << " ";
      }
      cout << "\n";
    }
    cout.flush();

    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        if (i == n && j == m)
          break;
        int x = (a[i][j] & 1) ? a[i][j] + 1 : a[i][j] - 1;
        pos[x] = make_pair(i, j);
      }
    pos[n * m] = make_pair(n, m);

    for (int i = 1; i <= n * m; i += 2) {
      int x, y;
      cin >> x >> y;
      if (i == n * m)
        break;
      int v = a[x][y];
      b[x][y] = 1;
      pii nw = pos[v];
      if (b[nw.first][nw.second]) {
        for (int j = 1; j <= n; j++) {
          bool Fl = false;
          for (int k = 1; k <= m; k++)
            if (!b[j][k] && adjacent(j, k)) {
              print(j, k);
              Fl = true;
              break;
            }
          if (Fl)
            break;
        }
        continue;
      }
      print(nw);
    }
    return;
  }

  if (n == 4 && m == 4) {
    add(1, 2, 1, 1, 2, 2, 1, 3);
    add(3, 1, 2, 1, 3, 2, 4, 1);
    add(4, 3, 4, 2, 4, 4, 3, 3);
    add(2, 4, 1, 4, 3, 4, 2, 3);
  } else {
    if (n == 4 && m == 5) {
      add(1, 2, 1, 1, 2, 2, 1, 3);
      add(3, 1, 2, 1, 3, 2, 4, 1);
      add(4, 3, 4, 2, 4, 4, 3, 3);
      add(3, 5, 2, 5, 4, 5, 3, 4);
    } else if (n == 5 && m == 4) {
      add(2, 1, 1, 1, 2, 2, 3, 1);
      add(1, 3, 1, 2, 2, 3, 1, 4);
      add(3, 4, 2, 4, 4, 4, 3, 3);
      add(5, 3, 5, 2, 5, 4, 4, 3);
    } else {
      if (n > m) {
        add(2, 1, 1, 1, 2, 2, 3, 1);
        add(1, 3, 1, 2, 1, 4, 2, 3);
        add(n - 1, 1, n - 2, 1, n - 1, 2, n, 1);
        add(n, 3, n, 2, n, 4, n - 1, 3);
      } else {
        add(1, 2, 1, 1, 2, 2, 1, 3);
        add(3, 1, 2, 1, 3, 2, 4, 1);
        add(1, m - 1, 1, m - 2, 2, m - 1, 1, m);
        add(3, m, 2, m, 4, m, 3, m - 1);
      }
    }
    match();
  }

  for (int i = 1; i <= n; i++, cout << "\n")
    for (int j = 1; j <= m; j++)
      cout << a[i][j] << " ";
  cout.flush();

  for (int i = 1; i <= n * m; i += 2) {
    int x, y;
    cin >> x >> y;
    b[x][y] = 1;
    if (c[x][y]) {
      int id = c[x][y];
      pii nw = key[id];
      if (!b[nw.first][nw.second])
        print(nw);
      else {
        for (int j = 1; j <= 3; j++)
          if (!b[ot[id][j].first][ot[id][j].second]) {
            print(ot[id][j]);
            break;
          }
      }
    } else
      print(pos[a[x][y]]);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}