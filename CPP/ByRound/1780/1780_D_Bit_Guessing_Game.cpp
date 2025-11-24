// Problem: CF 1780 D - Bit Guessing Game
// https://codeforces.com/contest/1780/problem/D

/*
 * Problem: Bit Guessing Game
 * 
 * Algorithm/Techniques: 
 * - Binary search approach using bit manipulation to deduce the hidden number n.
 * - For each bit position, we attempt to subtract 2^b from n and check if the number of set bits decreases.
 * - If the number of set bits decreases, it means the bit at position b was set in the original number.
 * - We use this information to reconstruct the number progressively.
 *
 * Time Complexity: O(log n * log n) = O(log^2 n), where log n is the number of bits.
 *                  In the worst case, we perform at most 30 operations, and each operation involves
 *                  bit manipulation and a small amount of arithmetic.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <iostream>
int main() {
  int t, c, d, r, s;
  std::cin >> t;
  while (t--) {
    std::cin >> c;
    s = d = 0;
    for (int b = 0; c > d; b++)
      std::cout << "- " << (1 << b) << std::endl, std::cin >> r, d += (r >= c),
          s += ((r >= c) + 1) * (1 << b), c = r;
    std::cout << "! " << s << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/