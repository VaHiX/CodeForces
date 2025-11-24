// Problem: CF 522 A - Reposts
// https://codeforces.com/contest/522/problem/A

/*
Algorithm: Depth-First Search (DFS) on a Directed Graph
Purpose: To find the maximum depth of repost chain starting from "Polycarp"
Time Complexity: O(V + E) where V is the number of unique users and E is the number of reposts
Space Complexity: O(V + E) for storing adjacency list and visited map

The solution builds a directed graph where each edge represents a repost from user A to user B.
Since the reposts form a chain, we perform a DFS from "Polycarp" to find the longest path,
which corresponds to the maximum repost chain length.
*/

#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
using namespace std;
int d = 0;
map<string, vector<string>> adj; // Adjacency list to represent repost relationships
map<string, bool> vis; // Visited map to track visited nodes during DFS

// DFS function to compute the depth of the repost chain
int dfs(string s) {
  if (vis[s]) // If already visited, return 0 to avoid cycles
    return 0;
  int dist = 0;
  vis[s] = 1; // Mark current node as visited
  // Traverse all neighbors (users who reposted from current user)
  for (int i = 0; i < adj[s].size(); i++) {
    dist = max(dfs(adj[s][i]), dist); // Recursively visit neighbors and get max depth
  }
  return dist + 1; // Return depth plus 1 for current node
}

int main() {
  int i, j, k;
  int n, m;
  string s1, s2, r;
  cin >> n; // Read number of reposts
  for (i = 0; i < n; i++) {
    cin >> s1 >> r >> s2; // Read repost details: s1 reposted s2
    // Convert names to lowercase for case-insensitive comparison
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    // Build adjacency list: s2 -> s1 (s1 reposted s2)
    adj[s2].push_back(s1);
    // Also add reverse edge for correctness in graph traversal
    adj[s1].push_back(s2);
  }
  // Start DFS from "polycarp" to find maximum chain length
  cout << dfs("polycarp");
  return 0;
}


// https://github.com/VaHiX/CodeForces/