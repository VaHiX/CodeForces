// Problem: CF 1180 A - Alex and a Rhombus
// https://codeforces.com/contest/1180/problem/A

/*
 * Problem: A. Alex and a Rhombus
 * Purpose: Compute the number of cells in an n-th order rhombus.
 * Algorithm: Observing the pattern:
 *   - 1st order: 1 cell
 *   - 2nd order: 5 cells (1 + 4)
 *   - 3rd order: 13 cells (5 + 8)
 *   - Each step adds a layer of cells around the previous rhombus.
 *   - The number of cells added forms a sequence:
 *     1, 4, 8, 12, ... which is 4 * (i) for i = 1, 2, ...
 *   - So total = 1 + 4*(1) + 4*(2) + ... + 4*(n-1)
 *     = 1 + 4 * (1 + 2 + ... + (n-1))
 *     = 1 + 4 * ( (n-1)*n / 2 )
 *     = 1 + 2*(n-1)*n
 *   - Simplified formula:
 *     ans = n*n + (n-1)*(n-1);
 *   - Or we can simulate by adding layers.
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 1000100
#define inf 1e18
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;
int main() {
  int i, j, k;
  int n, m;
  sf(n);
  ll ans = 0, p = 1; // p represents the number of cells in current layer
  for (i = 1; i <= n - 1; i++) { // iterate through all layers except final one
    ans += p * 2; // add previous layer's contributions twice (left and right)
    p += 2;       // increment to next layer size
  }
  ans += p; // add the last layer contribution
  pfl(ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/