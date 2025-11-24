// Problem: CF 485 D - Maximum Value
// https://codeforces.com/contest/485/problem/D

/*
 * Problem: Maximum Value
 * Purpose: Find the maximum possible remainder when dividing any two elements in the sequence,
 *          where the dividend is greater than or equal to the divisor.
 * 
 * Algorithm:
 * - Sort the array in ascending order.
 * - For each element from the end (largest to smallest), compute the maximum remainder
 *   with all smaller elements, using a two-pointer technique to avoid redundant checks.
 * 
 * Time Complexity: O(n log n + n^2) in worst case, but optimized with two pointers to roughly O(n^2 / 2)
 * Space Complexity: O(1) - only a few variables used, not counting input array
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
const int maxn = 200010;
int n, a[maxn] = {0}, maxx, j, ans = 0;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  sort(a + 1, a + n + 1);  // Sort array in ascending order
  j = n - 1;               // Initialize j to second last element
  for (int i = n; i > 1; i--) {  // Iterate from largest to second element
    maxx = 0;              // Reset max remainder for current i
    while (j >= 1 && (a[i] % a[j] >= maxx)) {  // While j is valid and remainder can improve
      maxx = a[i] % a[j];  // Update max remainder
      j--;                 // Move j to smaller element
    }
    ans = max(ans, maxx);  // Update global answer
    j++;                   // Move j back to previous position
    if (j >= i)            // Ensure j doesn't go beyond i
      j = i - 1;
  }
  printf("%d", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/