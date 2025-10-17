// Problem: CF 1760 D - Challenging Valleys
// https://codeforces.com/contest/1760/problem/D

/*
 * Problem: D. Challenging Valleys
 * 
 * Algorithm/Technique: Single Pass with State Tracking
 * 
 * Time Complexity: O(n) - Each element is visited once per test case.
 * Space Complexity: O(1) - Only using a constant amount of extra space.
 * 
 * Description:
 * Determines if an array is a "valley". A valley has exactly one flat subarray
 * (a segment of equal elements) such that the elements before it are strictly
 * decreasing and after it are strictly increasing.
 * 
 * Approach:
 * - Traverse the array once while tracking if we're in a decreasing or increasing phase.
 * - When encountering an increase, switch to increasing mode.
 * - If we encounter a decrease when already in increasing mode, it's not a valley.
 * - Also handle cases where array is all equal or has multiple peaks/valleys.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cur;
    scanf("%ld", &cur);
    bool down(true), res(true); // 'down' tracks if we're currently going down; 'res' tracks validity
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (cur > x) { // If current element is greater than next, we are decreasing
        if (!down) { // If previously already started increasing, then invalid valley
          res = false;
        }
      } else if (cur < x) { // If current element is less than next, we start to increase
        down = false; // Mark that we've entered the increasing phase
      }
      cur = x; // Move to next element
    }
    puts(res ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/