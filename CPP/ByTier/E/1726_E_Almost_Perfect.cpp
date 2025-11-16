// Problem: CF 1726 E - Almost Perfect
// https://codeforces.com/contest/1726/problem/E

/*
 * Problem: Count the number of "almost perfect" permutations of length n.
 * 
 * An almost perfect permutation satisfies: for all i, |p[i] - p^{-1}[i]| <= 1.
 * This means each element is at most one position away from its value in the inverse permutation.
 * 
 * Algorithm:
 * - Precompute factorials and inverse factorials for fast modular arithmetic.
 * - Use dynamic programming to compute base count of almost perfect permutations.
 * - Then, add corrections for cases involving cycles of length 4 that were overcounted.
 * 
 * Time Complexity: O(n) preprocessing + O(n) per query
 * Space Complexity: O(n)
 */

#include <cstdio>
#define P 998244353
int i, T, n, f[300005], I[300005], C, ans;

int main() {
  // Precompute factorials and inverse factorials
  f[0] = f[1] = I[1] = 1;
  for (i = 2; i <= 300000; i++)
    f[i] = (f[i - 1] + 1ll * (i - 1) * f[i - 2]) % P,  // DP recurrence for f[i]
    I[i] = 1ll * (P - P / i) * I[P % i] % P;  // Efficiently compute modular inverse

  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n), C = 1, ans = f[n];  // Initialize C = 1 and ans = base count
    
    // Iterate over number of 4-cycles that can be formed
    for (i = 1; i <= n >> 2; i++)
      C = 1ll * C * (n - (i << 2) + 4) % P * (n - (i << 2) + 3) % P *  // Multiply by combinations of 4 elements
          (n - (i << 2) + 2) % P * (n - (i << 2) + 1) % P *  // These are combinations of 4 elements from remaining
          I[n - (i << 1) + 1] % P * I[n - (i << 1) + 2] % P * I[i] % P,  // Apply modular inverse to count combinations
      ans = (ans + 1ll * C * f[n - (i << 2)]) % P;  // Add corrected term to total count
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/