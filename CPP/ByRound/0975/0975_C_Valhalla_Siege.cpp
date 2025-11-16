// Problem: CF 975 C - Valhalla Siege
// https://codeforces.com/contest/975/problem/C

/*
Algorithm: Prefix Sum + Binary Search (lower_bound)
Time Complexity: O(n + q * log n)
Space Complexity: O(n)

This problem simulates a battle where Ivar's warriors take arrows and get
destroyed. Warriors are arranged in a line, and each warrior has a strength
value. Each minute, Lagertha's army shoots a certain number of arrows. Arrows
hit warriors from left to right until the warrior is destroyed. After all
warriors die, they are revived at the end of the minute.

We use a prefix sum array to compute cumulative strengths.
For each minute, we add the arrows shot to a running total and use binary search
to find the first warrior whose cumulative strength is greater than or equal to
the total arrows shot. This determines how many warriors remain standing.

The key steps:
1. Compute prefix sums of warriors' strengths
2. For each minute:
   a. Add arrows to the total
   b. Find first warrior that can't take all arrows using lower_bound
   c. Adjust index if needed (based on exact match)
   d. Output number of remaining warriors
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 1010101
#define inf 1e18
#define mod 998244353
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
  sff(n, q);
  ll a[n];
  memset(a, 0, sizeof(a));
  for (i = 0; i < n; i++) {
    sf(m);
    if (i > 0)
      a[i] = a[i - 1] + m;
    else
      a[i] = m;
  }
  ll x, arrow = 0;
  for (i = 1; i <= q; i++) {
    sfl(x);
    arrow += x;
    k = lower_bound(a, a + n, arrow) - a;
    if (k >= n)
      pf(n), arrow = 0;
    else {
      if (a[k] > arrow)
        k--;
      if (k == n - 1)
        pf(n), arrow = 0;
      else
        pf(n - k - 1);
    }
    nl;
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/