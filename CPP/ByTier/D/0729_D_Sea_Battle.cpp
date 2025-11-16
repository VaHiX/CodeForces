// Problem: CF 729 D - Sea Battle
// https://codeforces.com/contest/729/problem/D

/*
 * Purpose: Solve the one-dimensional Sea Battle problem where we must determine 
 *          the minimum number of additional shots needed to guarantee hitting at least one ship.
 *          Given a grid of length n, a ships each of size b, and k previous misses,
 *          we need to place the minimum number of shots such that every valid ship placement
 *          is hit by at least one shot.
 *          
 * Algorithm: 
 *   1. Identify all maximal continuous segments of unused cells (misses).
 *   2. From these segments, pick the optimal positions to place shots such that 
 *      each ship (of size b) is covered.
 *   3. Use a greedy strategy to place shots just before the end of each valid segment
 *      that can accommodate a ship of length b.
 * 
 * Time Complexity: O(n) - Single pass through the string.
 * Space Complexity: O(n) - For storing the positions of shot candidates.
 * 
 * Techniques:
 *   - Greedy algorithm
 *   - Sliding window approach on unused cells
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, a, b, k;
  std::cin >> n >> a >> b >> k;
  std::string s;
  std::cin >> s;
  long counter(0); // Counter for consecutive unused cells
  std::vector<long> v; // Vector to store positions where shots should be made
  
  for (long p = 0; p < n; p++) {
    if (s[p] == '1') {
      // If the cell was already shot (1), reset counter
      counter = 0;
    } else {
      // If the cell is unused (0), increment counter
      ++counter;
      // If we've found a segment of b or more unused cells
      if (counter >= b) {
        // Mark the end of the segment (position p) as a safe shot location
        counter = 0;
        v.push_back(p);
      }
    }
  }
  
  // Calculate how many shots we need to make
  long needed = v.size() - a + 1;
  std::cout << needed << std::endl;
  
  // Output the shot positions
  for (long p = 0; p < needed; p++) {
    std::cout << (v[p] + 1) << " "; // Convert to 1-based indexing
  }
  std::cout << std::endl;
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/