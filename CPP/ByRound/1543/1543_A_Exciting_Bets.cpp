// Problem: CF 1543 A - Exciting Bets
// https://codeforces.com/contest/1543/problem/A

#include <cstdio>
typedef long long ll;

/*
 * Problem: Exciting Bets
 * 
 * Purpose:
 *   Given two integers a and b representing bets, determine the maximum possible GCD 
 *   after performing operations that either increase or decrease both values by 1.
 * 
 * Algorithms/Techniques:
 *   - Number theory (GCD properties)
 *   - Mathematical optimization using modular arithmetic
 *   - Greedy approach for minimal steps
 * 
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    ll mn = (a < b) ? a : b;  // Find minimum of a and b
    ll mx = (a > b) ? a : b;  // Find maximum of a and b
    ll g = mx - mn;           // Difference between max and min

    if (g == 0) {
      puts("0 0");            // If a == b, GCD is a, no moves needed
      continue;
    }

    // Calculate steps to reduce difference to a multiple of g
    ll stepsA = (g + (g - mn) % g) % g;  // Steps to make smaller number congruent to 0 mod g
    ll stepsB = (mn % g);                // Steps to make smaller number divisible by g
    ll steps = (stepsA < stepsB) ? stepsA : stepsB;  // Take minimum steps

    printf("%lld %lld\n", g, steps);
  }
}


// https://github.com/VaHiX/codeForces/