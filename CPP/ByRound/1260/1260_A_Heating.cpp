// Problem: CF 1260 A - Heating
// https://codeforces.com/contest/1260/problem/A

/*
 * Problem: Heating
 * Algorithm: Greedy with mathematical optimization
 * Time Complexity: O(n), where n is the number of rooms
 * Space Complexity: O(1)
 *
 * For each room, we need to distribute 'sum_i' sections among at most 'c_i' radiators
 * such that total cost (sum of squares of section counts) is minimized.
 * 
 * Strategy:
 * 1. Distribute sections as evenly as possible among the radiators.
 * 2. If sum % count != 0, some radiators will have one more section than others.
 * 3. Calculate cost using formula derived from this optimal distribution:
 *    - d = sum / count (base number of sections per radiator)
 *    - m = sum % count (number of radiators with one extra section)
 *    - ans = (count - m) * d^2 + m * (d + 1)^2
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  while (n--) {
    long cnt, s;
    scanf("%ld %ld", &cnt, &s);
    long d = (s / cnt);            // Base number of sections per radiator
    long m = (s % cnt);            // Number of radiators with one extra section
    long ans = (cnt - m) * d * d + m * (d + 1) * (d + 1);  // Compute minimum cost
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/