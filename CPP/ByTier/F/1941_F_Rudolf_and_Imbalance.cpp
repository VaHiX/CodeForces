// Problem: CF 1941 F - Rudolf and Imbalance
// https://codeforces.com/contest/1941/problem/F

/*
Code Purpose:
This solution aims to minimize the "imbalance" of a set of problems after possibly adding one new problem. 
The imbalance is defined as the maximum difference between consecutive elements in the sorted array of complexities.
The approach sorts the differences between existing elements, then tries to insert an optimal new element to reduce the maximum gap.

Algorithms/Techniques:
- Sorting differences to identify the largest gaps
- Binary search using lower_bound to efficiently find candidates
- Brute-force checking a small window around the binary search result to verify candidates
- Optimization by removing duplicates in the function array

Time Complexity: O(n log n + m * k * log k) in the worst case (but effectively reduced due to filtering and small windows)
Space Complexity: O(n + m + k) for the arrays storing input elements
*/

#include <stdio.h>

typedef long long LL;
#include <algorithm>

using namespace std;
#define P1 972663749
#define P2 911382323
#define MOD 998244353
bool rcmp(int a, int b) { return a > b; }
struct VNode {
  int v, i;
  bool operator<(const VNode &b) const { return v > b.v; }
};
int as[1 << 20];        // Array to store initial problem complexities
int bs[1 << 20];        // Array to store model complexities
int cs[1 << 20];        // Array to store function complexities
VNode ds[1 << 20];      // Array to store differences and their indices
int main() {
  int n, i, m, k, md, cd, j, v, v1, v2, i1, i2, mi;
  int vv;
  LL s, e;
  int tc;
  scanf("%d", &tc);
  while (tc--) {
    scanf("%d %d %d", &n, &m, &k);
    for (i = 0; i < n; i++)
      scanf("%d", &as[i]);
    for (i = 0; i < m; i++)
      scanf("%d", &bs[i]);
    for (i = 0; i < k; i++)
      scanf("%d", &cs[i]);
    // Compute differences between consecutive elements and store in ds
    for (i = 0; i < n - 1; i++) {
      ds[i].v = as[i + 1] - as[i];
      ds[i].i = i;
    }
    sort(ds, ds + (n - 1));  // Sort differences in descending order to find the max difference first

    // If there's only one difference, the answer is that difference
    if (n - 1 > 1 && ds[0].v == ds[1].v)
      printf("%d\n", ds[0].v);
    else {
      i = ds[0].i;  // Index of the maximum difference
      s = as[i];    // Start of the interval with max difference
      e = as[i + 1]; // End of the interval with max difference

      // Remove duplicates from function complexities
      sort(cs, cs + k);
      for (j = 0, i = 0; i < k; i++) {
        if (i && cs[i] == cs[i - 1])
          continue;
        cs[j++] = cs[i];
      }
      k = j;

      md = ds[0].v;  // Initialize minimum imbalance with current max difference

      // Try every model to combine with functions to form a new problem
      for (i = 0; i < m; i++) {
        v = bs[i];
        v1 = (s + e) / 2 - v;  // Target value to place between s and e
        mi = lower_bound(cs, cs + k, v1) - cs;  // Get the position in sorted function complexities
        // Check small window around mi to find the best placement
        for (j = mi - 8; j <= mi + 8; j++) {
          if (j < 0 || j >= k)
            continue;
          vv = v + cs[j];  // New problem complexity 
          if (vv <= s || vv >= e)  // If it's outside the current interval, skip
            continue;
          cd = max(vv - s, e - vv);  // Calculate new imbalance if this placement is used
          md = min(md, cd);  // Update minimum imbalance
        }
      }
      
      // Also consider the second best difference if more than one difference
      if (n - 1 > 1)
        md = max(md, ds[1].v);
      printf("%d\n", md);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/