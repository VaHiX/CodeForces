// Problem: CF 1877 G - Ball-Stackable
// https://codeforces.com/contest/1877/problem/G

/*
Algorithm: 
- This problem involves directing edges in a graph and assigning colors to edges such that all stackable walks are also ball-stackable.
- The core idea is to perform a DFS traversal of the tree and assign directions and colors to edges such that:
  - When going forward (in the direction of the edge), a new ball of edge color is pushed onto the stack.
  - When going backward (against direction), a ball of the same color as the edge must be popped.
- The approach is to:
  1. Build the graph with special representations for directed/undirected edges.
  2. Perform DFS to determine a spanning tree and track distances (used for root selection).
  3. Choose the vertex with minimum distance as root for second DFS.
  4. In the second DFS, process edges:
     - For undirected edges: if going forward, assign a new color, push it; if going backward, pop the same color.
     - For directed edges, just use the current color from stack.
- Time Complexity: O(n) - linear DFS traversal.
- Space Complexity: O(n) - for storing graph and auxiliary data structures.

Techniques Used:
- Depth-First Search (DFS)
- Tree Traversal
- Stack-based simulation of ball operations
- Graph Representation and Edge Direction Handling
*/

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <utility>
#include <vector>

#define int long long
#define fast                                                                   \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0)
#define pb push_back
#define ft first
#define sd second
#define vec vector
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
using namespace std;
const int mod = 1e9 + 7;
const int inf = 1e12;
const int N = 1e5 + 52;
const int SB = 450;
vector<pair<int, int>> g[N]; // adjacency list with special representation for edge types
vector<int> dist(N), used(N); // dist to track distance from root, used to track visited nodes
int cnt; // count of colors used
map<pair<int, int>, int> mp; // map to store edge directions and colors

// First DFS to find distances and mark nodes
void dfs1(int x, int kol) {
  used[x] = 1;
  dist[x] = kol;
  for (auto to : g[x]) {
    if (to.sd == 10) { // undirected edge in original graph
      if (!used[to.ft])
        dfs1(to.ft, kol); // recurse with same level
    } else { // directed edge
      if (to.sd == -1) { // edge points to parent
        if (!used[to.ft])
          dfs1(to.ft, kol - 1); // decrease level
      } else { // edge points to child
        if (!used[to.ft])
          dfs1(to.ft, kol + 1); // increase level
      }
    }
  }
}

stack<int> st; // stack for ball tracking

// Second DFS to assign directions and colors to edges
void dfs2(int x) {
  used[x] = 1;
  for (auto to : g[x]) {
    if (to.sd == 10) { // undirected edge
      if (!used[to.ft]) {
        // Assign a new color and push it onto stack
        mp[{x, to.ft}] = cnt;
        st.push(cnt);
        cnt++;
        dfs2(to.ft);
        st.pop(); // pop after recursion
      }
    } else { // directed edge
      if (to.sd == -1) { // going backward, needs to pop matching color
        if (!used[to.ft]) {
          // Assign color from stack top (should match edge's color)
          mp[{to.ft, x}] = st.top();
          int gg = st.top();
          st.pop(); // remove the color from stack
          dfs2(to.ft);
          st.push(gg); // push back to stack after recursion
        }
      } else { // going forward, push a new color
        if (!used[to.ft]) {
          mp[{x, to.ft}] = cnt;
          st.push(cnt);
          cnt++;
          dfs2(to.ft);
          st.pop(); // pop after recursion
        }
      }
    }
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v, type;
    cin >> u >> v >> type;
    if (type == 0) { // undirected edge
      g[u].pb({v, 10}); // flag for undirected edge
      g[v].pb({u, 10});
    } else { // directed edge
      g[u].pb({v, 1}); // flag for forward directed edge
      g[v].pb({u, -1}); // flag for reverse directed edge
    }
  }
  
  dfs1(1, 0); // build spanning tree by first DFS
  
  int mn = 1;
  used[mn] = 0;
  for (int i = 1; i <= n; i++) {
    if (dist[mn] > dist[i])
      mn = i; // find the vertex that has smallest distance to root (min depth)
    used[i] = 0;
  }
  
  cnt = 1; // start color at 1
  dfs2(mn); // DFS from root node to assign directions and colors
  
  int mx = 0;
  for (auto xz : mp)
    mx = max(mx, xz.sd); // find maximum color used
  
  cout << mx << "\n";
  for (auto xz : mp)
    cout << xz.ft.ft << " " << xz.ft.sd << " " << xz.sd << "\n"; // output results
}

int32_t main() {
  fast;
  int tt = 1;
  while (tt--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/