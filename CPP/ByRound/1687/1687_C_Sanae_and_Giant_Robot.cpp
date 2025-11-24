// Problem: CF 1687 C - Sanae and Giant Robot
// https://codeforces.com/contest/1687/problem/C

/*
 * Problem: C. Sanae and Giant Robot
 * 
 * Algorithm/Technique: 
 * 1. Use difference array to track changes needed from array 'a' to 'b'
 * 2. Use a graph of segments to represent connectivity
 * 3. Use BFS (queue) to process overlapping segments
 * 4. Maintain a set to track positions where changes are needed
 * 
 * Time Complexity: O(n + m * log(m)) - where n is array length and m is number of segments
 * Space Complexity: O(n + m) - for difference array and segment graph
 * 
 * The approach models the problem as a graph connectivity issue where each segment
 * represents a connection, and we check if all positions can be made consistent
 * through these connections.
 */

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <utility>

using namespace std;
enum { N = 200009 };
long long s[N]; // Difference array to store cumulative sum of changes needed
set<int> p; // Set to store positions where difference is non-zero
queue<pair<int, int>> q; // Queue to store connected segments to be processed
basic_string<int> g[N]; // Adjacency list representing segment connections

// Function to add adjacent segments to queue for processing
void wk(int x) {
  for (int o : g[x]) {
    if (!p.count(o)) { // If neighbor hasn't been processed yet
      if (x < o)
        q.push({x, o});
      else
        q.push({o, x});
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T, n, m, i, j, k;
  for (cin >> T; T--;) {
    cin >> n >> m;
    for (i = 1; i <= n; ++i)
      cin >> s[i]; // Read initial array 'a'
    for (i = 1; i <= n; ++i)
      cin >> j, s[i] -= j, s[i] += s[i - 1]; // Compute difference array (cumulative)
    for (i = 0; i <= n; ++i)
      g[i] = {}; // Initialize graph
    p = {}; // Clear set
    while (m--) {
      cin >> j >> k; // Read a segment
      g[j - 1] += k; // Add k to j-1's adjacency list
      g[k] += j - 1; // Add j-1 to k's adjacency list
    }
    for (i = 0; i <= n; ++i)
      if (s[i])
        p.insert(i); // Add positions with non-zero difference
    for (i = 0; i <= n; ++i)
      if (!s[i])
        wk(i); // Process segments that don't need changes
    while (q.size()) {
      tie(i, j) = q.front(), q.pop(); // Extract segment boundaries
      while (1) {
        auto o = p.lower_bound(i); // Find first position >= i
        if (o == p.end() || *o > j) // If no more positions in range
          break;
        wk(*o), p.erase(o); // Process and remove that position
      }
    }
    if (p.size()) // If any positions are left unprocessed
      cout << "NO\n";
    else
      cout << "YES\n";
  }
}


// https://github.com/VaHiX/CodeForces/