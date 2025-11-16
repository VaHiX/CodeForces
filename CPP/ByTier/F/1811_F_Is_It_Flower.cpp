// Problem: CF 1811 F - Is It Flower?
// https://codeforces.com/contest/1811/problem/F

#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define lb(x, y) lower_bound(all(x), y) - begin(x)

// Flowerbox:
// Purpose: Determine if a given graph is a k-flower for some k.
// Algorithm: 
// 1. First check if number of vertices N is a perfect square (k^2 = N), since a k-flower has k cycles of length k each.
// 2. Then, perform BFS to find two types of components:
//    - Components of degree 2 vertices forming a cycle (potential outer cycle)
//    - Components of degree 4 vertices forming the central structure
// 3. Validate that outer cycles have exactly k-1 vertices, and central vertices have exactly 2 connections.
// 4. Final checks ensure only one component of degree 4, and all vertices are visited.
// Time Complexity: O(N + M) per test case, where N is vertices, M is edges.
// Space Complexity: O(N + M) for adjacency list storage and visited array.

int search(int k, int l, int r) {
  if (l > r)
    return -1;
  int mid = (l + r) / 2;
  if (mid * mid >= k) {
    int m = search(k, l, mid - 1);
    if (m == -1)
      return mid;
    return m;
  }
  return search(k, mid + 1, r);
}

void solve() {
  int N, M;
  cin >> N >> M;
  vector<vector<int>> adj(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  int K = search(N, 0, 1000);
  if (K * K != N) {
    cout << "NO" << "\n";
    return;
  }
  queue<int> q;
  vector<bool> vis(N);
  fill(all(vis), false);
  int cnt4 = 0;
  for (int i = 0; i < N; i++) {
    if (sz(adj[i]) == 2 && !vis[i]) {
      vector<int> out;
      vis[i] = true;
      q.push(i);
      int cnt = 0;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;
        for (int v : adj[u]) {
          if (sz(adj[v]) != 2) {
            if (sz(adj[v]) != 4) {
              cout << "NO" << "\n";
              return;
            }
            out.pb(v);
          } else if (!vis[v]) {
            vis[v] = true;
            q.push(v);
          }
        }
      }
      if (!(cnt == K - 1 && sz(out) == 2 && out[0] == out[1])) {
        cout << "NO" << "\n";
        return;
      }
    } else if (sz(adj[i]) == 4 && !vis[i]) {
      cnt4++;
      vis[i] = true;
      q.push(i);
      int cnt = 0;
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        cnt++;
        int cntA = 0;
        for (int v : adj[u]) {
          if (sz(adj[v]) == 4) {
            cntA++;
          }
          if (sz(adj[v]) == 4 && !vis[v]) {
            vis[v] = true;
            q.push(v);
          }
        }
        if (cntA != 2) {
          cout << "NO" << "\n";
          return;
        }
      }
      if (cnt != K) {
        cout << "NO" << "\n";
        return;
      }
    }
  }
  if (cnt4 != 1) {
    cout << "NO" << "\n";
    return;
  }
  for (bool b : vis) {
    if (!b) {
      cout << "NO" << "\n";
      return;
    }
  }
  cout << "YES" << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/