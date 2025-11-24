// Problem: CF 818 B - Permutation Game
// https://codeforces.com/contest/818/problem/B

/*
 * Problem: Permutation Game
 * 
 * Algorithm:
 * - The game involves children standing in a circle, with each child having a number
 *   indicating how many steps to move clockwise.
 * - We are given the sequence of leaders at the beginning of each step.
 * - The goal is to reconstruct a valid permutation of numbers from 1 to n that
 *   produces the given sequence of leaders.
 * 
 * Approach:
 * 1. For each consecutive pair of leaders, compute the number of steps between them
 *    (considering the circular arrangement).
 * 2. Use this information to infer values in the permutation.
 * 3. Assign remaining unused numbers to empty positions.
 * 
 * Time Complexity: O(n + m)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Simulation with modular arithmetic for circular indexing
 * - Greedy assignment of remaining values
 */

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(n + 1, 0);           // To store the permutation a[1..n]
  std::vector<bool> b(n + 1, 0);           // To track which values are already assigned
  std::vector<long> lead(m, 0);            // Input sequence of leaders
  for (long p = 0; p < m; p++) {
    scanf("%ld", &lead[p]);
  }
  bool possible(true);
  // Process each pair of consecutive leaders to deduce values in the permutation
  for (long p = 1; p < m; p++) {
    long diff = lead[p] - lead[p - 1];     // Difference in positions
    if (diff <= 0) {
      diff += n;                           // Wrap around if needed (circular)
    }
    // If this value is already used and is inconsistent, no solution
    if (b[diff] && a[lead[p - 1]] != diff) {
      possible = false;
      break;
    }
    b[diff] = 1;                           // Mark this value as used
    a[lead[p - 1]] = diff;                 // Assign it to the leader's position
  }
  // Collect unused numbers from 1 to n
  std::vector<long> rem;
  for (long p = 1; p <= n; p++) {
    if (!b[p]) {
      rem.push_back(p);
    }
  }
  // Assign remaining numbers to unspecified positions
  for (long p = 1; p <= n; p++) {
    if (a[p] > 0) {
      continue;  // Skip if already assigned
    }
    if (rem.size() > 0) {
      a[p] = rem.back();   // Assign last remaining number
      rem.pop_back();
    } else {
      possible = 0;        // No more numbers to assign - impossible
      break;
    }
  }
  if (!possible) {
    puts("-1");
  } else {
    for (long p = 1; p <= n; p++) {
      printf("%ld ", a[p]);
    };
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/