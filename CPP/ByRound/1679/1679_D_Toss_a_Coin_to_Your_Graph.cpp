// Problem: CF 1679 D - Toss a Coin to Your Graph...
// https://codeforces.com/contest/1679/problem/D

/*
 * Problem: Masha wants to move a coin through a directed graph to minimize the maximum value
 *          written in her notebook after exactly k-1 operations.
 *          
 * Algorithm: Binary search on the answer combined with DFS to check if a certain maximum
 *            value allows completing k operations.
 *            
 * Time Complexity: O((n + m) * log(10^18)) where n is vertices, m is edges.
 * Space Complexity: O(n + m) for adjacency list and auxiliary arrays.
 * 
 * Techniques:
 * 1. Binary search over the maximum value (range from 1 to 10^18)
 * 2. DFS to compute maximum number of steps possible from each node
 * 3. Graph preprocessing with a dummy node 0 connected to all nodes
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll maxn = 2e5 + 5;
ll a[maxn];
vector<ll> edge[maxn];
ll mid;
ll vis[maxn];
ll dp[maxn];
ll n;

// Initialize visited and dp arrays
void init() {
  for (int i = 0; i <= n; i++)
    vis[i] = 0, dp[i] = 0;
}

// DFS to compute maximum steps possible from node x without exceeding 'mid' value
ll dfs(ll x) {
  if (vis[x]) // Detected cycle
    return dp[x] = 2e18;
  if (dp[x]) // Already computed
    return dp[x];
  vis[x] = 1;
  for (ll y : edge[x]) {
    if (a[y] > mid) // Skip if value exceeds current target
      continue;
    dp[x] = max(dfs(y) + 1, dp[x]); // Take maximum steps from neighbors
  }
  vis[x] = 0; // Backtrack
  return dp[x];
}

int main() {
  ll m, k;
  cin >> n >> m >> k;
  for (ll i = 1; i <= n; i++)
    cin >> a[i];
  for (ll i = 1; i <= m; i++) {
    ll x, y;
    cin >> x >> y;
    edge[x].push_back(y);
  }
  ll l = 1, r = 2e18;
  ll ans = -1;
  
  // Connect dummy node 0 to all nodes to allow starting from any node
  for (ll i = 1; i <= n; i++)
    edge[0].push_back(i);
    
  // Binary search over the answer
  while (l <= r) {
    mid = (l + r) / 2;
    init();
    if (dfs(0) < k) // If we can't make enough steps
      l = mid + 1;
    else // If we can make enough steps, try smaller value
      r = mid - 1, ans = mid;
  }
  cout << ans << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/