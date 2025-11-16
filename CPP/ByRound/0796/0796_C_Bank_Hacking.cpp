// Problem: CF 796 C - Bank Hacking
// https://codeforces.com/contest/796/problem/C

/*
 * Problem: C. Bank Hacking
 * 
 * Purpose: Determine the minimum strength of Inzane's computer needed to hack all banks.
 * 
 * Approach:
 * - The graph is a tree (n nodes, n-1 edges).
 * - A bank can be hacked if it's neighboring an offline bank and its strength is <= computer strength.
 * - Each time a bank is hacked:
 *   - It becomes offline.
 *   - All neighboring and semi-neighboring online banks have their strength increased by 1.
 * - Key observation:
 *   - If we start hacking from a node with maximum strength, and the graph has a structure where
 *     a unique maximum strength node is connected to all other maximum strength nodes, 
 *     then we might be able to reduce the required computer strength to just the max strength.
 *   - Otherwise, we need to increase the strength by 1.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n), maxn(n), maxsn(n);
  long mx(-1e9), whichMax(-1);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    if (a[p] > mx) {
      mx = a[p];
      whichMax = p;
    }
  }
  long cntMax(0), cntMaxB(0);
  for (long p = 0; p < n; p++) {
    cntMax += (a[p] == mx);
    cntMaxB += (a[p] == (mx - 1));
  }
  for (long p = 1; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    --x;
    --y;
    if (a[x] == mx) {
      ++maxn[y];
    } else if (a[x] == mx - 1) {
      ++maxsn[y];
    }
    if (a[y] == mx) {
      ++maxn[x];
    } else if (a[y] == mx - 1) {
      ++maxsn[x];
    }
  }
  long ans(mx + 2);
  if (cntMax == 1 && (n == 1 || maxsn[whichMax] == cntMaxB)) {
    ans = mx;
  } else {
    for (long p = 0; p < n; p++) {
      if ((a[p] == mx && maxn[p] == cntMax - 1) || (maxn[p] == cntMax)) {
        ans = mx + 1;
        break;
      }
    }
  }
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/