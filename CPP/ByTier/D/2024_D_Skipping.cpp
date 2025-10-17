// Problem: CF 2024 D - Skipping
// https://codeforces.com/contest/2024/problem/D

/*
D. Skipping
Algorithms/Techniques: Dynamic Programming with Priority Queue (Min-Heap)
Time Complexity: O(n log n) per test case
Space Complexity: O(n)

The problem models a competitive scenario where Prokhor can either submit or skip problems,
with each problem having a score 'a[i]' and parameter 'b[i]'. The progression of problems
is determined by the rules involving submission/skip and parameters. A greedy dynamic programming
approach is used with a min-heap to track the minimum cost (dp value) for reaching each position.

Key idea:
- Use dp[i] to represent the minimum cost (points lost) to reach problem i.
- When skipping a problem, we can move to problem at index b[i], ensuring no revisit.
- The priority queue helps maintain optimal transitions between states efficiently.

The final answer is computed as max(sum of scores - dp[i]) for all i, where sum is prefix sum.
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i], b[i]--;
  vector<ll> dp(n, 1e18); // dp[i] stores the minimum cost to reach problem i
  dp[0] = 1; // Start with cost 1 (or 0 if we're counting from zero)
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
  pq.push({0, 0}); // Push initial state: {cost, index}
  for (int i = 0; i < n; i++) {
    // Remove outdated entries in the priority queue
    while (!pq.empty() && pq.top().second < i)
      pq.pop();
    if (pq.empty())
      break;
    dp[i] = pq.top().first;
    if (b[i] <= i)
      continue; // No forward jump possible, so skip adding to heap
    pq.push({dp[i] + a[i], b[i]}); // Add new state: {new_cost, next_index}
  }
  ll ans = 0, sum = 0;
  for (int i = 0; i < n; i++) {
    sum += a[i];
    ans = max(ans, sum - dp[i]); // Maximize score by minimizing cost
  }
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int _ = 1;
  cin >> _;
  while (_--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/