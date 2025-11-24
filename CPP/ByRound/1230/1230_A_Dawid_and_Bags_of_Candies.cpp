// Problem: CF 1230 A - Dawid and Bags of Candies
// https://codeforces.com/contest/1230/problem/A

/*
A. Dawid and Bags of Candies
Algorithms/Techniques: Bitmask Enumeration
Time Complexity: O(1) - Since we iterate through at most 2^4 = 16 combinations
Space Complexity: O(1) - Only using a fixed size array and variables

The problem asks whether we can distribute 4 bags of candies between two friends such that 
each friend gets the same total number of candies. This is equivalent to partitioning the 4 elements
into two subsets with equal sums. We use bitmask enumeration to try all possible ways to assign
each bag to one of the two friends and check if any assignment results in equal sums.
*/

#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 110
#define inf 1e18
#define mod 100000007
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
  int n, m, q;
  int a[4];
  for (i = 0; i < 4; i++)
    sf(a[i]);
  for (i = 1; i <= 15; i++) { // Iterate through all non-empty subsets except the full set
    int x = 0, y = 0;
    for (j = 0; j < 4; j++) {
      if ((1 << j) & i) // If j-th bit is set in i, add a[j] to x
        x += a[j];
      else // Otherwise, add a[j] to y
        y += a[j];
    }
    if (x == y) { // Check if the two subsets have equal sums
      pfs("YES");
      return 0;
    }
  }
  pfs("NO");
  return 0;
}


// https://github.com/VaHiX/codeForces/