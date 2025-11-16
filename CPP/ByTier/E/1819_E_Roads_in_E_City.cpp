// Problem: CF 1819 E - Roads in E City
// https://codeforces.com/contest/1819/problem/E

/*
Algorithm: 
This problem involves identifying which roads in a graph are repaired by using a series of queries.
The approach uses:
1. First, for each road, we temporarily block it and check if the graph remains connected using a query.
   If it's not connected, then the road must be repaired.
2. Then we build a spanning tree using the repaired roads.
3. Finally, for each non-repaired edge, we try to verify if it's actually needed by temporarily blocking the edge,
   and checking if we can still connect the endpoints via the spanning tree. If not, then the edge is repaired.

Time Complexity: O(m^2 * log(n)) where m is the number of edges and n is the number of vertices.
Space Complexity: O(n + m) for storing graph information, spanning tree, etc.

*/
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

// Structure to store edge information
struct Node {
  ll u, v;
} a[200100];

// Structure to store adjacent nodes and their edge index
struct node {
  ll to;
  ll idx;
} st;

ll T, n, m; // T: number of test cases, n: vertices, m: edges
ll ans[200100]; // Stores answer: 1 if road is repaired, 0 otherwise
ll g[200100]; // Marks which edges are not yet determined as repaired
ll p[200100]; // Parent array for spanning tree
ll dep[200100]; // Depth array for spanning tree
vector<node> h[200100]; // Adjacency list for graph

// Query function: send ? y to jury and return result
inline bool qy(ll x) {
  printf("? %lld\n", x);
  fflush(stdout);
  ll res;
  scanf("%lld", &res);
  return res;
}

// Block a road
inline void del(ll x) {
  printf("- %lld\n", x);
  fflush(stdout);
  return;
}

// Unblock a road
inline void add(ll x) {
  printf("+ %lld\n", x);
  fflush(stdout);
  return;
}

// Check whether the road i is in the spanning tree
inline bool ok(ll x) {
  ll u = a[x].u;
  ll v = a[x].v;
  bool b = 0;
  for (ll i = 20; i >= 0; i--) {
    b |= (!qy(u));
    b |= (!qy(v));
    if (b) {
      break;
    }
  }
  return b;
}

// DFS to build the spanning tree
void dfs(ll u, ll fa) {
  for (ll i = 0; i < h[u].size(); i++) {
    st = h[u][i];
    ll v = st.to;
    ll xx = st.idx;
    if (v == fa) {
      continue;
    }
    dep[v] = dep[u] + 1;
    p[v] = xx;
    dfs(v, u);
  }
  return;
}

int main() {
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= m; i++) {
      scanf("%lld%lld", &a[i].u, &a[i].v);
    }
    for (ll i = 1; i <= m; i++) {
      del(i); // Temporarily block road i
      if (ok(i)) { // If after blocking, the graph is not connected
        st.to = a[i].v;
        st.idx = i;
        h[a[i].u].push_back(st);
        st.to = a[i].u;
        h[a[i].v].push_back(st);
        add(i); // Reunblock road i
        ans[i] = 1; // Mark road i as repaired
      } else {
        g[i] = 1; // Mark road i as not repaired
      }
    }
    
    dfs(1, 0); // Build spanning tree from node 1
    
    for (ll i = 1; i <= m; i++) {
      if (g[i]) { // If not determined yet
        ll u = a[i].u;
        ll v = a[i].v;
        if (dep[u] < dep[v]) {
          swap(u, v); // Ensure u is deeper than v
        }
        del(p[u]); // Temporarily block the spanning tree edge from u
        add(i); // Unblock current edge i
        if (!ok(i)) { // Check if still connected
          ans[i] = 1; // Edge i is repaired
        }
        del(i); // Temporarily block edge i
        add(p[u]); // Reunblock the spanning tree edge
      }
    }
    
    // Output answer
    printf("!");
    for (ll i = 1; i <= m; i++) {
      printf(" %lld", ans[i]);
    }
    printf("\n");
    fflush(stdout);
    
    // Reset data structures for next test case
    for (ll i = 1; i <= n; i++) {
      h[i].clear();
    }
    for (ll i = 1; i <= m; i++) {
      g[i] = ans[i] = 0;
    }
    scanf("%lld", &n);
    if (!n) {
      return 0;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/