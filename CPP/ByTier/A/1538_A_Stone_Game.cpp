// Problem: CF 1538 A - Stone Game
// https://codeforces.com/contest/1538/problem/A

/*
 * Problem: Stone Game
 * Algorithm: Greedy approach to find minimum moves to eliminate both min and max elements.
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 *
 * Description:
 * Polycarp needs to destroy the stones with minimum and maximum power values.
 * Each turn, he can only remove either the leftmost or the rightmost stone.
 * The goal is to find the minimum number of moves required to eliminate both the 
 * stone with the smallest power and the stone with the largest power.
 *
 * Strategy:
 * 1. Find positions of min and max elements.
 * 2. Calculate three possible strategies:
 *    - Remove from left to reach min, then remove from right to reach max.
 *    - Remove from left to reach max, then remove from right to reach min.
 *    - Remove from right to reach min, then remove from left to reach max.
 * 3. Choose the minimum among these possibilities.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1e7), mx(-1e7); // Initialize min and max values
    long wn(-1), wx(-1);    // Positions of min and max elements
    
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < mn) {         // Update minimum element and its position
        mn = x;
        wn = p;
      }
      if (x > mx) {         // Update maximum element and its position
        mx = x;
        wx = p;
      }
    }
    
    // Ensure wn is the leftmost of the two positions (so we can compute distance properly)
    if (wn > wx) {
      long tmp = wn;
      wn = wx;
      wx = tmp;
    }
    
    // Compute three possible strategies:
    // da : removing from left to reach min, then from right to reach max
    // db : removing from right to reach min, then from left to reach max  
    // dc : removing from left to reach max, then from right to reach min
    
    long da = wx + 1;        // Distance to reach max from left (0-indexed), +1 for 1-based
    long db = n - wn;        // Distance to reach min from right
    long dc = (n - wx + 1) + wn; // From right to max, then left to min
    
    long res = (da < db) ? da : db;
    res = res < dc ? res : dc;
    
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/