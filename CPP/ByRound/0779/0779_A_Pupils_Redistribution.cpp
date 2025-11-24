// Problem: CF 779 A - Pupils Redistribution
// https://codeforces.com/contest/779/problem/A

#include <iostream>
#include <vector>
/*
 * Problem: Pupils Redistribution
 * 
 * Purpose: 
 *   Redistribute students between two groups A and B such that both groups have the same count of students for each academic performance (1 to 5).
 *   Each exchange involves one student from A and one from B swapping groups.
 * 
 * Algorithm:
 *   1. Count the occurrences of each grade (1 to 5) in both groups.
 *   2. For each grade, compute the difference in counts between groups.
 *   3. If any difference is odd, it's impossible to balance, return -1.
 *   4. Otherwise, sum up the absolute differences and divide by 4 to get minimum exchanges.
 * 
 * Time Complexity: O(n) where n is the number of students per group.
 * Space Complexity: O(1) as we use fixed-size arrays of size 6 (for grades 0 to 5).
 * 
 * Techniques:
 *   - Frequency counting
 *   - Greedy approach to minimize swaps
 *   - Modular arithmetic for validation
 */
int main() {
  std::ios_base::sync_with_stdio(false);
  const int N = 5;
  int n;
  std::cin >> n;
  std::vector<int> countA(N + 1, 0), countB(N + 1, 0);
  for (int p = 0; p < n; p++) {
    int x;
    std::cin >> x;
    ++countA[x]; // Count grade x in group A
  }
  for (int p = 0; p < n; p++) {
    int x;
    std::cin >> x;
    ++countB[x]; // Count grade x in group B
  }
  bool possible(true);
  int total(0);
  for (int p = 1; p <= N; p++) {
    int diff = countA[p] - countB[p]; // Difference in count for grade p
    if (diff % 2) { // If difference is odd, balancing is impossible
      possible = false;
      break;
    }
    if (diff < 0) {
      diff = -diff; // Take absolute value
    }
    total += diff; // Accumulate total imbalance
  }
  if (possible && (total % 4 == 0)) { // If balanced and total swaps are even
    std::cout << (total / 4) << std::endl; // Minimum exchanges required
  } else {
    std::cout << "-1" << std::endl; // Impossible to balance
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/