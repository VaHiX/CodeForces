// Problem: CF 1873 F - Money Trees
// https://codeforces.com/contest/1873/problem/F

/*
 * Problem: F. Money Trees
 * 
 * Purpose: Find the maximum length of a contiguous subarray such that:
 *          1. Each tree's height is divisible by the next tree's height.
 *          2. The total number of fruits collected does not exceed k.
 * 
 * Algorithm: Sliding window technique with careful handling of divisibility condition.
 *            - Use two pointers (start and i) to maintain a valid window.
 *            - When the sum exceeds k, shrink the window from the left.
 *            - When a divisibility condition fails, reset the window starting at the next element.
 * 
 * Time Complexity: O(n) per test case, where n is the number of trees.
 * Space Complexity: O(n) for storing the arrays f and h.
 */

#include <stdio.h>
int f[200005];  // Array to store fruit amounts
int h[200005];  // Array to store tree heights
typedef long long ll;
int n, m, k;

int main() {
  scanf("%d", &n);  // Read number of test cases
  for (int l = 0; l < n; l++) {
    scanf("%d %d", &m, &k);  // Read number of trees and max fruits allowed
    for (int i = 1; i <= m; i++)
      scanf("%d", f + i);  // Read fruit values
    for (int i = 1; i <= m; i++)
      scanf("%d", h + i);  // Read tree heights
    
    ll sum = 0, max = 0, start = 1;  // Initialize sliding window variables
    for (int i = 1; i <= m; i++) {
      sum += f[i];  // Add current tree's fruits to the window sum
      
      // Shrink window from left if sum exceeds k
      while (sum > k)
        sum -= f[start++];
      
      // Update maximum length if current window is larger
      if (i - start + 1 > max)
        max = i - start + 1;
      
      // Check divisibility condition: if current height is not divisible by next height,
      // then we must start a new window from the next element
      if (i != m && h[i] % h[i + 1]) {
        start = i + 1;
        sum = 0;
      }
    }
    printf("%d\n", max);  // Output the maximum valid subarray length
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/