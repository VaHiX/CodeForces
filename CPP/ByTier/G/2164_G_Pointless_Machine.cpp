// Problem: CF 2164 G - Pointless Machine
// https://codeforces.com/contest/2164/problem/G

/*
Purpose:
This program solves the interactive problem "G. Pointless Machine" where the goal is to reconstruct a hidden tree by querying the number of edges in induced subgraphs.
The approach uses a technique based on representing each vertex using a 10-digit base-3 number and performing multiple queries to determine the tree structure.

Algorithms/Techniques:
- Interactive problem solving using multiple queries
- Representation of vertices using base-3 numbers
- Induced subgraph edge counting
- BFS-based reconstruction of tree edges

Time Complexity: O(n log n)
Space Complexity: O(n)

The algorithm works by:
1. Generating 31 different permutations of vertex indices for queries
2. For each query, it computes the number of edges in the induced subgraph
3. Uses the differences between consecutive query results to deduce edge connections
4. Reconstructs the tree using BFS traversal based on vertex degrees and edge counts

*/
#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <utility>
#include <vector>

#define rep(i, l, r) for (auto i(l), i##_end(r); i <= i##_end; ++i)
#define per(i, r, l) for (auto i(r), i##_end(l); i >= i##_end; --i)
#define fi first
#define se second
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define SZ(a) ((int)(a).size())
using namespace std;
using cint = const int;
using ll = long long;
using cll = const long long;
using ull = unsigned long long;
#if __SIZEOF_POINTER__ == 8
using lll = __int128;
#endif
using db = double;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
mt19937 rnd(random_device{}());
mt19937_64 rnd64(random_device{}());
void debug() { cerr << endl; }
template <typename T, typename... Args> void debug(T t, Args... args) {
  cerr << t;
  if (sizeof...(args))
    cerr << ", ";
  debug(args...);
}
#define deb(x...)                                                              \
  do {                                                                         \
    cerr << #x << ": ";                                                        \
    debug(x);                                                                  \
  } while (0)
template <typename T> bool cmax(T &a, const T &b) {
  return b > a ? a = b, 1 : 0;
}
template <typename T> bool cmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
const int N = 5e4 + 5;
int n;
int q[10][3][N], pos[10][3][N], a[10][3][N];
int q0[N], a0[N];
int pw[10], d[N];
void task() {
  cin >> n;
  rep(i, 0, n) d[i] = 0;
  pw[0] = 1;
  rep(i, 1, 9) pw[i] = pw[i - 1] * 3;
  rep(i, 0, 9) {
    rep(c, 0, 2) {
      int t = 0;
      rep(x, 0, 2) rep(j, 1, n) if (j / pw[i] % 3 == (c + x) % 3) q[i][c][++t] =
          j;
    }
  }
  rep(i, 1, n) q0[i] = q[0][0][n - i + 1];
  cout << "31\n";
  rep(i, 0, 9) rep(c, 0, 2) rep(j, 1, n) {
    pos[i][c][q[i][c][j]] = j;
    cout << q[i][c][j] << " \n"[j == n];
  }
  rep(j, 1, n) cout << q0[j] << " \n"[j == n];
  cout.flush();
  rep(i, 0, 9) rep(c, 0, 2) {
    rep(j, 1, n) cin >> a[i][c][j];
    per(j, n, 1) a[i][c][j] -= a[i][c][j - 1];
  }
  rep(j, 1, n)(cin >> a0[j]);
  per(j, n, 1) a0[j] -= a0[j - 1];
  rep(i, 1, n) {
    d[q[0][0][i]] += a[0][0][i];
    d[q0[i]] += a0[i];
  }
  queue<int> q;
  rep(i, 1, n) if (d[i] == 1) q.push(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (d[u] != 1)
      continue;
    int v = 0;
    rep(i, 0, 9) {
      int r = u / pw[i] % 3, ca[3];
      rep(c, 0, 2) ca[c] = a[i][c][pos[i][c][u]];
      if (ca[(r + 2) % 3] - ca[r])
        v += (r + 2) % 3 * pw[i];
      else if (ca[(r + 1) % 3] - ca[(r + 2) % 3])
        v += (r + 1) % 3 * pw[i];
      else
        v += r * pw[i];
    }
    cout << u << " " << v << "\n";
    d[u]--, d[v]--;
    if (d[v] == 1)
      q.push(v);
    rep(i, 0, 9) {
      rep(c, 0, 2) {
        if (pos[i][c][u] < pos[i][c][v])
          a[i][c][pos[i][c][v]]--;
        else
          a[i][c][pos[i][c][u]]--;
      }
    }
  }
  cout.flush();
}
int main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    task();
}


// https://github.com/VaHiX/CodeForces/