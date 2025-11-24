// Problem: CF 746 D - Green and Black Tea
// https://codeforces.com/contest/746/problem/D

/*
 * Problem: D. Green and Black Tea
 * 
 * Purpose: To determine the order of brewing tea bags such that Innokentiy drinks exactly n cups,
 *          where each cup is either green or black tea, and no same type of tea is consumed more than k times in a row.
 * 
 * Approach:
 * - Greedily build the sequence by prioritizing the type of tea with higher count (b), but respecting the constraint k.
 * - If the number of black teas (b) exceeds the maximum allowed consecutive consumption (i.e., (a + 1) * k), it's impossible.
 * - Otherwise, alternate between the two types, giving preference to the more abundant type, but ensuring no more than k consecutive same types.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * 
 * Algorithms/Techniques:
 * - Greedy algorithm
 * - Simulation approach
 */

#include <stdint.h>
#include <iostream>

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t n, k, a, b;
  std::cin >> n >> k >> a >> b;
  int64_t count(0);
  char gc('G'), bc('B');
  if (a > b) {
    // Ensure 'a' represents the smaller count to simplify logic
    int64_t t = a;
    a = b;
    b = t;
    char u = gc;
    gc = bc;
    bc = u;
  }
  if (b > (a + 1) * k) {
    // Impossible case: even if we place all green teas with maximum allowed black teas between them,
    // we still couldn't fit all black teas
    std::cout << "NO" << std::endl;
  } else {
    // Build the sequence greedily
    for (int64_t p = 0; p < n; p++) {
      if (b > a && count < k) {
        // Use black tea (bc) because there are more black teas left,
        // and we haven't exceeded the limit k for consecutive same type
        std::cout << bc;
        --b;
        ++count;
      } else {
        // Switch to green tea (gc) or reset counter
        std::cout << gc;
        --a;
        count = 0; // Reset consecutive count
      }
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/