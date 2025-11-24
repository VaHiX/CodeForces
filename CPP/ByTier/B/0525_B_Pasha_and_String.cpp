// Problem: CF 525 B - Pasha and String
// https://codeforces.com/contest/525/problem/B

/*
 * Problem: B. Pasha and String
 * 
 * Purpose:
 *   This program simulates a series of string reversal operations on a given string.
 *   For each operation, a segment from position 'a' to 'length - a + 1' is reversed.
 *   The solution uses a difference array technique to efficiently track how many times
 *   each character in the string has been affected by reversals, then applies those changes
 *   to compute the final string.
 *
 * Algorithms/Techniques:
 *   - Difference Array Technique: Used to efficiently apply range updates for reversal operations.
 *   - Lazy Propagation Simulation: Reversals are computed on-the-fly as we traverse the string.
 *
 * Time Complexity: O(n + m), where n is the length of the string and m is number of operations.
 * Space Complexity: O(n), for storing the difference array and the result string.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::string s;
  getline(std::cin, s);
  long m;
  std::cin >> m;
  
  // Difference array to track reversal counts at each position
  std::vector<long> rev(s.size() + 1, 0);
  
  for (int p = 0; p < m; p++) {
    long a;
    std::cin >> a;
    --a;  // Convert to 0-based indexing
    
    // Mark the start and end of the reversal range
    ++rev[a];                        // Increment at the start
    --rev[s.size() - a];             // Decrement just after the end
  }
  
  int reversals(0);  // Tracks current number of active reversals
  std::string ans(s);  // Resultant string
  
  for (int p = 0; p < s.size(); p++) {
    reversals += rev[p];       // Add current change to the running count
    reversals %= 2;            // Only care if it's odd or even (odd means reversed)
    
    if (reversals) {
      // If currently in a reversed segment, map to mirrored position
      ans[p] = s[s.size() - p - 1];
    }
  }
  
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/