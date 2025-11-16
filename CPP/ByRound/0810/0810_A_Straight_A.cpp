// Problem: CF 810 A - Straight <<A>>
// https://codeforces.com/contest/810/problem/A

/*
 * Purpose: Calculate the minimum number of additional marks to be added
 *          so that the average of all marks rounds up to k.
 *          
 * Algorithm: 
 *   - We want the final average to round up to k.
 *   - The rounding rule is: if the average is x.5, it rounds up (e.g., 7.5 -> 8).
 *   - To achieve this, we try to find the minimal number of extra marks,
 *     each in the range [1, k], such that when added, the average rounds to k.
 *   - We calculate how much the sum needs to increase so that:
 *     (sum + x) / (n + y) >= k - 0.5 (to ensure it rounds up to k)
 *   - Rearranging algebraically to solve for the minimal number of marks needed.
 *   
 * Time Complexity: O(n) - single pass through the input array
 * Space Complexity: O(1) - only using a few variables
 */
#include <cstdio>
int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  double s(0);  // s is the current sum of marks
  for (int p = 0; p < n; p++) {
    int x;
    scanf("%d", &x);
    s += x;
  }
  // Compute the minimal number of marks needed using derived formula
  double da = 2 * (n * (k - 0.5) - s);
  long a = (da > 0) ? da : 0;  // Ensure non-negative result
  if (a < da) {                // Handle rounding correctly
    ++a;
  }
  printf("%ld\n", a);
  return 0;
}


// https://github.com/VaHiX/CodeForces/