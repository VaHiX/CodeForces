// Problem: CF 1841 D - Pairs of Segments
// https://codeforces.com/contest/1841/problem/D

/*
 * Problem: Pairs of Segments
 *
 * Algorithm: Dynamic Programming with Segment Sorting
 * 
 * Approach:
 * - Sort segments by their right endpoint (and then by left endpoint for tie-breaking)
 * - Use dynamic programming where f[i] represents the maximum number of segments 
 *   that can be paired ending at index i (in a valid pairing)
 * - For each segment, check all previous segments to see if they can be paired:
 *   - If p[j].second >= p[i].first, the segments intersect (can be paired)
 *   - Track the maximum valid pairing count
 * - The answer is total segments minus the maximum pairing count
 * 
 * Time Complexity: O(n^2) per test case due to nested loops for dynamic programming
 * Space Complexity: O(n) for storing segments and DP array
 */

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  if (fopen("main.in", "r"))
    freopen("main.in", "r", stdin);
  int nTest;
  cin >> nTest;
  while (nTest-- > 0) {
    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    for (auto &[l, r] : p)
      cin >> l >> r;
    // Sort segments by right endpoint (and then left endpoint)
    sort(p.begin(), p.end(), [](pair<int, int> a, pair<int, int> b) {
      if (a.second != b.second)
        return a.second < b.second;
      return a.first < b.first;
    });
    vector<int> f(n);
    for (int i = 0; i < n; i++) {
      int left = INT_MIN;
      for (int j = i - 1; j >= 0; j--) {
        // If the left boundary is sufficiently large and the current segment
        // starts after the previous one's right boundary, we can form a new pair
        if (left != INT_MIN && left > p[j].second && p[i].first > p[j].second) {
          f[i] = max(f[i], f[j] + 2);
        }
        // If segments intersect (p[j].second >= p[i].first)
        if (p[j].second >= p[i].first) {
          f[i] = max(f[i], 2); // We can form a pair
          left = max(left, p[j].first); // Keep track of the maximum left value
        }
      }
    }
    // Answer is total segments minus the maximum number that can be paired
    cout << n - *max_element(f.begin(), f.end()) << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/