// Problem: CF 1949 K - Make Triangle
// https://codeforces.com/contest/1949/problem/K

/*
K. Make Triangle
Algorithms/Techniques: Greedy algorithm with sorting and binary-like selection
Time Complexity: O(n log n) per test case due to sorting; overall is O(sum of n * log(sum of n))
Space Complexity: O(n) for storing arrays and vectors

The problem requires splitting n integers into three groups of specified sizes such that the sums of each group can form a triangle.
This is possible if and only if the sum of the three sides satisfies the triangle inequality (i.e., no side is greater than or equal to the sum of the other two).
The strategy uses a greedy approach:
1. Sort integers in descending order.
2. For each integer, try placing it into a group that still has capacity and where adding this number keeps that group's sum below or equal to the average of all sums (which is approximated as total_sum / 2).
3. If we can't place an integer into any valid group, return "NO".
4. Otherwise, output the groups.

The key idea is to avoid placing large elements in groups too early so that we still have room for smaller ones to satisfy triangle conditions.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long LL;
typedef double DB;
const int N = 222222;
int n, a[3], f[N];
LL s[N], m, t[3];
vector<int> v[3];

int main() {
  int T, i, j, x, y;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (j = 0; j < 3; j++)
      scanf("%d", a + j);  // Read the required sizes for groups
    for (i = 1; i <= n; i++)
      scanf("%d", f + i);  // Read the numbers to be partitioned
    sort(f + 1, f + n + 1);  // Sort in ascending order
    for (i = 1; i <= n; i++)
      s[i] = s[i - 1] + f[i];  // Compute prefix sums
    m = (s[n] - 1) / 2;  // Estimate maximum allowed value for group sum to ensure triangle inequality
    for (j = 0; j < 3; j++)
      t[j] = 0, v[j].clear();  // Reset group totals and vectors
    y = 1;  // Flag indicating if solution is valid
    for (i = n; i >= 1; i--) {  // Process from largest to smallest element
      x = 1;  // x=1 means no group could take current number
      for (j = 0; j < 3; j++)  // Try placing this number in one of the three groups
        if (a[j] && t[j] + f[i] + s[a[j] - 1] <= m) {  // Check condition to avoid exceeding limit
          v[j].push_back(f[i]);  // Place element into group j
          a[j]--;  // Decrement remaining slots in this group
          t[j] += f[i];  // Update cumulative sum for this group
          x = 0;  // Successfully placed
          break;
        }
      if (x) {
        printf("NO\n");
        y = 0;
        break;
      }
    }
    if (y) {
      printf("YES\n");
      for (j = 0; j < 3; j++) {
        for (i = 0; i < v[j].size(); i++)
          printf("%d ", v[j][i]);
        printf("\n");
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/