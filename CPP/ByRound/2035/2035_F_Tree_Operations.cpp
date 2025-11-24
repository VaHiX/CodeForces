// Problem: CF 2035 F - Tree Operations
// https://codeforces.com/contest/2035/problem/F

/*
F. Tree Operations
Algorithms/Techniques: Binary search on answer, DFS with subtree processing, tree traversal

Time Complexity: O(n^2 * log(S)) where S is the sum of all values in the tree and n is the number of nodes.
Space Complexity: O(n)

The problem involves a tree with n nodes rooted at node x. Each node has an initial value,
and operations are performed cyclically on nodes. An operation can increment or decrement
the value of any node in a selected node's subtree by 1. We need to find the minimum number
of such operations to make all values equal to zero. This is solved using binary search on
the answer, and for each candidate answer, we use DFS to simulate the process and check feasibility.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define fi first
#define se second
typedef long long ll;
const int N = 5e5 + 5;
int n, x;
ll a[N];
vector<int> adj[N];
ll dp[N];
ll boss;

// DFS to compute minimum operations needed for each subtree
void dfs(int id, int p) {
  ll need = a[id]; // initial value of node 'id'
  for (auto c : adj[id]) {
    if (c == p)
      continue; // Skip parent
    dfs(c, id); // Recursively process child
    need += dp[c]; // Add operations needed from subtree
  }
  
  // The key idea: determine optimal way to distribute excess in subtree
  ll hv = (boss + (n - id)) / n;
  ll mn = (need + hv) % 2;
  dp[id] = max(mn, need - hv);
}

// Check if it is possible to reduce all nodes to zero in 't' operations
bool check(ll t) {
  boss = t;
  dfs(x, 0); // Start DFS from root x
  
  // If root's required operations are zero, it means entire tree can be reduced
  if (dp[x] == 0)
    return true;
  else
    return false;
}

void solve() {
  cin >> n >> x;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    adj[i].clear();
  }
  
  // Build adjacency list for the tree
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  
  ll ans = ((ll)2e9 + 5) * (2 * n); // Initialize large answer
  ll funny = ans;
  int counter = 2 * n; // Binary search iterations
  
  while (counter--) {
    // Binary search bounds based on current ans
    ll l = (ans) / (2 * n) - 5, r = ans / (2 * n);
    if (ans == funny)
      l = 0;
    l = max(l, 0LL);
    
    // Perform binary search in range [l,r]
    while (l != r) {
      ll mid = (l + r) / 2;
      if (check(2 * n * mid + 2 * n - counter - 1))
        r = mid;
      else
        l = mid + 1;
    }
    
    ans = min(ans, 2 * n * l + 2 * n - counter - 1);
  }
  
  // Output result or -1 if impossible
  if (ans == 5e18)
    cout << "-1\n";
  else
    cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/