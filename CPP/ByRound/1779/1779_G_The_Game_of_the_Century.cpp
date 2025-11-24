// Problem: CF 1779 G - The Game of the Century
// https://codeforces.com/contest/1779/problem/G

/*
 * Problem: The Game of the Century
 * Algorithm: Greedy approach with checking connectivity constraints
 * 
 * Time Complexity: O(n) per test case, where n is the side length of the triangle
 * Space Complexity: O(n) for storing the input strings
 * 
 * The village is modeled as a triangular grid with n^2 small triangles.
 * Each of the 3n roads (parallel to the three sides) has a direction assigned.
 * The task is to find the minimum number of road segments to reverse so that
 * all intersections are reachable from each other (i.e., the graph becomes strongly connected).
 * 
 * Key Insight:
 * For a directed triangular grid, each pair of roads (one from each of the three directions)
 * must be properly connected. If the last segment of two roads differs in direction,
 * we need to consider reversing segments to make the graph connected.
 * 
 * The solution works by:
 * 1. Comparing the last segment of each pair of roads from different directions
 * 2. If they differ, we need to reverse some segments in between
 * 3. We count how many reversals are needed
 * 4. Return the minimum of total reversals or n (because there's an upper bound)
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int n, t, ans;
string st[3];

void solve() {
  cin >> n >> st[0] >> st[1] >> st[2];
  ans = 0;
  
  // Check each pair of directions (0,1), (0,2), (1,2)
  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++) {
      // If the last road segments of direction i and j are different
      if (st[i][n - 1] != st[j][n - 1]) {
        // Traverse backwards to count how many segments need to be reversed
        for (int k = n - 1;
             k >= 0 && st[i][n - 1] != st[j][k] && st[i][k] != st[j][n - 1];
             k--)
          ans++;  // Increment counter for each reversal needed
      }
    }
  }
  
  // Output minimum between total reversals and n (bound)
  cout << min(ans, n) << endl;
}

int main() {
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/