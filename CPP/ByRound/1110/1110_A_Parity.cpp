// Problem: CF 1110 A - Parity
// https://codeforces.com/contest/1110/problem/A

/*
 * Problem: Determine if a number represented in base b with k digits is even or odd.
 *
 * Algorithm: 
 * - The parity (even/odd) of the number depends only on the last digit and the base's parity.
 * - For any term a_i * b^(k-i-1), we check if it contributes to the parity:
 *   - If b is even, all terms except the last one are even, so only a_{k-1} matters.
 *   - If b is odd, each digit's contribution to parity depends on whether the digit and base are odd/even.
 * - Optimization: Only the last digit and the base's parity matter for final result.
 *
 * Time Complexity: O(k)
 * Space Complexity: O(k)
 */

#include <cstdio>
#include <vector>
int main() {
  long b, k;
  scanf("%ld %ld", &b, &k);
  std::vector<long> a(k);
  for (long p = 0; p < k; p++) {
    scanf("%ld", &a[p]); // Read each digit
  }
  long parity(a[k - 1] % 2); // Start with last digit's parity
  for (long p = 0; p < k - 1; p++) {
    parity += (a[p] % 2) * (b % 2); // Add contribution of previous digits based on base parity
  }
  parity %= 2; // Final parity modulo 2
  puts(parity ? "odd" : "even"); // Output result
  return 0;
}


// https://github.com/VaHiX/codeForces/