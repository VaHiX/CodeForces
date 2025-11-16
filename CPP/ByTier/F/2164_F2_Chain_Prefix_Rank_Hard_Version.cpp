// Problem: CF 2164 F2 - Chain Prefix Rank (Hard Version)
// https://codeforces.com/contest/2164/problem/F2

/*
Algorithm: Dynamic Programming with Tree Traversal and Fenwick Tree
Purpose: Count permutations satisfying ancestor condition for each node in a tree

Time Complexity: O(n log n) per test case
Space Complexity: O(n) for storage and recursion stack

This solution uses tree traversal with dynamic programming approach where:
- For each node, we process its children recursively
- We maintain a Fenwick Tree to efficiently compute prefix sums
- We use combinatorics and modular arithmetic for counting valid permutations
- The problem involves counting permutations such that for each node u,
  exactly a[u] ancestors v have p[v] < p[u]

Key components:
1. Tree construction from parent array
2. DFS traversal for bottom-up processing
3. Fenwick Tree for efficient prefix operations
4. Combinatorial counting with modular inverse
5. Dynamic programming merge operations on subtrees
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define F first
#define S second
#define all(x) x.begin(), x.end()
#define pb push_back
#define FIO                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 5e5 + 7, lg = 19, mod = 998244353;
inline int madd(int x, int y) { return x + y < mod ? x + y : x + y - mod; }
inline int mmul(int x, int y) { return (ll)x * y % mod; }
int fac[N], rfac[N];
int pw(int x, ll y) {
  int res = 1, pot = x;
  while (y) {
    if (y % 2)
      res = mmul(res, pot);
    pot = mmul(pot, pot);
    y /= 2;
  }
  return res;
}
int C(int x, int y) {
  return x < 0 || y < 0 || x < y ? 0 : mmul(fac[x], mmul(rfac[y], rfac[x - y]));
}
int n;
int a[N];
vector<int> adj[N];
pii c[N];
int fen[N];
vector<int> td, his;
inline pii mer(pii x, pii y) {
  return {x.F + y.F, mmul(x.S, mmul(y.S, C(x.F + y.F, x.F)))};
}
void add(int x, int y) {
  for (x++; x < N; x += x & -x)
    fen[x] += y;
}
int gsum(int x) {
  int out = 0;
  for (x++; x; x -= x & -x)
    out += fen[x];
  return out;
}
int get(int x) {
  x++;
  int y = 0;
  for (int i = lg - 1; i >= 0; i--) {
    if ((y | (1 << i)) < N && x > fen[y | (1 << i)]) {
      y |= (1 << i);
      x -= fen[y];
    }
  }
  return y;
}
void upd(int x, pii y) {
  x = get(x);
  c[x] = mer(c[x], y);
  td.pb(x);
}
void spo(int xx) {
  int x = get(xx), y = get(xx + 1);
  add(y, -1);
  his.pb(y);
  c[x] = {c[x].F + c[y].F + 1, mmul(c[x].S, c[y].S)};
  c[y] = {0, 1};
  td.pb(x);
}
void clear() {
  for (int x : td)
    c[x] = {0, 1};
  td.clear();
  for (int x : his)
    add(x, 1);
  his.clear();
}
void dfs(int x) {
  vector<pair<int, pii>> v;
  for (int i = 1; i < adj[x].size(); i++) {
    int y = adj[x][i];
    dfs(y);
    for (int z : td)
      if (c[z].F || c[z].S != 1)
        v.pb({gsum(z) - 1, c[z]}), c[z] = {0, 1};
    clear();
  }
  if (!adj[x].empty()) {
    int y = adj[x][0];
    dfs(y);
    for (auto it : v)
      upd(it.F, it.S);
  }
  spo(a[x]);
}
void task() {
  cin >> n;
  for (int i = 0; i < n; i++)
    adj[i].clear();
  vector<int> pa(n), siz(n, 1);
  for (int i = 1; i < n; i++)
    cin >> pa[i], adj[--pa[i]].pb(i);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = n - 1; i; i--)
    siz[pa[i]] += siz[i];
  for (int i = 0; i < n; i++) {
    for (int j = (int)adj[i].size() - 2; j >= 0; j--) {
      if (siz[adj[i][j]] < siz[adj[i][j + 1]])
        swap(adj[i][j], adj[i][j + 1]);
    }
  }
  dfs(0);
  cout << c[get(0)].S << "\n";
  clear();
}
int main() {
  FIO;
  fac[0] = 1;
  for (int i = 1; i < N; i++)
    fac[i] = mmul(fac[i - 1], i);
  rfac[N - 1] = pw(fac[N - 1], mod - 2);
  for (int i = N - 1; i; i--)
    rfac[i - 1] = mmul(rfac[i], i);
  for (int i = 0; i < N - 1; i++)
    add(i, 1);
  for (int i = 0; i < N - 1; i++)
    c[i] = {0, 1};
  int tt;
  cin >> tt;
  while (tt--)
    task();
  return 0;
}


// https://github.com/VaHiX/CodeForces/