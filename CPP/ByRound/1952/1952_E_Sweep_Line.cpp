// Problem: CF 1952 E - Sweep Line
// https://codeforces.com/contest/1952/problem/E

/*
 * Problem: Sweep Line with State Tracking
 * Algorithm/Techniques: Dynamic Programming with State Compression
 * 
 * Purpose:
 *   This code processes a sequence of integers (0, 1, or 2) and tracks states 
 *   using a pair of integers to determine how many valid solutions exist.
 *   It uses a sweep line approach, updating state based on input values.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <cstdio>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  
  // cur represents current state (first, second) 
  // nxt represents next state
  std::pair<int, int> cur(1, 0), nxt(1, 1);
  
  for (int p = 0; p < n; p++) {
    int x;
    scanf("%d", &x);
    
    // Update current state based on input value
    if (x == 0) {
      // Reset second component to 0
      cur.second = 0;
    } else if (x == 1) {
      // Swap first and second components
      std::swap(cur.first, cur.second);
    } else if (x == 2) {
      // Reset first component to 0
      cur.first = 0;
    }
    
    // Swap current and next states for next iteration
    std::swap(cur, nxt);
  }
  
  // Output result: (cur.first + cur.second) * nxt.first
  printf("%d\n", (cur.first + cur.second) * nxt.first);
}


// https://github.com/VaHiX/codeForces/