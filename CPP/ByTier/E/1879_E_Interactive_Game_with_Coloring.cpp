// Problem: CF 1879 E - Interactive Game with Coloring
// https://codeforces.com/contest/1879/problem/E

/*
Purpose: Solve an interactive tree coloring problem where edges are colored to ensure winning strategy
         for moving a chip from any vertex to root in exactly d moves, where d is the distance.

Algorithms/Techniques:
- Tree traversal (DFS)
- Depth-based coloring strategy
- Adaptive interactive problem solving with dynamic decisions based on vertex information
- Special handling for different tree structures based on maximum depth

Time Complexity: O(n) where n is the number of vertices - DFS traversal, color assignment, and interaction loop
Space Complexity: O(n) for storing adjacency list, depth array, and color array

*/

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

#define fori(i, ini, lim) for (int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for (int i = int(ini); i >= int(lim); i--)
#define debug(x) cout << #x << " = " << x << endl
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
const int MAX = 105;
vector<int> adj[MAX];
int p[MAX], c[MAX], depth[MAX];
int n, k = -1;

// Output the edge coloring
void f_output() {
  cout << k << endl;
  fori(i, 2, n + 1) {
    if (i > 2)
      cout << " ";
    cout << c[i];
  }
  cout << endl;
}

// Depth-first search to compute depth of each vertex
void dfs(int u) {
  if (u == 1)
    depth[u] = 1;
  else
    depth[u] = depth[p[u]] + 1;
  for (int v : adj[u]) {
    dfs(v);
  }
}

// Read integer from input
int read_int() {
  int x;
  cin >> x;
  return x;
}

// Output integer to output
void output_int(int x) { cout << x << endl; }

// Read k integers representing edge counts for each color at current vertex
vector<int> read_k() {
  vector<int> v(k + 1);
  fori(i, 1, k + 1) { cin >> v[i]; }
  return v;
}

// Helper to find special vertices (leaves) through DFS
void sp_bk(int u, vector<int> &s) {
  if (adj[u].size() == 1)
    s.push_back(u);
  for (int v : adj[u])
    sp_bk(v, s);
}

// Find special vertices (leaves) in subtree rooted at u
vector<int> find_specials(int u) {
  vector<int> s;
  sp_bk(u, s);
  return s;
}

// Apply alternating color to subtree rooted at u (for 2-color case)
void apply_color(int u, int cur_color) {
  c[u] = cur_color;
  for (int v : adj[u]) {
    apply_color(v, cur_color == 1 ? 2 : 1);
  }
}

// Main solution logic
void solve() {
  cin >> n;
  fori(i, 2, n + 1) {
    cin >> p[i];
    adj[p[i]].push_back(i);
  }
  dfs(1);
  int max_depth = 0;
  fori(i, 1, n + 1) max_depth = max(max_depth, depth[i]);
  
  // If max depth is 2, all edges can be same color
  if (max_depth == 2) {
    k = 1;
    fori(i, 2, n + 1) c[i] = 1;
  } else {
    k = 2;
    // Check if we need 3 colors based on parity of depths
    for (int u : adj[1]) {
      vector<int> specials = find_specials(u);
      set<int> parity;
      for (int s : specials)
        parity.insert(depth[s] & 1);
      if (parity.size() > 1)
        k = 3;
    }
    // Apply coloring strategy based on k
    if (k == 2) {
      for (int u : adj[1]) {
        vector<int> specials = find_specials(u);
        int initial_color = 1;
        if (!specials.empty() and (depth[specials[0]] & 1) == 1)  // If the leaf has odd depth
          initial_color = 2;
        apply_color(u, initial_color);
      }
    } else {
      // For 3 colors, use depth modulo 3 to assign colors
      fori(i, 2, n + 1) { c[i] = (depth[i] % 3) + 1; }
    }
  }
  f_output();
  while (1) {
    int type = read_int();
    if (type == -1 or type == 1)
      break;
    assert(type == 0);
    vector<int> move = read_k();
    
    // Select move based on information received
    vector<int> ones;
    fori(i, 1, k + 1) {
      if (move[i] == 1)
        ones.push_back(i);
    }
    // If only one edge of a color is incident, use that color
    if (ones.size() == 1) {
      output_int(ones[0]);
    } else {
      // Decision making for 2-color vs 3-color cases
      if (k == 2) {
        output_int(1);  // Prefer color 1 for 2-color case
      } else {
        // Prefer color that has exactly one incident edge (to move towards root efficiently)
        if (move[1] == 1 and move[3] == 1)
          output_int(3);
        if (move[1] == 1 and move[2] == 1)
          output_int(1);
        if (move[2] == 1 and move[3] == 1)
          output_int(2);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/