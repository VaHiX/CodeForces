// Problem: CF 1725 J - Journey
// https://codeforces.com/contest/1725/problem/J

/*
Purpose: Solve the problem of finding the minimum time to visit all cities in a tree-shaped country,
         with the ability to use a teleportation device once to move between any two cities.
         The journey must start and end at any city, visiting each city at least once.

Algorithms/Techniques: 
  - Tree Dynamic Programming (DP)
  - DFS traversal of the tree
  - State compression: For each node, we track the minimum cost to cover a certain number of cities with or without using the teleportation device.

Time Complexity: O(N)
Space Complexity: O(N)

State definition:
dp[u][i][j] = minimum time to cover i cities in subtree rooted at u, where j=1 means teleportation is used, j=0 means not used.

*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
int N;
vector<pair<int, int>> G[1 << 17]; // Adjacency list for tree (17 is enough for 1e5 nodes)
long long dp[1 << 17][5][2]; // dp[node][number_of_cities_covered][used_teleportation]

void dfs(int u, int p) {
  long long tmp[5][2]; // Temporary DP table for combining results from children
  // Initialize dp[u] to 0
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 2; j++)
      dp[u][i][j] = 0;
  
  // Iterate through all neighbors (children in tree)
  for (pair<int, int> e : G[u])
    if (e.first != p) {
      int v = e.first;
      int w = e.second;
      dfs(v, u); // Recurse on child
      
      // Reset tmp table
      for (int i = 0; i < 5; i++)
        for (int j = 0; j < 2; j++)
          tmp[i][j] = 1e18;
      
      // Combine results from current node and child
      for (int i = 0; i < 5; i++)
        for (int j = 0; i + j <= 4; j++) {
          int ni = i + j; // New number of cities covered (i from current + j from child)
          for (int k = 0; k < 2; k++)
            for (int l = 0; k + l <= 1; l++) {
              // Compute cost to connect current subtree (dp[u][i][k]) and child subtree (dp[v][j][l])
              long long now =
                  dp[u][i][k] + dp[v][j][l] + (j % 2 == 0 ? w + w : w);
              tmp[ni][k | l] = min(tmp[ni][k | l], now);
              // Special handling for case when teleportation is used once
              if ((k | l) == 0 && j == 2) {
                tmp[ni][1] = min(tmp[ni][1], now - w - w);
              }
            }
        }
      // Update dp[u] with combined results
      for (int i = 0; i < 5; i++)
        for (int j = 0; j < 2; j++)
          dp[u][i][j] = tmp[i][j];
    }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for (int i = 1; i < N; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--; // Convert to 0-based indexing
    G[u].push_back(make_pair(v, w));
    G[v].push_back(make_pair(u, w));
  }
  dfs(0, -1); // Start DFS from root node 0
  cout << dp[0][4][1] << endl; // Result: minimum time to cover all 4 cities (since N = 4) with teleportation used
}


// https://github.com/VaHiX/CodeForces/