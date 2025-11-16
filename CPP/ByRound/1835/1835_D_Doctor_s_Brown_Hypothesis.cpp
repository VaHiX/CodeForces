// Problem: CF 1835 D - Doctor's Brown Hypothesis
// https://codeforces.com/contest/1835/problem/D

/* 
 * Purpose: Solve the problem of finding valid ship placements for rebels to confuse imperial forces.
 *          The task involves detecting cycles in a directed graph and determining if paths of exactly k hours exist
 *          between pairs of nodes (ships) or if a single node can complete a cycle back to itself.
 *          
 * Algorithm:
 *   1. Find Strongly Connected Components (SCCs) using Tarjan's algorithm.
 *   2. For each SCC with more than one node:
 *      - Compute the cycle length g using DFS to find GCD of all cycle lengths.
 *      - Count how many nodes exist at each modulo of g in the SCC.
 *      - If k is a valid time for a cycle completion, count valid pairs or single nodes.
 *      
 * Time Complexity: O(n + m + g), where g is the gcd of cycle lengths in each SCC.
 * Space Complexity: O(n + m), for storing graph, SCC data, and auxiliary arrays.
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;
int n, m;
long long k;
vector<int> ed[100005]; // Adjacency list representation of the graph
int dfn[100005], low[100005], Insta[100005], cnt; // Tarjan's algorithm variables
stack<int> st;
int scnt, col[100005]; // Number of SCCs, and node to SCC mapping
vector<int> scc[100005]; // SCCs stored as lists of nodes

// Tarjan's algorithm to find all strongly connected components
void tarjan(int x) {
  dfn[x] = low[x] = ++cnt;
  st.push(x);
  Insta[x] = true;
  for (auto &p : ed[x]) {
    if (!dfn[p]) {
      tarjan(p);
      low[x] = min(low[x], low[p]);
    } else if (Insta[p]) {
      low[x] = min(low[x], dfn[p]);
    }
  }
  if (low[x] == dfn[x]) {
    scnt++;
    while (st.top() != x) {
      col[st.top()] = scnt;
      scc[scnt].push_back(st.top());
      Insta[st.top()] = false;
      st.pop();
    }
    scc[scnt].push_back(x);
    col[x] = scnt;
    Insta[x] = false;
    st.pop();
  }
}

int g; // GCD of all cycle lengths in current SCC
bool vis[100005]; // Visited array for DFS
int cntx[100005], dep[100005]; // cntx tracks count of nodes per modulo, dep tracks depth for cycle length calculation

// DFS to compute cycle lengths in SCC
void dfs(int x, int fa) {
  vis[x] = true;
  dep[x] = dep[fa] + 1;
  for (auto &p : ed[x]) {
    if (col[p] != col[x]) continue; // Skip edges to different SCCs
    if (vis[p]) {
      g = __gcd(g, abs(dep[x] - dep[p] + 1)); // Update GCD of cycle lengths
    } else {
      dfs(p, x);
    }
  }
}

int main() {
  scanf("%d%d%lld", &n, &m, &k);
  for (int i = 1; i <= m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    ed[x].push_back(y); // Build directed graph
  }
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) tarjan(i); // Find all SCCs
  }
  long long ans = 0;
  for (int i = 1; i <= scnt; i++) {
    if (scc[i].size() == 1) continue; // Skip trivial SCCs (single node)
    g = 0;
    dfs(scc[i][0], 0); // Compute cycle lengths in SCC
    for (int j = 0; j < g; j++) cntx[j] = 0; // Reset counter for modulo classes
    for (auto &p : scc[i]) {
      cntx[dep[p] % g]++; // Count nodes by their modulo
    }
    if (g % 2 == 0 && k % g == g / 2) { // Special case for pairs
      for (int j = 0; j < g / 2; j++)
        ans += (long long)cntx[j] * cntx[j + g / 2]; // Count valid pair combinations
    }
    if (k % g == 0) { // Valid for single nodes too
      for (int j = 0; j < g; j++)
        ans += (long long)cntx[j] * (cntx[j] - 1) / 2 + cntx[j]; // Count combinations of pairs + single nodes
    }
  }
  printf("%lld\n", ans);
}


// https://github.com/VaHiX/CodeForces/