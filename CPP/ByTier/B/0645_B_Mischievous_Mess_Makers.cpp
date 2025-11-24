// Problem: CF 645 B - Mischievous Mess Makers
// https://codeforces.com/contest/645/problem/B

#include <stdint.h>
#include <iostream>

/*
 * Code Purpose:
 * This program computes the maximum possible "messiness" of a cow arrangement
 * after performing at most k swaps. Messiness is defined as the number of
 * inversions in the sequence of cow labels.
 *
 * The key insight is that to maximize inversions, we want to reverse the order
 * of the cows as much as possible. However, due to constraints, we can only make
 * up to k swaps.
 *
 * Algorithm:
 * - If k >= n/2, we can fully reverse the array, achieving maximum inversions.
 * - Otherwise, we calculate the maximum inversions obtainable in k swaps.
 *
 * Time Complexity: O(1) - Constant time operations.
 * Space Complexity: O(1) - Only uses a constant amount of space.
 */

int main() {
  int64_t n, k;
  std::cin >> n >> k;
  if (k >= n / 2) {
    // If we can make at least n/2 swaps, we can reverse the whole array
    // Maximum inversions = n * (n - 1) / 2 (total possible inversions)
    std::cout << (n * (n - 1) / 2) << std::endl;
  } else {
    // Otherwise, compute the maximum inversions achievable in k swaps
    // Formula derived from optimal swap strategy for maximizing inversions
    std::cout << (k * (2 * n - 2 * k - 1)) << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/