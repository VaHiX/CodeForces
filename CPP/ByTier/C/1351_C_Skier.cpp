// Problem: CF 1351 C - Skier
// https://codeforces.com/contest/1351/problem/C

/*
C. Skier
Purpose: Calculate the total time taken by a skier to traverse a path described by a string of directions.
         Movement along new segments takes 5 seconds, while reusing segments takes 1 second.

Algorithms/Techniques:
- Simulate skier's movement step-by-step.
- Track visited edges (pairs of consecutive points) using a set.
- For each move, check if the edge was previously visited to determine time cost.

Time Complexity: O(n * log n) per test case, where n is the length of the string.
                 The log n factor comes from set operations (insert and count).

Space Complexity: O(n), for storing visited edges in the set.

*/

#include <stdio.h>
#include <iostream>
#include <set>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    // Set to store visited edges (pairs of points)
    std::set<std::pair<std::pair<long, long>, std::pair<long, long>>> vis;
    // Current position of skier
    std::pair<long, long> cur(std::make_pair(0, 0));
    long cnt(0);  // Total time counter
    
    for (long p = 0; p < s.size(); p++) {
      // Compute next position based on direction
      std::pair<long, long> next = cur;
      if (s[p] == 'S') {
        --next.second;
      } else if (s[p] == 'N') {
        ++next.second;
      } else if (s[p] == 'W') {
        --next.first;
      } else if (s[p] == 'E') {
        ++next.first;
      }
      
      // Calculate time based on whether edge was visited before
      // If edge is new (count = 0), add 5 seconds, otherwise add 1 second
      cnt += 5 - 4 * vis.count(std::make_pair(cur, next));
      
      // Mark the current and reverse edges as visited
      vis.insert(std::make_pair(cur, next));
      vis.insert(std::make_pair(next, cur));
      
      // Move to next position
      cur = next;
    }
    
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/