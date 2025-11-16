// Problem: CF 2044 G2 - Medium Demon Problem (hard version)
// https://codeforces.com/contest/2044/problem/G2

/*
 * Problem: G2. Medium Demon Problem (hard version)
 * Description: 
 *   A group of n spiders exchange plushies every year. Each spider i gives one plushie to spider r[i] if they have at least one plushie.
 *   The process is stable when the number of plushies each spider has remains the same as the previous year.
 *   Find the first year in which this stability occurs.
 *
 * Algorithms/Techniques:
 *   - Topological sorting with queue
 *   - Graph traversal to simulate plushie distribution
 *   - Detect cycles and compute maximum depth in directed graph
 *
 * Time Complexity: O(n) per test case, as each node is visited once.
 * Space Complexity: O(n) for storing adjacency list, in-degrees, and auxiliary data structures.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
#define end '\n'

void sol() {
  int n;
  cin >> n;
  int ans = 0;
  vector<int> ind(n + 1, 0);     // in-degree of each node
  vector<int> d(n + 1, 0);       // depth or number of plushies for each node
  vector<int> nxt(n + 1, 0);     // next recipient of plushie for each spider

  // Read input and build graph (in-degrees and next pointers)
  for (int i = 1; i <= n; ++i) {
    cin >> nxt[i];
    d[i]++;                      // Initially each spider has one plushie
    ind[nxt[i]]++;               // increment in-degree of recipient
  }

  queue<int> q;
  // Initialize queue with nodes having zero in-degree (no incoming edges)
  for (int i = 1; i <= n; ++i) {
    if (!ind[i])
      q.push(i);
  }

  // Process nodes in topological order
  while (!q.empty()) {
    auto u = q.front();          // current spider
    auto v = nxt[u];             // recipient of plushie from spider u
    q.pop();
    ans = max(ans, d[u]);        // update maximum depth seen so far
    ind[v]--;                    // decrement in-degree of recipient
    d[v] += d[u];                // accumulate plushies to recipient
    if (!ind[v])                 // if recipient now has zero in-degree
      q.push(v);                 // add to queue for processing
  }

  cout << ans + 2 << endl;       // Add 2 because first year is not stable and we start from year 1
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    sol();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/