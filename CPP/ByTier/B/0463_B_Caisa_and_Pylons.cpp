// Problem: CF 463 B - Caisa and Pylons
// https://codeforces.com/contest/463/problem/B

/*
Purpose: This program calculates the minimum number of dollars Caisa must pay to ensure he can reach the n-th pylon
         without running out of energy. The key insight is that Caisa needs enough initial height on pylon 0 so that
         the energy never goes negative during the journey. The minimum height required at pylon 0 is the maximum
         "drop" (difference in height) he encounters when moving from one pylon to the next, starting from pylon 0.

Algorithms/Techniques: 
- Linear scan through the array of heights.
- Track the maximum drop in height encountered when moving from one pylon to the next.
- The required initial height of pylon 0 is equal to this maximum drop.

Time Complexity: O(n) - single pass through n elements
Space Complexity: O(1) - only using a few variables regardless of input size

*/
#include <cstdio>
int main() {
  long n;
  scanf("%ld\n", &n);
  long output = 0;  // This variable will store the maximum drop encountered
  for (long p = 0; p < n; p++) {
    long height;
    scanf("%ld", &height);
    // Update the output to be the maximum of current output and the height of the current pylon
    // This effectively tracks how much we might need to increase pylon 0's height
    output = (output > height) ? output : height;
  }
  printf("%ld\n", output);
  return 0;
}


// https://github.com/VaHiX/CodeForces/