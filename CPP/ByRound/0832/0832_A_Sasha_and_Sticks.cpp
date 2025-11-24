// Problem: CF 832 A - Sasha and Sticks
// https://codeforces.com/contest/832/problem/A

/*
 * Code Purpose:
 * Determine if Sasha wins the stick game based on the number of sticks (n) and sticks crossed out per turn (k).
 * The game alternates between Sasha and Lena, with Sasha going first.
 * Sasha wins if he makes strictly more moves than Lena.
 *
 * Algorithm:
 * - Calculate total number of moves possible: n / k
 * - If this number is odd, Sasha makes the last move and thus wins.
 * - This is determined by checking if (n / k) % 2 == 1.
 *
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only using a fixed amount of space
 */

#include <stdint.h>
#include <iostream>

int main() {
  int64_t n, k;
  std::cin >> n >> k;
  int64_t win = (n / k) % 2;  // Determine if total moves is odd (Sasha wins)
  std::cout << (win ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/