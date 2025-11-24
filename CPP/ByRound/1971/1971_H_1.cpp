// Problem: CF 1971 H - ±1
// https://codeforces.com/contest/1971/problem/H

/*
 * Problem: Determine if Alice can choose values for array a such that after Bob sorts each column,
 * the middle row of the resulting grid contains only 1s.
 * 
 * Algorithm: This is a 2-SAT problem. For each column, we determine the constraints on the 
 * values of a_i based on how the sorting affects the middle element.
 * 
 * Key Insight:
 * For each column j, if the elements are a, b, c in the three rows, after sorting, we must 
 * ensure that the middle element (after sorting) is 1.
 * 
 * For example, if a, b, c = -a_i, a_j, a_k, then after substituting values, we need to ensure 
 * that when these are sorted, the middle value is 1.
 * 
 * To model this as 2-SAT:
 * - Each a_i corresponds to two variables: a_i (true) and -a_i (false)
 * - We add clauses to ensure that for each column, the possible assignments lead to middle element being 1
 * - We use Tarjan's algorithm to find SCCs and check if contradictions exist
 * 
 * Time Complexity: O(N + M) where N is the number of variables (2*n), M is number of clauses (3*n)
 * Space Complexity: O(N + M) for the graph storage and recursion stack
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <stack>
#include <utility>
#include <vector>

#define rep(i, n) for (int i = 0; i < (n); i++)
#define For(i, s, t) for (__typeof(s) i = (s); i <= (t); i++)
#define Rof(i, s, t) for (__typeof(t) i = (s); i >= (t); i--)
using namespace std;
typedef long long i64;
typedef pair<int, int> pii;
const int N = 1010, INF = 0x3f3f3f3f, mod = 1e9 + 7;
const i64 INFLL = 0x3f3f3f3f3f3f3f3fLL;
inline int read() {
  int x = 0, f = 0;
  char ch = getchar();
  while (!isdigit(ch))
    f |= (ch == 45), ch = getchar();
  while (isdigit(ch))
    x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return f ? -x : x;
}
int dfn[N], low[N], scc[N];
int dfn_cnt, scc_cnt;
stack<int> stk;
bool instk[N];
vector<int> adj[N];
void init(int n) {
  For(i, 1, n) {
    dfn[i] = low[i] = scc[i] = 0;
    instk[i] = false;
    adj[i].clear();
  }
  dfn_cnt = scc_cnt = 0;
  while (!stk.empty())
    stk.pop();
}
void tarjan(int u) {
  dfn[u] = low[u] = ++dfn_cnt;
  stk.push(u);
  instk[u] = true;
  for (auto v : adj[u]) {
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (instk[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++scc_cnt;
    int v;
    do {
      v = stk.top();
      stk.pop();
      scc[v] = scc_cnt;
      instk[v] = false;
    } while (v != u);
  }
}
int g[3][N];
void solve() {
  int n = read();
  init(2 * n);
  rep(i, 3) {
    rep(j, n) {
      g[i][j] = read();
      if (g[i][j] < 0)
        g[i][j] = -g[i][j] + n; // Convert negative values to index offset
    }
  }
  rep(j, n) {
    auto rev = [&](int x) { return x > n ? x - n : x + n; }; // Reverse variable mapping
    int a = g[0][j], b = g[1][j], c = g[2][j];
    // Add edges based on possible values that make middle element 1
    adj[rev(a)].push_back(b); 
    adj[rev(a)].push_back(c);
    adj[rev(b)].push_back(a);
    adj[rev(b)].push_back(c);
    adj[rev(c)].push_back(a);
    adj[rev(c)].push_back(b);
  }
  For(i, 1, 2 * n) {
    if (!dfn[i])
      tarjan(i);
  }
  // Check if any variable and its negation are in the same SCC
  for (int i = 1; i <= n; i++) {
    if (scc[i] == scc[i + n]) {
      puts("NO");
      return;
    }
  }
  puts("YES");
}
int main() {
  int T = read();
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/