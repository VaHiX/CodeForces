// Problem: CF 899 D - Shovel Sale
// https://codeforces.com/contest/899/problem/D

/*
 * Problem: D. Shovel Sale
 * 
 * Purpose: Find the number of pairs of shovels such that their total cost ends 
 *          with the maximum possible number of nines.
 * 
 * Algorithm: 
 * 1. Determine the maximum number of trailing 9s possible for pairs of shovels.
 *    This is found by iteratively building numbers of the form 9, 99, 999, etc.
 *    until the maximum sum (2*n - 1) is exceeded.
 * 2. For each valid sum (of form mx+1, 2*(mx+1), ...) that can be formed:
 *    - Compute the range of valid pairs (i, j) where i + j = sum
 *    - Count how many such pairs exist where i < j and both are within [1, n]
 * 
 * Time Complexity: O(log n) - The loop for determining mx runs in log time.
 * Space Complexity: O(1) - Only a few variables are used.
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll n;
  scanf("%lld", &n);
  ll mx(0);
  // Build the maximum number of trailing 9s possible (9, 99, 999, ...)
  while (10 * mx + 9 <= 2 * n - 1) {
    mx = 10 * mx + 9;
  }
  ll cnt(0);
  // Iterate over all valid sums that end in trailing 9s
  for (ll p = mx; p <= 2 * n - 1; p += mx + 1) {
    // left: starting index of valid pair (i)
    ll left = (p - n > 1) ? (p - n) : 1;
    // right: ending index of valid pair (j = p - i)
    ll r = p - left;
    // Count valid pairs in range [left, r] where i < j and i + j = p
    cnt += (r - left + 1) / 2;
  }
  printf("%lld", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/