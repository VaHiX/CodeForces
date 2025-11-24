// Problem: CF 457 B - Distributed Join
// https://codeforces.com/contest/457/problem/B

/*
 * Problem: Distributed Join
 * 
 * Purpose: 
 *   Given two tables A and B, each partitioned across multiple clusters,
 *   determine the minimum number of network operations to ensure that
 *   every row from A and every row from B exist in at least one partition
 *   such that each row of A can be joined with every row of B.
 * 
 * Approach:
 *   - The minimal number of operations is achieved by transferring rows to
 *     a single partition in each cluster.
 *   - For table A, we compute the cost of moving all rows to one of the
 *     partitions of A or to a partition of B (depending on which is cheaper).
 *   - Similarly for table B.
 *   - The final answer is the minimum of these two costs.
 * 
 * Time Complexity: O(m + n)
 * Space Complexity: O(1)
 * 
 * Algorithms/Techniques:
 *   - Greedy approach with prefix sum calculation
 *   - Optimization to minimize total copy operations
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
#define ll long long
const int N = 100000;
int a[N], b[N];
int max(int a, int b) { return a > b ? a : b; }
ll min(ll a, ll b) { return a < b ? a : b; }
int main() {
  int i, n, m, f, xa, xb;
  ll sa, sb, ua, ub, ra, rb, ans;
  xa = xb = 0;
  ua = ub = ra = rb = sa = sb = 0;
  scanf("%d%d", &n, &m);
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]), sa += a[i], xa = max(xa, a[i]);  // Compute total rows in A and max partition size
  for (i = 0; i < m; i++)
    scanf("%d", &b[i]), sb += b[i], xb = max(xb, b[i]);  // Compute total rows in B and max partition size
  for (f = i = 0; i < n; i++) {
    if (a[i] < sb)  // If partition i in A has fewer rows than total B
      ra += a[i];   // Add all rows in A's partition to the cost
    else
      ra += sb, f = 1;  // Move all B rows to A's partition; flag to indicate we moved
  }
  if (!f)  // If none of A's partitions had more than total B rows
    ra += sb - xa;  // Add the extra rows needed to make up for the difference
  for (f = i = 0; i < m; i++) {
    if (b[i] < sa)  // If partition i in B has fewer rows than total A
      rb += b[i];   // Add all rows in B's partition to the cost
    else
      rb += sa, f = 1;  // Move all A rows to B's partition; flag to indicate we moved
  }
  if (!f)  // If none of B's partitions had more than total A rows
    rb += sa - xb;  // Add the extra rows needed to make up for the difference
  ans = min(ra, rb);  // Choose the minimum cost operation
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/