// Problem: CF 1015 A - Points in Segments
// https://codeforces.com/contest/1015/problem/A

/*
 * Problem: Points in Segments
 * Algorithm: Brute Force 
 * Time Complexity: O(n * m) where n is number of segments and m is the upper bound of coordinates
 * Space Complexity: O(m) for the array to mark covered points
 *
 * Task: Given n segments on a line from 1 to m, find all points in [1,m] not covered by any segment.
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <utility>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 200100
#define inf 100000000
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;

bool cmp(pp a, pp b) { return a.first > b.first; }

int main() {
  int i, j, k;
  int n, m;
  int l, r;
  sff(n, m); // Read number of segments and upper bound
  int a[m + 1]; // Array to mark which points are covered
  memset(a, 0, sizeof(a)); // Initialize all values to 0
  for (i = 0; i < n; i++) {
    sff(l, r); // Read segment endpoints
    for (j = l; j <= r; j++)
      a[j]++; // Mark all points in segment as covered
  }
  vector<int> ans; // Vector to store uncovered points
  for (i = 1; i <= m; i++) {
    if (!a[i]) // If point is not covered
      ans.pb(i); // Add to result
  }
  pf(ans.size()); // Print count of uncovered points
  pfs("\n");
  for (i = 0; i < ans.size(); i++)
    pf(ans[i]); // Print uncovered points
  return 0;
}


// https://github.com/VaHiX/codeForces/