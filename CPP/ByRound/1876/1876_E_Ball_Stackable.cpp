// Problem: CF 1876 E - Ball-Stackable
// https://codeforces.com/contest/1876/problem/E

/*
Purpose: This code solves the "Ball-Stackable" problem by determining how to direct undirected edges and assign colors to edges such that all stackable walks are also ball-stackable. It uses a tree traversal approach with DFS to determine the optimal edge orientations and color assignments.

Algorithms/Techniques:
- Tree DFS traversal
- Euler tour technique for edge orientation and coloring
- Depth-first search for computing in-degrees and out-degrees
- Stack simulation for tracking ball operations

Time Complexity: O(n), where n is the number of vertices in the tree
Space Complexity: O(n), for storing the adjacency list and auxiliary arrays

*/
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
using LL = long long;
struct Edge {
  int b, c;
};
struct FEdge {
  int a, b, c;
};
const int MAXN = 100010;
vector<Edge> x[MAXN];
int in[MAXN];
int m;
vector<FEdge> ans;
void Dfs1(int a, int fa) {
  // First DFS to compute in-degree values for each node
  for (auto [b, c] : x[a]) {
    if (b == fa)
      continue;
    Dfs1(b, a);
    in[a] += in[b];
    if (c == -1)
      ++in[a];
  }
}
void Dfs2(int a, int fa, int upin) {
  // Second DFS to adjust in-degrees based on the direction of edges
  in[a] += upin;
  for (auto [b, c] : x[a]) {
    if (b == fa)
      continue;
    Dfs2(b, a, in[a] - in[b] + c);
  }
}
void Solve(int a, int fa, stack<int> &st) {
  // Recursive function to traverse the tree and assign directions and colors
  for (auto [b, c] : x[a]) {
    if (b == fa)
      continue;
    if (c != -1) {
      // If edge is directed away from current node, push new color to stack
      st.push(++m);
      ans.push_back({a, b, m});
      Solve(b, a, st);
      st.pop();
    } else {
      // If edge is directed towards current node, pop color from stack
      int pre = st.top();
      ans.push_back({b, a, pre});
      st.pop();
      Solve(b, a, st);
      st.push(pre);
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  // Read the input edges and build adjacency list
  for (int i = 1; i < n; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    --a;
    --b;
    if (c == 1) {
      x[a].push_back({b, 1});
      x[b].push_back({a, -1});
    } else {
      x[a].push_back({b, 0});
      x[b].push_back({a, 0});
    }
  }
  Dfs1(0, -1);
  Dfs2(0, -1, 0);
  int s = 0;
  // Find the node with minimum in-degree
  for (int i = 0; i < n; ++i) {
    if (in[i] < in[s])
      s = i;
  }
  stack<int> st;
  Solve(s, -1, st);
  cout << m << "\n";
  for (auto [a, b, c] : ans) {
    cout << a + 1 << " " << b + 1 << " " << c << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/