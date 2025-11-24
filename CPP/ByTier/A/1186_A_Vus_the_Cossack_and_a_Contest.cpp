// Problem: CF 1186 A - Vus the Cossack and a Contest
// https://codeforces.com/contest/1186/problem/A

#include <cstdio>
int main() {
  long n, m, k;
  scanf("%ld %ld %ld", &n, &m, &k);
  puts((n <= m && n <= k) ? "Yes" : "No");
  return 0;
}
/*
Flowerbox:
Problem: A. Vus the Cossack and a Contest
Purpose: Determine if Vus can award all participants with at least one pen and one notebook.
Algorithm: Simple comparison of required items (n) against available items (m pens, k notebooks).
Time Complexity: O(1) - constant time operation.
Space Complexity: O(1) - only using a fixed number of variables.
*/

// https://github.com/VaHiX/codeForces/