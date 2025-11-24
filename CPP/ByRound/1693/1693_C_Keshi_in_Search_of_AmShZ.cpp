// Problem: CF 1693 C - Keshi in Search of AmShZ
// https://codeforces.com/contest/1693/problem/C

/*
 * Problem: Keshi in Search of AmShZ
 *
 * Approach:
 * This problem is about finding the minimum number of days required for Keshi
 * to reach city n from city 1, where each day AmShZ can either block a road or
 * tell Keshi to move. Keshi moves to a random reachable city (if any), and
 * AmShZ knows Keshi's location at all times.
 *
 * Key Idea:
 * This is essentially a shortest path problem, but we're looking for a
 * "worst-case" scenario. We model it as a modified Dijkstra using a priority
 * queue.
 *
 * We calculate d[i] = minimum number of days to reach city i from city n,
 * and for each city we track how many outgoing edges remain unblocked.
 *
 * We use a reverse graph (rg) to process from the destination (n) back to
 * source (1), using a modified Dijkstra with priority on the number of
 * out-going edges.
 *
 * Time Complexity: O((n + m) * log n)
 * Space Complexity: O(n + m)
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m, x, y, out[N], d[N], v[N];
vector<int> rg[N]; // Reverse graph: rg[i] contains cities with edges to i
priority_queue<pair<int, int>>
    q; // Priority queue for Dijkstra: {-distance, node}

signed main() {
  scanf("%d%d", &n, &m);
  // Read all directed edges and update out-degree and reverse graph
  for (int i = 1; i <= m; i++)
    scanf("%d%d", &x, &y), out[x]++, rg[y].push_back(x);

  // Initialize distances to infinity (0x3f = 63 in decimal)
  memset(d, 0x3f, sizeof(d)),
      d[n] = 0, q.push({0, n}); // Start from node n with distance 0
  while (q.size()) {
    int y = q.top().second; // Current node
    q.pop();
    if (v[y]) // Skip if already processed (visited)
      continue;
    v[y] = 1; // Mark as visited

    // For all predecessors of current node y
    for (int x : rg[y]) {
      // If we found a better way to reach x, update distance
      if (d[x] > d[y] + out[x])
        d[x] = d[y] + out[x], q.push({-d[x], x});
      out[x]--; // Decrease the out-degree of x as one edge is blocked
    }
  }
  printf("%d\n", d[1]); // Distance from city 1 to city n
  return 0;
}

// https://github.com/VaHiX/CodeForces/