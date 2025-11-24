// Problem: CF 1846 G - Rudolf and CodeVid-23
// https://codeforces.com/contest/1846/problem/G

/*
Algorithm: Shortest Path with Dijkstra
Approach: 
- Each symptom state is a node in a graph
- Each medicine is an edge with cost equal to the number of days it takes
- State transition: remove symptoms (a), then add side effects (b)
- Use Dijkstra's algorithm to find minimum days to reach state 0 (no symptoms)

Time Complexity: O(2^n * m * log(2^n)) where n <= 10, so 2^n <= 1024
Space Complexity: O(2^n) for dp and vis arrays, and O(m) for medicine data
*/

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <utility>
#include <vector>

#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)x.size())
#define rep(i, a, n) for (int i = a; i < n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define IOS                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0);
using namespace std;
using ll = long long;
using PII = pair<int, int>;
mt19937 mrand(random_device{}());
const int N = 1000010, M = 1000, mod = 1e9 + 7, inf = 1 << 30;
int n, m;
void solve() {
  cin >> n >> m;
  vector<int> dp(1 << n, inf), vis(1 << n); // dp[x] = min days to reach state x, vis[x] = visited flag
  vector<array<int, 3>> e(m); // e[i][0] = days, e[i][1] = symptoms removed, e[i][2] = side effects
  int s = 0; // initial state (bitmask of symptoms)
  rep(i, 0, n) {
    char c;
    cin >> c;
    s = s * 2 + c - '0'; // convert string to bitmask
  }
  rep(i, 0, m) {
    cin >> e[i][0]; // days needed
    int s = 0;
    rep(j, 0, n) {
      char c;
      cin >> c;
      s = s * 2 + c - '0'; // symptoms removed
    }
    e[i][1] = s;
    s = 0;
    rep(j, 0, n) {
      char c;
      cin >> c;
      s = s * 2 + c - '0'; // side effects
    }
    e[i][2] = s;
  }
  dp[s] = 0; // initial state requires 0 days
  priority_queue<PII, vector<PII>, greater<PII>> q; // priority queue for Dijkstra: {days, state}
  q.push({0, s});
  auto print = [&](int u) {
    vector<int> a(n);
    for (int i = n - 1; i >= 0; i--)
      a[i] = u >> i & 1;
    rep(i, 0, n) cout << a[i];
    cout << ' ' << dp[u] << endl;
  };
  while (q.size()) {
    auto [w, u] = q.top();
    q.pop();
    if (vis[u])
      continue; // Skip if already processed
    vis[u] = 1;
    for (auto [c, a, b] : e) { // For each medicine
      int v = (u & ~a) | b; // Apply medicine: remove symptoms (a), then add side effects (b)
      if (dp[v] > w + c) { // If we found a better path
        dp[v] = c + w;
        q.push({dp[v], v}); // Add to queue for processing
      }
    }
  }
  if (dp[0] >= inf) // If state 0 (no symptoms) is unreachable
    dp[0] = -1;
  cout << dp[0] << '\n';
}
int main() {
  IOS int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/