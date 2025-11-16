// Problem: CF 1775 D - Friendly Spiders
// https://codeforces.com/contest/1775/problem/D

/*
 * Problem: D. Friendly Spiders
 * 
 * Purpose: Find the minimum time to send a message between two spiders in a colony,
 *          where spiders are friends if they share a common factor greater than 1.
 *          The message transmission follows the shortest path in a graph where
 *          edges exist between friend spiders.
 * 
 * Approach:
 * 1. Precompute smallest prime factors (SPF) for numbers up to 3e5 using sieve.
 * 2. Group spider indices by their prime factors (spiders with same prime factors are connected).
 * 3. Run BFS from source spider to find shortest path to target spider.
 * 4. Reconstruct the path using parent pointers.
 * 
 * Time Complexity: O(N * log(N) + N * sqrt(N)) where N = 3e5
 *                  - Sieve of Eratosthenes: O(N * log(log(N)))
 *                  - Prime factorization of legs: O(N * sqrt(N))
 *                  - BFS: O(N)
 * Space Complexity: O(N) for SPF array, adjacency list, distance, and parent arrays
 * 
 * Algorithms/Techniques:
 * - Sieve of Eratosthenes for precomputing smallest prime factors
 * - BFS for shortest path in unweighted graph
 * - Prime factorization with SPF
 * - Path reconstruction using parent pointers
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#ifdef LOCAL
#include "debug.h"
#else
#define dout(...) 0
#endif
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  const int N = 3e5;
  vector<int> f(N + 1, -1);
  // Precompute smallest prime factor for each number from 2 to N
  for (int i = 2; i <= N; i++) {
    if (f[i] == -1) {
      for (int j = i; j <= N; j += i) {
        f[j] = i;
      }
    }
  }
  int n;
  cin >> n;
  vector<int> a(n);
  vector<vector<int>> g(N); // Group spiders by their prime factors
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    int x = a[i];
    // Factorize the number and build the adjacency list
    while (x > 1) {
      int y = f[x];
      g[y].push_back(i);
      while (x % y == 0) {
        x /= y;
      }
    }
  }
  int s, t;
  cin >> s >> t;
  --s, --t; // Convert to 0-based indexing
  queue<int> q;
  const int INF = 1e9;
  vector<int> d(n, INF), p(n, -1); // Distance and parent arrays
  q.push(s);
  d[s] = 0;
  while (!q.empty()) {
    int i = q.front();
    q.pop();
    int x = a[i];
    // Traverse all prime factors of current spider's legs
    while (x > 1) {
      int y = f[x];
      // Process all spiders with this prime factor
      for (int j : g[y]) {
        if (d[j] > d[i] + 1) {
          d[j] = d[i] + 1;
          p[j] = i;
          q.push(j);
        }
        // Update spider's legs to avoid reprocessing same prime factor
        while (a[j] % y == 0) {
          a[j] /= y;
        }
      }
      // Move to the next prime factor
      while (x % y == 0) {
        x /= y;
      }
    }
  }
  if (d[t] == INF) { // No path exists
    cout << -1 << '\n';
    return 0;
  }
  vector<int> ans;
  int u = t;
  // Reconstruct path from target to source
  while (u != s) {
    ans.push_back(u);
    u = p[u];
  }
  ans.push_back(s);
  reverse(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (int x : ans) {
    cout << x + 1 << " \n"[x == t]; // Print in 1-based indexing
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/