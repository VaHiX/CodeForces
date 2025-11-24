// Problem: CF 839 B - Game of the Rows
// https://codeforces.com/contest/839/problem/B

/*
 * Problem: Game of the Rows
 * Purpose: Determine if soldiers from different groups can be seated in an airplane
 *          such that no two soldiers from different groups are in neighboring seats.
 * 
 * Algorithm:
 * 1. For each group of soldiers, compute how many 4-person, 2-person, and 1-person
 *    blocks can be formed from their count.
 * 2. Calculate maximum number of 2-seat pairs (each pair can fit two 1-person groups)
 *    and 1-seat singles that can be placed.
 * 3. Validate whether all soldiers can be assigned to seats without violating
 *    the neighbor constraint.
 * 
 * Time Complexity: O(k)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  long f(0), g(0), h(0); // f: number of 4-person groups, g: number of 2-person groups, h: number of 1-person groups
  for (long p = 0; p < k; p++) {
    long a;
    scanf("%ld", &a);
    f += a / 4;         // Count how many complete 4-seater groups
    a %= 4;
    g += a / 2;         // Count how many complete 2-seater groups
    a %= 2;
    h += a;             // Remaining 1-seater groups
  }
  long pairs = 2 * n + ((n >= f) ? 1 : 2) * (n - f); // Total possible pairs of adjacent seats in n rows
  long singles = (n >= f) * (n - f) + (pairs > g) * (pairs - g); // Number of available single seats
  h += 2 * (g > pairs) * (g - pairs); // Additional 1-seaters if 2-person groups exceed pair capacity
  if (h > singles) {  // If we have more 1-seaters than available single seats, impossible
    puts("NO");
    return 0;
  }
  puts("YES");
  return 0;
}


// https://github.com/VaHiX/CodeForces/