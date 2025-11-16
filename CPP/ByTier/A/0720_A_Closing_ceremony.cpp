// Problem: CF 720 A - Closing ceremony
// https://codeforces.com/contest/720/problem/A

/*
 * Problem: Closing Ceremony
 * 
 * Algorithm/Technique: Greedy + Sorting + Two Pointers
 * 
 * Time Complexity: O(n * m * log(n * m))
 * Space Complexity: O(n * m)
 * 
 * Approach:
 * - We model the seating arrangement as a grid of n rows and m columns.
 * - People are divided into two queues:
 *   - Queue 1 at (0, 0) with k people having stamina values.
 *   - Queue 2 at (0, m+1) with (n*m - k) people having stamina values.
 * - We want to assign each seat to a person such that the person's stamina 
 *   is sufficient for the Manhattan distance to reach the seat.
 * - Greedy assignment is used:
 *   - Process seats row by row from bottom to top.
 *   - For each seat (i,j), compute the minimum distance from both queues.
 *   - Assign the seat to a person with sufficient stamina.
 *   - If no one is available, return "NO".
 * 
 * Key observations:
 * - For seat (i, j), queue 1 (0,0) distance is (i + j).
 * - For seat (i, j), queue 2 (0, m+1) distance is (i + (m+1-j)).
 * - Sorting stamina arrays lets us use efficient binary search.
 * - Use lower_bound to find the smallest stamina value that satisfies the required distance.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m, k, x;
vector<int> a, b;

int main() {
  cin >> n >> m >> k;
  // Read stamina values for people at (0,0)
  for (int i = 0; i < k; i++)
    cin >> x, a.push_back(x);
  // Read number of people at (0, m+1) and then their stamina values
  cin >> x;
  for (int i = 0; i < n * m - k; i++)
    cin >> x, b.push_back(x);
  
  // Sort stamina values for efficient matching
  sort(a.begin(), a.end()), sort(b.begin(), b.end());
  
  // Process seats in a specific order (bottom to top, left to right)
  for (int i = n; i >= 1; i--)
    for (int j = 1; j <= m; j++) {
      // Find minimum stamina needed for seat (i,j)
      // From queue 1 (0,0): distance = i + j
      // From queue 2 (0,m+1): distance = i + m + 1 - j
      auto p = lower_bound(a.begin(), a.end(), i + j);  // Check queue 1
      auto q = lower_bound(b.begin(), b.end(), i + m + 1 - j);  // Check queue 2
      
      // Try to assign to queue 1
      if (p != a.end()) {
        a.erase(p);  // Remove used stamina value
      } else if (q != b.end()) {
        b.erase(q);  // Remove used stamina value
      } else {
        // No one can reach this seat
        return cout << "NO", 0;
      }
    }
    
  cout << "YES";
}


// https://github.com/VaHiX/CodeForces/