// Problem: CF 2118 D2 - Red Light, Green Light (Hard version)
// https://codeforces.com/contest/2118/problem/D2

/*
Problem: D2. Red Light, Green Light (Hard version)
Algorithms/Techniques: 
  - Graph construction using modular arithmetic 
  - DFS for cycle detection in directed graph
  - Two-pointer technique with sorting
  - Map-based lookup and forward/backward traversal

Time Complexity: O(n log n + m log m + n + m)
Space Complexity: O(n + m)

Code Purpose:
This solution determines whether a person starting at various positions on a strip will escape within 10^100 seconds, based on timing of traffic lights.
Each light shows red at l*k + d_i seconds where l is integer and d_i is the delay.
A DFS is used to detect cycles in the movement graph, which helps determine if a position leads to an escape or loop.
*/
#include <algorithm>
#include <cstdio>
#include <map>
#include <utility>

using namespace std;
int n, m, l, t, lp[400010], ant[200010], to[400010];
long long md, p[200010], d[200010];
pair<long long, int> q[200010];
bool ans[200010];
map<long long, int> mp;

// dfs: Performs depth-first search to label nodes with cycle information
void dfs(int x) {
  lp[x] = 1; // Mark node as being visited
  if (!to[x]) {
    lp[x] = 2; // Set label for terminal node (0)
    return;
  }
  if (!lp[to[x]]) // If not visited yet, visit next node
    dfs(to[x]);
  lp[x] = lp[to[x]]; // Propagate label from next node
}

void solve() {
  scanf("%d%lld", &n, &md);
  for (int i = 1; i <= n; ++i)
    to[i] = lp[i] = to[n + i] = lp[n + i] = 0;
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &p[i]);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &d[i]);
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    scanf("%lld", &q[i].first);
    q[i].second = i;
    ant[i] = 0;
  }
  sort(q, q + m); // Sort queries by position
  mp.clear();
  
  // Build forward edges from points to nearest next point (based on delay)
  for (int i = 1; i <= n; ++i) {
    to[i] = mp[(p[i] + d[i]) % md]; // Find previous point matching condition 
    mp[(p[i] + d[i]) % md] = n + i; // Store current point index
  }
  
  mp.clear();
  
  // Build reverse edges for points using backward logic with delay and modulo
  for (int i = n, j = m - 1; j >= 0 || i; --i) {
    while (j >= 0 && (!i || p[i] < q[j].first)) {
      ant[j] = mp[q[j].first % md]; // Get nearest previous point
      --j;
    }
    if (!i)
      break;
    to[n + i] = mp[(p[i] + md - d[i]) % md]; // Forward connection based on delay and modulo
    mp[(p[i] + md - d[i]) % md] = i; // Store point using computed value
  }
  
  // Label all nodes using DFS to find cycle information
  for (int i = 1; i <= 2 * n; ++i)
    if (!lp[i])
      dfs(i);
      
  // Evaluate answer for each query using precomputed ant and lp values
  for (int j = 0; j < m; ++j) {
    if (!ant[j]) // No previous node found
      ans[q[j].second] = 1;
    else
      ans[q[j].second] = ~lp[ant[j]] & 1; // Check label from ant to determine result
  }
  
  for (int j = 0; j < m; ++j)
    printf(ans[j] ? "YES\n" : "NO\n");
}

int main() {
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/