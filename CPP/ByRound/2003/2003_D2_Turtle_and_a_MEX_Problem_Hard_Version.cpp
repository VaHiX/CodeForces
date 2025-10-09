// Problem: CF 2003 D2 - Turtle and a MEX Problem (Hard Version)
// https://codeforces.com/contest/2003/problem/D2

/*
D2. Turtle and a MEX Problem (Hard Version)
Algorithms/Techniques: Graph construction, Dynamic Programming, MEX computation

Time Complexity: O(sum of l_i) per test case
Space Complexity: O(N) where N = 2e5 + 5

The problem involves finding the maximum value of x after applying mex operations on sequences,
and then computing the sum of f(i) for i from 0 to m, where f(k) is the result of starting with k.
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 2e5 + 5;
bool vis[N]; // Visited array to track which numbers are present in current sequence
vector<int> g[N]; // Graph to store transitions between states
int T, n, m, dp[N]; // dp[i] stores the maximum reachable value from state i

void Solve() {
  cin >> n >> m;
  int V = 0; // Tracks the maximum value seen so far
  long long ans = 1ll * m * (m + 1) / 2; // Initial contribution of sum(0..m)
  
  for (int i = 1, l; i <= n; i++) {
    cin >> l;
    // Reset visited array for this sequence
    for (int j = 0; j <= l + 1; j++)
      vis[j] = 0;
    
    // Mark all values in the current sequence as present
    for (int j = 1, x; j <= l; j++) {
      cin >> x;
      if (x <= l + 1)
        vis[x] = 1;
    }
    
    int u = 0;
    // Find the first missing number in [0...l]
    for (int j = 0; j <= l; j++) {
      u = j;
      if (!vis[j])
        break;
    }
    vis[u] = 1; // Mark it as visited to avoid reuse
    
    int v = 0;
    // Find the first missing number in [0...l+1]
    for (int j = 0; j <= l + 1; j++) {
      v = j;
      if (!vis[j])
        break;
    }
    
    g[u].push_back(v); // Add edge from u to v
    V = max(V, l + 1); // Update maximum value seen
  }
  
  // Initialize dp array: dp[i] = i initially (no transitions)
  for (int i = 0; i <= V; i++) {
    dp[i] = i;
  }
  
  int maxx = 0;
  // Process from back to front to compute max reachable values
  for (int i = V; i >= 0; i--) {
    for (int v : g[i]) { // For each neighbor v of i
      dp[i] = max(dp[i], dp[v]); // Update with the maximum reachable value
    }
    if (g[i].size() > 1)
      maxx = max(maxx, dp[i]);
    if (g[i].size())
      maxx = max(maxx, i);
    g[i].clear(); // Clear edges after processing
  }
  
  // Add contribution of f(i) for each i from 0 to min(V,m)
  for (int i = 0; i <= min(V, m); i++) {
    ans += max(maxx, dp[i]) - i;
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--; Solve()) {
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/