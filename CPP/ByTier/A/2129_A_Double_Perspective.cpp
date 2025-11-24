// Problem: CF 2129 A - Double Perspective
// https://codeforces.com/contest/2129/problem/A

/*
 * Flowerbox:
 * Problem: Maximizing f(S') - g(S')
 * Algorithms/Techniques: Greedy selection based on segment overlap and cycle detection logic
 *
 * Time Complexity: O(n log n) per test case due to map operations and sorting-like behavior
 * Space Complexity: O(n) for storing the map and input data
 *
 * Task Description:
 * Given n pairs (a_i, b_i), we want to select a subset S' such that f(S') - g(S') is maximized,
 * where f(S) is the union length of segments and g(S) is the number of nodes in cycles of at least 3 edges.
 *
 * Approach:
 * For each unique 'a' value, we keep only the pair with maximum 'b' (to maximize union length).
 * We then greedily compute indices that form valid segments to maximize f(S') - g(S').
 * g(S') is estimated by counting nodes involved in cycles of size >= 3 (but this part is heuristic here).
 *
 * This simplification assumes we select a minimal set of segments to maximize overlap while minimizing 
 * cycle contribution (since nodes forming cycles contribute negatively to net gain).
 */
#include <iostream>
#include <map>
#include <utility>

using namespace std;

map<int, pair<int, int>> m; // key = 'a', value = {max_b, index_of_pair}
int t, n;

int main() {
  cin >> t;
  while (t--) {
    m.clear(); // Clear previous data for new test case
    cin >> n;
    for (int i = 1; i <= n; i++) {
      int a, b;
      cin >> a >> b;
      if (m[a].first < b) // If current segment has larger 'b' than stored one for same 'a'
        m[a] = {b, i};   // Update to store this better pair with its index
    }
    cout << m.size() << endl; // Output count of selected pairs
    for (auto op : m) {
      cout << op.second.second << ' '; // Print index of selected pair
    }
    cout << endl;
  }
}


// https://github.com/VaHiX/codeForces/