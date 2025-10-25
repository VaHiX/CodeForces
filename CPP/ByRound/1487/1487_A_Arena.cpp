// Problem: CF 1487 A - Arena
// https://codeforces.com/contest/1487/problem/A

/*
 * Problem: Arena
 * Description: Given n heroes with initial levels, determine how many of them can possibly become the winner
 *              of a tournament where fights occur between any two heroes. When two heroes fight:
 *              - If their levels are equal, no one wins.
 *              - If their levels are different, the higher-level hero wins and gains 1 level.
 *              A hero becomes the winner if they win at least 10^500 fights.
 *              The task is to count how many heroes can possibly become winners under optimal fight sequences.
 *
 * Algorithm:
 *   - For each test case, find the minimum initial level among all heroes.
 *   - Count how many heroes have this minimum level.
 *   - The number of possible winners = total heroes - count of heroes with minimum level.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(107), cnt(0);  // mn = minimum level, cnt = count of heroes with minimum level
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (a < mn) {         // If current hero's level is less than minimum
        mn = a;             // Update minimum
        cnt = 1;            // Reset count to 1
      } else if (a == mn) { // If current hero's level equals minimum
        ++cnt;              // Increment count
      }
    }
    printf("%ld\n", n - cnt);  // Number of possible winners = total heroes - heroes with min level
  }
}


// https://github.com/VaHiX/codeForces/