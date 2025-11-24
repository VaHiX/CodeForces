// Problem: CF 1796 E - Colored Subgraphs
// https://codeforces.com/contest/1796/problem/E

/*
Purpose: This code solves the problem of finding the maximum possible cost of a tree
         when coloring vertices such that each color class forms a connected subgraph
         and all vertices in a color class have distinct distances from the root.
         The cost is defined as the minimum number of vertices assigned to any color.

Algorithms/Techniques:
- Tree DFS traversal
- Dynamic Programming on trees
- Preprocessing and postprocessing for distance calculations
- Optimization to find the maximum cost among all possible root choices

Time Complexity: O(n) per testcase, where n is the number of vertices.
Space Complexity: O(n) for storing adjacency list and auxiliary arrays.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
int INF = 300000;
int n;
int len[200010][3]; // Stores top 3 distances from each node to leaves
int pre[200010], suf[200010]; // Pre and suffix arrays for path optimization
int backw[200010][2]; // Backward distance tracking
int res[200010]; // Final result array
vector<int> graph[200010]; // Adjacency list representation of the tree

// Initialize the graph for each test case
void init() {
  for (int i = 1; i <= n; i++) {
    graph[i].clear();
  }
}

// DFS to compute top 3 distances from each node to leaves
void dfs(int pos, int parent) {
  // If node is a leaf (except for root)
  if (graph[pos].size() == 1 && parent != -1) {
    len[pos][0] = 0;
    for (int i = 1; i <= 2; i++)
      len[pos][i] = INF;
    return;
  }
  int tlen[4] = {INF, INF, INF, INF}; // Temporary array to store top 3 distances
  for (auto x : graph[pos]) {
    if (x == parent) continue; // Skip parent to avoid going back
    dfs(x, pos); // Recursively process children
    
    // Insert new distance into sorted array
    for (int i = 0; i <= 2; i++) {
      if (len[x][0] + 1 < tlen[i]) {
        for (int j = 2; j >= i; j--) {
          tlen[j + 1] = tlen[j];
        }
        tlen[i] = len[x][0] + 1;
        break;
      }
    }
  }
  for (int i = 0; i <= 2; i++) {
    len[pos][i] = tlen[i];
  }
}

// DFS to compute backward distances for path optimization
void backwdfs(int pos, int parent) {
  int zptr = 0, optr = 1; // Pointers to handle special cases for backward distances
  if (len[pos][0] + 1 == len[parent][0]) {
    zptr = 1;
    optr = 2;
  } else if (len[pos][0] + 1 == len[parent][1]) {
    optr = 2;
  }
  if (parent == 1) { // If current node is direct child of root
    backw[pos][0] = len[parent][zptr];
    backw[pos][1] = len[parent][optr];
    if (backw[pos][0] == INF) {
      backw[pos][0] = 0;
    }
  } else if (len[parent][zptr] == INF) { // If no valid parent distance
    backw[pos][0] = backw[parent][0] + 1;
    backw[pos][1] = INF;
  } else {
    // Determine whether parent contribution or direct path gives better result
    if (len[parent][zptr] < backw[parent][0] + 1) {
      backw[pos][0] = len[parent][zptr];
      backw[pos][1] = min(backw[parent][0] + 1, len[parent][optr]);
    } else {
      backw[pos][0] = backw[parent][0] + 1;
      backw[pos][1] = min(len[parent][zptr], len[parent][optr]);
    }
  }
  for (auto x : graph[pos]) {
    if (x == parent) continue;
    backwdfs(x, pos);
  }
}

// Preprocessing to calculate prefix values
void predfs(int pos, int parent, int &preval) {
  for (auto x : graph[pos]) {
    if (x == parent) continue;
    predfs(x, pos, preval); // Process children first
  }
  pre[pos] = len[pos][1]; // Get second smallest distance
  pre[pos] = min(pre[pos], preval); // Min with previous value
  preval = pre[pos]; // Update prevalence
}

// Suffix processing to calculate suffix values
void sufdfs(int pos, int parent, int &preval) {
  for (int i = graph[pos].size() - 1; i >= 0; i--) {
    int x = graph[pos][i];
    if (x == parent) continue;
    sufdfs(x, pos, preval); // Process children in reverse order
  }
  suf[pos] = len[pos][1]; // Get second smallest distance
  suf[pos] = min(suf[pos], preval); // Min with previous value
  preval = suf[pos]; // Update prevalence
}

// Final DFS to compute the result for each node
void ansdfs(int pos, int parent, int pval) {
  pval = min(pval, backw[pos][1]); // Min with backward second best distance
  res[pos] = min(pval, min(pre[pos], suf[pos])); // Take minimum of all three
  
  // Special handling for leaf nodes
  if (graph[pos].size() == 1)
    res[pos] = min(res[pos], backw[pos][0] + 2);
  else if (len[pos][0] > backw[pos][0] + 1) // If there's a better path than direct
    res[pos] = min(res[pos], min(len[pos][0], backw[pos][0] + 2));
  else
    res[pos] = min(res[pos], min(len[pos][0] + 1, backw[pos][0] + 1));
  
  for (auto x : graph[pos]) {
    if (x == parent) continue;
    ansdfs(x, pos, pval); // Recurse to children
  }
}

// Main solving function
void solve() {
  init(); // Clear graph
  scanf("%d", &n); // Read number of nodes
  INF = n; // Update INF to n
  for (int i = 1; i < n; i++) { // Read edges
    int u, v;
    scanf("%d %d", &u, &v);
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  dfs(1, -1); // Start DFS from root node 1
  
  backw[1][0] = 0;
  backw[1][1] = INF;
  for (auto x : graph[1]) { // Initialize backward distances for children of root
    backwdfs(x, 1);
  }
  
  int gval = INF;
  predfs(1, -1, gval); // Compute prefix distances
  gval = INF;
  sufdfs(1, -1, gval); // Compute suffix distances
  
  ansdfs(1, -1, INF); // Compute final results
  
  res[1] = min(min(suf[1], pre[1]), len[1][0] + 1); // Adjust for root node
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, res[i]); // Maximum among all vertices
  }
  printf("%d\n", ans);
  return;
}

// Entry point of the program
int main() {
  int t = 1;
  scanf("%d", &t); // Read number of test cases
  for (; t > 0; t--) {
    solve(); // Solve each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/