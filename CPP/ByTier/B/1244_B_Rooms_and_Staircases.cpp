// Problem: CF 1244 B - Rooms and Staircases
// https://codeforces.com/contest/1244/problem/B

/*
 * Problem: B. Rooms and Staircases
 * 
 * Purpose:
 *   Given a two-storied house with n rooms per floor, and staircases between corresponding rooms,
 *   find the maximum number of rooms that can be visited in a single path without revisiting any room.
 * 
 * Algorithms/Techniques:
 *   - Greedy approach: For each possible starting position (either floor), calculate the maximum
 *     reachable nodes by simulating movement through adjacent cells and using staircases when available.
 *   - For each '1' in the string, a staircase exists between floors at that index.
 * 
 * Time Complexity: O(n^2) where n is the number of rooms per floor.
 * Space Complexity: O(1) - only constant extra space used (not counting input).
 */

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  long t;
  std::cin >> t;  // Read number of test cases
  while (t--) {
    long n;
    std::cin >> n;  // Read number of rooms per floor
    std::string s;
    std::cin >> s;  // Read the string representing staircases

    long mx(n);  // Initialize maximum with n (at least one full floor can be visited)
    
    for (long p = 0; p < n; p++) {
      if (s[p] == '0') {
        continue;  // Skip if no staircase at this position
      }
      
      // Calculate maximum reachable rooms starting from this staircase
      long cur = 2 * ((2 * p < n) ? (n - p) : (p + 1));
      mx = (mx > cur) ? mx : cur;  // Update maximum if current is larger
    }
    
    printf("%ld\n", mx);  // Output result for this test case
  }
  
  return 0;
}


// https://github.com/VaHiX/codeForces/