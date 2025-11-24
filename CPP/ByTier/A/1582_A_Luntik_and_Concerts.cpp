// Problem: CF 1582 A - Luntik and Concerts
// https://codeforces.com/contest/1582/problem/A

/*
Problem: A. Luntik and Concerts
Purpose: Distribute all songs into two concerts such that the absolute difference of their durations is minimized.
Algorithm: 
    - Total duration of all songs = a*1 + b*2 + c*3 = a + 2*b + 3*c
    - To minimize the difference, try to split the total into two parts as close as possible.
    - The minimum difference will be 0 if total is even, 1 if total is odd.
    - The key insight is that we can always construct such a split because we have enough flexibility with the available song types.

Time Complexity: O(1) - Constant time operations
Space Complexity: O(1) - Only using a fixed number of variables
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long fa, fb, fc;
    scanf("%ld %ld %ld", &fa, &fb, &fc);
    // Calculate total duration modulo 2 to determine minimal difference
    printf("%ld\n", (fa + fc) % 2);
  }
}


// https://github.com/VaHiX/codeForces/