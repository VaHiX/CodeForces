// Problem: CF 471 C - MUH and House of Cards
// https://codeforces.com/contest/471/problem/C

/*
Purpose: This program calculates the number of distinct possible heights (number of floors) 
         for a house of cards that can be built using exactly n cards.

Approach:
- The problem involves finding valid configurations of card houses where:
  - Each floor has a non-zero number of rooms.
  - Each floor has fewer rooms than the floor below it.
  - All n cards must be used exactly.
- For a house with k floors, the minimum number of cards required is derived from:
  - If we denote the number of rooms on each floor as r1 > r2 > ... > rk,
  - Then total cards = 3*r1 + 3*r2 + ... + 3*rk - (k-1) = 3*(r1 + r2 + ... + rk) - (k-1).
  - To minimize card usage, we assign r1 = k, r2 = k-1, ..., rk = 1. This gives:
    Total = 3*(k*(k+1)/2) - (k-1) = (3*k^2 + 3*k - 2*k + 2)/2 = (3*k^2 + k + 2)/2.
  - Solving inequality: (3*k^2 + k + 2)/2 <= n for the maximum possible k.
- A quadratic formula is used to estimate maxFloors.
- Further adjustments are made to ensure valid configurations.
- The final answer is the count of valid heights.

Time Complexity: O(1) - constant time due to math operations.
Space Complexity: O(1) - only a few variables used.
*/
#include <cmath>
#include <cstdio>
int main() {
  long long n;
  scanf("%lld\n", &n);
  // Estimate maximum number of floors using quadratic formula
  long long maxFloors = (-1 + sqrt(1 + 24 * n)) / 6.0;
  // Adjust maxFloors to ensure the configuration is valid with given n cards
  maxFloors -= (n + maxFloors) % 3;
  // Compute the number of distinct heights possible
  printf("%lld\n", (maxFloors + 2) / 3);
  return 0;
}


// https://github.com/VaHiX/CodeForces/