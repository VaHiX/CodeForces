// Problem: CF 1835 E - Old Mobile
// https://codeforces.com/contest/1835/problem/E

/*
 * Problem: E. Old Mobile
 * Purpose: Calculate the expected number of button presses needed to type a number
 *          on a mobile device with m+1 buttons (digits 0 to m-1 and a backspace)
 *          where only k of the digits from 0 to m-1 are actually used in the target number.
 *          
 * Algorithm:
 *   - Precompute factorials, modular inverses, and prefix sums for efficient calculation
 *   - Use dynamic programming + linearity of expectation to find the expected value
 *   - The solution involves calculating probabilities and costs based on how many
 *     unique digits are present in the target number
 *
 * Time Complexity: O(m)
 * Space Complexity: O(m)
 */
#include <stdio.h>
#define M 1000
#define MD 1000000007
int vv[M + 3], ff[M + 3], gg[M + 3], hh[M + 3];

// Precompute factorials, modular inverses and prefix sums for use in main logic
void init() {
  int i;
  ff[0] = gg[0] = 1, hh[0] = 0;
  for (i = 1; i <= M + 2; i++) {
    // Compute modular inverse of i using extended Euclidean algorithm
    vv[i] = i == 1 ? 1 : (long long)vv[i - MD % i] * (MD / i + 1) % MD;
    // Compute factorial of i
    ff[i] = (long long)ff[i - 1] * i % MD;
    // Compute product of modular inverses up to i
    gg[i] = (long long)gg[i - 1] * vv[i] % MD;
    // Prefix sum of modular inverses
    hh[i] = (hh[i - 1] + vv[i]) % MD;
  }
}

int main() {
  static char used[M]; // Track which digits are used in the input number
  int n, m, k, i, a, ans;
  init(); // Initialize precomputed values

  scanf("%d%d", &n, &m); // Read input: length of number and base m
  k = 0; // Count of unique digits in the target number

  // Mark used digits and count the number of unique digits
  for (i = 0; i < n; i++) {
    scanf("%d", &a);
    if (!used[a])
      used[a] = 1, k++;
  }

  // Main formula to compute expected number of button presses
  ans = ((long long)(m + 2) * (k + 1) % MD * vv[k + 2] % MD - hh[k + 1]) % MD * 2 % MD;

  // Subtract contribution from the remaining unused digits
  ans = (ans - (long long)ff[m - k + 1] * gg[m + 1] % MD * (m - k) % MD) % MD;

  // Subtract one more contribution term
  ans = (ans - vv[m + 1]) % MD;

  // Add n (base cost of typing n digits)
  ans = (ans + n) % MD;
  
  // Ensure result is positive
  if (ans < 0)
    ans += MD;
  
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/