// Problem: CF 1043 A - Elections
// https://codeforces.com/contest/1043/problem/A

/*
 * Problem: Elections
 * Purpose: Determine the smallest number of votes per student (k) that allows Awruk to win
 *          by getting strictly more votes than Elodreip.
 *
 * Algorithm/Techniques:
 * - Greedy approach with binary search or linear search (since n <= 100)
 * - For each candidate k >= max(a_i), compute total votes for Elodreip and Awruk
 * - Find minimum k such that Awruk's votes > Elodreip's votes
 *
 * Time Complexity: O(n^2) in worst case due to checking all possible k values up to 2*max(a_i)
 * Space Complexity: O(1) - only using a few variables regardless of input size
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long k(0), t(0), m(n);
  while (m--) {
    long a;
    scanf("%ld", &a);
    t += a;                    // sum of all votes for Elodreip
    k = (k > a) ? k : a;       // find maximum votes any single student gives to Elodreip
  }
  long ans = 1 + 2 * t / n;    // initial estimate based on average votes per student
  ans = (ans >= k) ? ans : k;  // ensure k is at least the max vote count for any one student
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/