// Problem: CF 2032 C - Trinity
// https://codeforces.com/contest/2032/problem/C

/*
C. Trinity
Algorithm: Two-pointer technique with sorting
Time Complexity: O(n log n) per test case due to sorting and linear traversal
Space Complexity: O(1) additional space (excluding input array)

The problem asks to make an array such that every triplet of distinct indices forms a non-degenerate triangle.
A key insight is that if we sort the array, for any three elements a[i], a[j], a[k] where i < j < k,
they form a valid triangle if and only if a[i] + a[j] > a[k]. 
We can use two pointers to efficiently count how many operations are needed.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
int t, n, a[200001], ans;

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    sort(a + 1, a + n + 1); // Sort the array to apply two-pointer technique
    ans = n - 1; // Initialize with maximum possible operations (change all but one)
    for (int i = 1, j = 2; i <= n; i++)
      while (j <= n && a[i] + a[i + 1] > a[j]) {
        ans = min(ans, i - 1 + n - j); // Update minimum operations needed
        j++;
      }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/