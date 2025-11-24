// Problem: CF 1777 E - Edge Reverse
// https://codeforces.com/contest/1777/problem/E

/*
 * Problem: E. Edge Reverse
 * Algorithm: Strongly Connected Components (Tarjan's Algorithm) + Binary Search
 * 
 * Approach:
 * 1. Use binary search on edge weights to find the minimum cost to make graph
 *    fully reachable from one node.
 * 2. For each mid value in binary search, construct a graph:
 *    - Keep edges with weight <= mid as bidirectional (can be reversed or not)
 *    - Keep edges with weight > mid as unidirectional (must be reversed if needed)
 * 3. Run Tarjan to find SCCs (Strongly Connected Components)
 * 4. Build a condensed DAG (Directed Acyclic Graph) from SCCs
 * 5. Check if there is exactly one node with in-degree 0 (i.e., a source)
 *    - If yes, it's possible to reach all nodes from this source
 *    - If no such unique source, return -1
 * 
 * Time Complexity: O((n + m) * log(max_weight))
 * Space Complexity: O(n + m)
 */

#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>

using namespace std;
const int MAXN = 2e5 + 10;
const int N = 2e5;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const int mod = 1e9 + 7;
int n, m;
vector<int> vec[MAXN];
void add_edge(int x, int y) { vec[x].push_back(y); } // Add an edge from x to y
int u[MAXN], v[MAXN], w[MAXN];
int dep = 0, cnt = 0;
int dfn[MAXN], low[MAXN];
int c[MAXN], siz[MAXN];
bool vis[MAXN];
stack<int> st;
void Tarjan(int x) {
  dep++;
  dfn[x] = dep;
  low[x] = dep;
  vis[x] = true;
  st.push(x);
  for (int i = 0; i < vec[x].size(); i++) {
    int to = vec[x][i];
    if (!dfn[to]) {
      Tarjan(to);
      low[x] = min(low[x], low[to]);
    } else if (vis[to]) {
      low[x] = min(low[x], dfn[to]);
    }
  }
  if (low[x] == dfn[x]) {
    cnt++;
    while (st.top() != x) {
      int now = st.top();
      st.pop();
      vis[now] = false;
      c[now] = cnt;
      siz[cnt]++;
    }
    st.pop();
    vis[x] = false;
    c[x] = cnt;
    siz[cnt]++;
  }
}
int in[MAXN], out[MAXN];
void addedge(int x, int y) {
  in[y]++;
  out[x]++;
}
void tarjan() {
  while (!st.empty()) {
    st.pop();
  }
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
      Tarjan(i);
    }
  }
}
bool check(int x) {
  dep = 0;
  cnt = 0;
  for (int i = 1; i <= n; i++) {
    vec[i].clear(); // Reset the adjacency list
    dfn[i] = 0;
    low[i] = 0;
    vis[i] = false;
    c[i] = 0;
    siz[i] = 0;
    in[i] = 0;
    out[i] = 0;
  }
  for (int i = 1; i <= m; i++) {
    if (w[i] > x) {
      add_edge(u[i], v[i]); // Keep edges with weight > x as unidirectional
    } else {
      add_edge(u[i], v[i]); // Keep edges with weight <= x as bidirectional
      add_edge(v[i], u[i]);
    }
  }
  tarjan(); // Find strongly connected components
  for (int i = 1; i <= m; i++) {
    if (c[u[i]] != c[v[i]]) { // If u and v are in different SCCs
      if (w[i] > x) {
        addedge(c[u[i]], c[v[i]]); // Create edge in condensed graph if weight > x
      } else {
        addedge(c[u[i]], c[v[i]]); // Add bidirectional edge in condensed graph if weight <= x
        addedge(c[v[i]], c[u[i]]);
      }
    }
  }
  bool flag = false;
  for (int i = 1; i <= cnt; i++) {
    if (!in[i]) { // Count nodes with in-degree = 0
      if (flag) {
        return false; // Multiple sources -> not valid
      }
      flag = true;
    }
  }
  return flag; // True if exactly one source node exists
}
vector<int> W;
void solve() {
  W.clear();
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", &u[i], &v[i], &w[i]);
    W.push_back(w[i]);
  }
  sort(W.begin(), W.end());
  if (!check(W.back())) { // If even the maximum weight edge cannot make it valid
    puts("-1");
    return;
  }
  if (check(0)) { // If no edge reversal is needed
    puts("0");
    return;
  }
  int l = 1, r = m, mid;
  while (l < r) {
    mid = (l + r) / 2;
    if (check(W[mid - 1])) { // Check if the solution is valid with mid-1 as max edge weight
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  printf("%d\n", W[l - 1]);
}
signed main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/