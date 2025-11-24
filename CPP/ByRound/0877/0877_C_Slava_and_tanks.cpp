// Problem: CF 877 C - Slava and tanks
// https://codeforces.com/contest/877/problem/C

/*
Purpose: This code solves the problem of destroying all tanks on a 1xN map using the minimum number of bombs.
         The tanks move to adjacent cells upon first hit, and are destroyed on second hit.
         The approach involves a specific bombing sequence to ensure all possible tank positions are covered.

Algorithms/Techniques: Greedy strategy to minimize bomb usage by hitting cells in a specific order:
                       - First, hit all even-indexed cells (2, 4, 6, ...)
                       - Then, hit all odd-indexed cells (1, 3, 5, ...)
                       - Finally, hit all even-indexed cells again (2, 4, 6, ...)

Time Complexity: O(n) - We iterate through the cells a constant number of times.
Space Complexity: O(1) - Only a constant amount of extra space is used.
*/

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 501010
#define inf 1e9
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
#define pp pair<ll, ll>
using namespace std;

int main() {
  int i, j, k;
  int n, m, l;
  sf(n);
  int even = n / 2, odd = n / 2 + n % 2;
  pf(2 * even + odd), nl;
  // First, bomb all even-indexed cells (2, 4, 6, ...)
  for (i = 2; i <= n; i += 2)
    pf(i), pfs(" ");
  // Then, bomb all odd-indexed cells (1, 3, 5, ...)
  for (i = 1; i <= n; i += 2)
    pf(i), pfs(" ");
  // Finally, bomb all even-indexed cells again (2, 4, 6, ...)
  for (i = 2; i <= n; i += 2)
    pf(i), pfs(" ");
  return 0;
}


// https://github.com/VaHiX/CodeForces/