// Problem: CF 1099 A - Snowball
// https://codeforces.com/contest/1099/problem/A

/*
 * Problem: Snowball Rolling Down a Mountain
 * Algorithm/Techniques: Simulation
 * Time Complexity: O(h), where h is the initial height of the snowball
 * Space Complexity: O(1)
 *
 * The problem simulates a snowball rolling down a mountain, gaining weight 
 * based on current height, hitting stones at specific heights, and losing 
 * weight upon collision. The simulation proceeds from the top (height h) 
 * down to zero.
 */

#include <cstdio>
int main() {
  long w, h;
  scanf("%ld %ld", &w, &h);
  long u1, d1;
  scanf("%ld %ld", &u1, &d1);
  long u2, d2;
  scanf("%ld %ld", &u2, &d2);
  
  ++h; // Increment height to start simulation from h down to 0
  while (h--) {
    w += h; // Weight increases by current height
    if (h == d1) { // If current height matches first stone's height
      w -= u1; // Subtract first stone's weight
    }
    if (h == d2) { // If current height matches second stone's height
      w -= u2; // Subtract second stone's weight
    }
    if (w < 0) {
      w = 0; // Ensure weight doesn't go below zero
    }
  }
  printf("%ld\n", w);
  return 0;
}


// https://github.com/VaHiX/codeForces/