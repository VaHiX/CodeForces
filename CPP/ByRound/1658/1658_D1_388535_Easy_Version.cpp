// Problem: CF 1658 D1 - 388535 (Easy Version)
// https://codeforces.com/contest/1658/problem/D1

/*
 * Problem: Find the secret XOR value 'x' used to transform an array of consecutive integers.
 * Algorithm:
 *   - For each bit position, count how many 0s and 1s exist in the final array.
 *   - The original array was a permutation of [l, l+1, ..., r], so for any bit position:
 *     - If more 1s than 0s in the result, then the original bit at that position was 1.
 *     - Otherwise, it was 0.
 *   - Reconstruct x by setting bits accordingly.
 *
 * Time Complexity: O(B * (r - l + 1)) where B = 31 (number of bits)
 * Space Complexity: O(B * 2) for storing bit counts
 */

#include <cstdio>
#include <vector>
int main() {
  const int B = 31; // Number of bits to process (up to 2^17)
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<std::vector<long>> w(B, std::vector<long>(2, 0)); // w[b][0] = count of 0s, w[b][1] = count of 1s at bit b
    long left, right;
    scanf("%ld %ld", &left, &right);
    for (long p = left; p <= right; p++) {
      long x;
      scanf("%ld", &x);
      // Count bits of each number in the array
      for (long b = 0; b < B; b++, x /= 2) { 
        ++w[b][x % 2]; // Increment count for bit 0 or 1
      }
    }
    long ans(0);
    // Reconstruct the secret value x
    for (long p = 0; p < B; p++) {
      ans |= ((1L << p) * (w[p][1] > w[p][0])); // Set bit p if more 1s than 0s in result
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/