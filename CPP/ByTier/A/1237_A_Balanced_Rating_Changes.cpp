// Problem: CF 1237 A - Balanced Rating Changes
// https://codeforces.com/contest/1237/problem/A

/*
Algorithm: Balancing Rating Changes
Approach:
- For each participant, we initially compute the floor of half their rating change (x/2).
- However, since the final sum must be zero and we are rounding, we track a running "difference" (diff) from the ideal sum.
- When the current value is odd, we adjust it to make the overall sum closer to zero.
- If diff >= 0 and x is odd, we decrement x to reduce the total sum (to keep it balanced).
- If diff < 0 and x is odd, we increment x to increase the total sum (to keep it balanced).
  
Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long diff(0); // Tracks the cumulative difference from ideal rounding
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    // If x is odd and diff is non-negative, we round down (decrease x)
    // If x is odd and diff is negative, we round up (increase x)
    if (x % 2 && diff >= 0) {
      --x;      // Adjust x to round down
      --diff;   // Update diff accordingly
    } else if (x % 2 && diff < 0) {
      ++x;      // Adjust x to round up
      ++diff;   // Update diff accordingly
    }
    printf("%ld\n", x / 2); // Output the final rounded value
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/