// Problem: CF 675 B - Restoring Painting
// https://codeforces.com/contest/675/problem/B

/*
 * Problem: Restoring Painting
 * Algorithm: Mathematical constraints solving for 3x3 grid
 * 
 * The problem involves finding how many valid 3x3 grids can be formed 
 * where each cell has a value between 1 and n, and certain constraints 
 * on 2x2 square sums are satisfied.
 * 
 * Key idea:
 * Let the 3x3 grid look like:
 *   a x y
 *   z u v
 *   b c d
 * 
 * The constraint is that all 2x2 squares have the same sum.
 * From these, we derive relationships that let us express most variables in 
 * terms of others, and then find valid ranges for one variable.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long long n, a, b, c, d;
  scanf("%lld %lld %lld %lld %lld\n", &n, &a, &b, &c, &d);
  
  // low and high represent the range of valid values for the center cell 'u'
  long long low(1);
  
  // Compute lower bounds for 'u' based on constraints:
  // Each 2x2 sub-square must sum to same value as top-left 2x2
  low = (low > 1 + c - b) ? low : (1 + c - b);        // from top-right and bottom-left
  low = (low > 1 + d - a) ? low : (1 + d - a);        // from top-left and bottom-right
  low = (low > 1 + c + d - a - b) ? low : (1 + c + d - a - b); // from the overlapping constraint
  
  long long high(n);
  
  // Compute upper bounds for 'u' based on same constraints
  high = (high < n + c - b) ? high : (n + c - b);       // enforce upper bound from top-right
  high = (high < n + d - a) ? high : (n + d - a);       // enforce upper bound from bottom-right
  high = (high < n + c + d - a - b) ? high : (n + c + d - a - b); // enforce upper bound from overlapping

  // For each valid value of 'u', there are n valid choices for each of the remaining cells
  // The total number of valid configurations is n * (high - low + 1)
  printf("%lld\n", (high >= low) ? (n * (high - low + 1)) : 0);
  return 0;
}


// https://github.com/VaHiX/CodeForces/