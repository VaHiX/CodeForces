// Problem: CF 979 A - Pizza, Pizza, Pizza!!!
// https://codeforces.com/contest/979/problem/A

/*
 * Problem: Shiro's Pizza Cutting
 * Purpose: Determine the minimum number of straight cuts needed to divide a circular pizza
 *          into n + 1 equal slices.
 * 
 * Algorithm:
 * - If n = 0 (only Shiro), we need 0 cuts.
 * - If n = 1 (Shiro + 1 friend), we need 1 cut.
 * - For n >= 2:
 *   - If n+1 is odd, then we need (n+1) cuts.
 *   - If n+1 is even, we need (n+1)/2 cuts.
 * 
 * This is based on the concept that:
 * - To create k equal slices using straight cuts, we need k cuts if k is odd.
 * - If k is even, we can reduce the number of cuts by half by making cuts through
 *   the center, as each cut can split two slices.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll n;
  scanf("%lld", &n);
  ++n; // Now n represents the number of slices (n + 1)
  
  // If n > 1 and n is odd, we need n cuts.
  // Otherwise, we need n / 2 cuts.
  ll res = ((n > 1) && (n & 1)) ? n : (n / 2);
  
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/CodeForces/