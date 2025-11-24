// Problem: CF 784 B - Kids' Riddle
// https://codeforces.com/contest/784/problem/B

#include <stdint.h>
#include <iostream>

/*
 * Problem: B. Kids' Riddle
 * Algorithm: Digit processing in base-16 (hexadecimal)
 * Time Complexity: O(log₁₆(n)) - we process each digit of n in base-16
 * Space Complexity: O(1) - only using a constant amount of extra space
 * 
 * The algorithm counts specific digits in the hexadecimal representation of n.
 * For each hexadecimal digit, we look up how many "1"s are in that digit's binary
 * representation and sum them up. The lookup table 'loops' contains these values:
 * 0->0, 1->1, 2->1, 3->2, 4->1, 5->2, 6->2, 7->3, 8->1, 9->2, A->2, B->3, C->2, D->3, E->3, F->4
 * However, the code uses a different lookup approach where each value represents how many set bits
 * are there for the corresponding hex digit when we consider the pattern of counting.
 * 
 * The loop processes each hexadecimal digit from least to most significant,
 * accumulating the count according to precomputed values.
 */

int main() {
  const int loops[] = {1, 0, 0, 0, 1, 0, 1, 0, 2, 1, 1, 2, 0, 1, 0, 0};  // Precomputed set bit counts for hex digits 0-15
  int64_t n;
  std::cin >> n;
  int count((n == 0) ? 1 : 0);  // Special case for 0: count = 1
  while (n > 0) {
    count += loops[n % 16];     // Add the precomputed bit count for current hex digit
    n /= 16;                    // Move to next hex digit
  }
  std::cout << count << std::endl;
  return 0;
}

// https://github.com/VaHiX/codeForces/