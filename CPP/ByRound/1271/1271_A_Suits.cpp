// Problem: CF 1271 A - Suits
// https://codeforces.com/contest/1271/problem/A

/*
 * Problem: Maximize the cost of suits that can be formed from given clothing items.
 * 
 * Description:
 * We have a set of clothing items: ties (a), scarves (b), vests (c), and jackets (d).
 * Two types of suits can be made:
 *   - Type 1: 1 tie + 1 jacket, worth e coins
 *   - Type 2: 1 scarf + 1 vest + 1 jacket, worth f coins
 * 
 * Goal: Maximize the total value of suits formed.
 * 
 * Approach:
 * Greedy strategy:
 *   - Try both possibilities: prioritize suit type with higher value (e or f)
 *   - For each case, calculate how many suits can be made and maximize profit
 * 
 * Time Complexity: O(1) - Constant time operations
 * Space Complexity: O(1) - Only a fixed number of variables used
 */
#include <cstdio>
int main() {
  long a, b, c, d, e, f;
  scanf("%ld %ld %ld %ld %ld %ld", &a, &b, &c, &d, &e, &f);
  long x = a; // Number of ties available
  long y = (b < c) ? b : c; // Minimum of scarves and vests for second type suits
  long total(0); // Total maximum value

  if (e < f) {
    // Prioritize second type suits (higher value)
    y = (y < d) ? y : d; // Limit by number of jackets
    total = f * y; // Use all available jackets for second type suits
    d -= y; // Reduce jackets count
    x = (x < d) ? x : d; // Limit ties by remaining jackets
    total += e * x; // Add profit from first type suits
  } else {
    // Prioritize first type suits (higher value)
    x = (x < d) ? x : d; // Limit ties by jackets
    total = e * x; // Use all possible first type suits
    d -= x; // Reduce jackets count
    y = (y < d) ? y : d; // Limit scarves/vests by remaining jackets
    total += f * y; // Add profit from second type suits
  }
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/codeForces/