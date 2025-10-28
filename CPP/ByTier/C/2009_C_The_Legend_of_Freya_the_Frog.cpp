// Problem: CF 2009 C - The Legend of Freya the Frog
// https://codeforces.com/contest/2009/problem/C

/*
C. The Legend of Freya the Frog
Purpose: 
  Calculates the minimum number of moves required for Freya the Frog to reach point (x, y) from (0, 0),
  where each move has a maximum distance 'k', and alternating directions between x and y axes.
Algorithm:
  - Use mathematical approach to calculate minimum moves in O(1) time per test case.
  - For each coordinate, compute the number of steps needed using ceiling division: (value + k - 1) / k.
  - Since the frog alternates directions (x, then y, x, y, ...), we calculate the max steps required for either axis.
  - The formula is: 2 * max(x_steps, y_steps) - (1 if x_steps > y_steps else 0).
Time Complexity: O(1) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, k;
    scanf("%ld %ld %ld", &x, &y, &k);
    // Compute number of steps for x and y directions using ceiling division
    x = (x + k - 1) / k;  // Number of moves needed in x direction if each step goes up to k units
    y = (y + k - 1) / k;  // Number of moves needed in y direction if each step goes up to k units
    // Final result is calculated by taking the maximum of both directions and applying alternating pattern logic
    printf("%ld\n", 2 * (x > y ? x : y) - (x > y));  // Simplified expression for alternating move counting
  }
}


// https://github.com/VaHiX/codeForces/