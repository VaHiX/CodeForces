// Problem: CF 1854 C - Expected Destruction
// https://codeforces.com/contest/1854/problem/C

/*
 * Problem: Expected Destruction
 *
 * Purpose:
 *   Given a set S of n distinct integers between 1 and m, we simulate a process
 * where:
 *   - Each second, a random element x is removed from S.
 *   - If x+1 <= m and x+1 is not in S, then x+1 is added to S.
 *   We are to compute the expected number of seconds until S becomes empty.
 *
 * Algorithm:
 *   - Dynamic Programming with overlapping subproblems.
 *   - f[i][j] represents the expected number of steps to eliminate all elements
 *     in the interval [i, j) where i and j are consecutive "boundaries" of
 * active elements.
 *   - The key recurrence uses probabilistic analysis:
 *     f[i][j] = (f[i][j+1] + f[i+1][j] + 1) * 0.5 (mod P), where 0.5 is
 * represented as (mod+1)>>1.
 *
 * Time Complexity: O(m^2)
 * Space Complexity: O(m^2)
 */

#include <stdio.h>

const long long mod = 1000000007;
int n, m,
    a[502]; // a[502] stores the elements of the set S + one dummy value at end
long long f[502][502],
    answer; // f[i][j] stores expected steps for interval [i, j)
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", a + i);
  a[n + 1] = m + 1; // dummy value to simplify boundary logic

  // Fill DP table from right to left and top to bottom
  for (int i = m + 1; i; i--)        // for each starting point i (backward)
    for (int j = m + 1; j >= i; j--) // for each ending point j (backward)
      if (i == j)
        f[i][j] = 0; // base case: no elements to process
      else if (j == m + 1)
        f[i][j] =
            m + 1 -
            i; // if j is beyond m, directly compute steps to fill in the range
      else
        f[i][j] = (f[i][j + 1] + f[i + 1][j] + 1) * (mod + 1 >> 1) %
                  mod; // recurrence relation

  // Sum up contributions from each element in the initial set S
  for (int i = 1; i <= n; i++)
    answer = (answer + f[a[i]][a[i + 1]]) % mod;
  printf("%lld\n", answer);
}

// https://github.com/VaHiX/CodeForces/