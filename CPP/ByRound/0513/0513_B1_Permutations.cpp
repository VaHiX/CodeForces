// Problem: CF 513 B1 - Permutations
// https://codeforces.com/contest/513/problem/B1

/*
 * Problem: B1. Permutations
 * 
 * Purpose:
 *   This code finds the m-th lexicographically smallest permutation of length n
 *   that achieves the maximum possible value of f(p), where f(p) is defined as
 *   the sum of indices (1-based) of elements in the permutation.
 *
 * Algorithm:
 *   - The key insight is that to maximize f(p), we want to place larger numbers
 *     earlier in the permutation (since they contribute more to the sum).
 *   - However, among all permutations achieving the maximum f(p), we want the
 *     m-th lexicographically smallest one.
 *   - This is handled by interpreting m as a binary number of length n - 1,
 *     where each bit determines whether the next smallest element is appended
 *     to the left or right of the current result.
 *   - The construction is done recursively using bit manipulation.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Techniques:
 *   - Bit manipulation to determine the order of element insertion
 *   - Greedy approach with binary representation to generate required permutation
 */

#include <cstdio>
#include <vector>
int main() {
  long long n, m;
  scanf("%lld %lld", &n, &m);
  std::vector<bool> binary(n);  // Stores binary representation of (m-1)
  std::vector<int> perm(n);     // Result permutation
  int l(0), r(n - 1);           // Left and right pointers for building permutation
  --m;                          // Convert to 0-based indexing

  // Convert m to binary representation of length n-1
  for (int p = n - 2; p >= 0; p--) {
    binary[p] = m % 2;  // Extract least significant bit
    m /= 2;             // Shift right
  }

  // Build the permutation using binary bits
  for (int p = 0; p < n; p++) {
    if (binary[p]) {
      // If bit is 1, place the p+1 element on the right
      perm[r--] = p + 1;
    } else {
      // If bit is 0, place the p+1 element on the left
      perm[l++] = p + 1;
    }
  }

  // Output the permutation
  for (int p = 0; p < n; p++) {
    printf("%d ", perm[p]);
  };
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/