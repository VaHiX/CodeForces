/*
 * Problem URL : https://codeforces.com/problemset/problem/2068/I
 * Submit Date : 2025-08-23
 */

#include "bits/stdc++.h"
using namespace std;
#define all(x) x.begin(), x.end()
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << p.first << " " << p.second;
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  string sep;
  for (const T &x : v)
    os << sep << x, sep = " ";
  return os;
}
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#define ASSERT(...) 42
#endif
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pi;
const int oo = 1e9;
typedef complex<short> pt;
#define X real()
#define Y imag()
const pt dir4[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const string name = "DRUL";
const pt dir8[] = {{1, 0},  {1, 1},   {0, 1},  {-1, 1},
                   {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
const pt hdir[] = {{2, 1},   {1, 2},   {-1, 2}, {-2, 1},
                   {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
int n, m;
bool inside(pt p) { return 0 <= p.X and p.X < n and 0 <= p.Y and p.Y < m; }
void read(pt &p) {
  int a, b;
  cin >> a >> b;
  p = {a, b};
}
auto newdir(pt d, char c) {
  if (c == '.')
    return d;
  if (c == '#')
    return -d;
  if (c == '\\') {
    if (d.Y) {
      return d * pt{0, -1};
    }
    return d * pt{0, 1};
  } else {
    if (d.Y) {
      return d * pt{0, 1};
    }
    return d * pt{0, -1};
  }
}
int id(pt d) { return find(dir4, dir4 + 4, d) - dir4; }
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  vector<string> g(n);
  for (auto &i : g) {
    cin >> i;
  }
  pt s;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == 'S') {
        s = {i, j};
        g[i][j] = '.';
      }
    }

  vector<basic_string<int>> adj;
  vector<bool> isend;
  vector<pair<pt, pt>> whereend;

  vector who(n, vector(m, array<int, 4>{-1, -1, -1, -1}));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (g[i][j] != '#') {
        for (int o = 0; o < 4; ++o) {
          if (who[i][j][o] ==
              -1) { // position + what heading do I have coming in?
            int my = adj.size();
            adj.push_back({});
            isend.push_back(0);
            whereend.push_back({});
            pt at = {i, j};
            pt d = dir4[o];
            while (who[at.X][at.Y][id(d)] == -1) {
              who[at.X][at.Y][id(d)] = my;
              pt nd = newdir(d, g[at.X][at.Y]);
              pt to = at + nd;
              if (!inside(to)) {
                isend[my] = 1;
                whereend[my] = {at, -nd};
                nd = -nd;
                to = at;
              }
              at = to;
              d = nd;
            }
          }
        }
      }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (g[i][j] == '/' or g[i][j] == '\\') {
        auto &w = who[i][j];
        for (int a = 0; a < 4; ++a)
          for (int b = 0; b < 4; ++b)
            if (a != b) {
              adj[w[a]].push_back(w[b]);
            }
      }
  int k = adj.size();
  vi dist(k, oo);
  vi q;
  auto push = [&](int i, int di) {
    if (dist[i] == oo) {
      dist[i] = di;
      q.push_back(i);
    }
  };
  for (int o = 0; o < 4; ++o) {
    push(who[s.X][s.Y][o], 0);
  }
  for (int i = 0; i < q.size(); ++i) {
    int at = q[i];
    for (int to : adj[at])
      push(to, dist[at] + 1);
  }
  int endzone = -1;
  for (int i = 0; i < k; ++i)
    if (isend[i] and dist[i] != oo) {
      if (endzone == -1 or dist[endzone] > dist[i]) {
        endzone = i;
      }
    }
  if (endzone == -1) {
    cout << "NO\n";
    exit(0);
  }
  cout << "YES\n";
  auto [at, d] = whereend[endzone];
  int t = 0;
  vector<pair<pt, int>> broke;
  while (at != s) {
    int myd = dist[who[at.X][at.Y][id(d)]];
    bool fnd = 0;
    pt nd;
    if (g[at.X][at.Y] == '/' or g[at.X][at.Y] == '\\') {
      // check if leads to lower
      for (int o = 0; o < 4; ++o) {
        if (dist[who[at.X][at.Y][o]] < myd) {
          fnd = 1;
          nd = d;
          broke.push_back({at, t});
          break;
        }
      }
    }
    if (!fnd) {
      nd = newdir(d, g[at.X][at.Y]);
    }
    at += nd;
    d = nd;
    if (g[at.X][at.Y] != '#')
      t++;
  }

  cout << name[id(-d)] << '\n';
  cout << dist[endzone] << '\n';
  reverse(all(broke));
  for (auto &[at, mt] : broke) {
    mt = t - mt;
    cout << mt << ' ' << at.X + 1 << ' ' << at.Y + 1 << '\n';
  }
}