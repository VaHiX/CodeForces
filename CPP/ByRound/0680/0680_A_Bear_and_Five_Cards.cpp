// Problem: CF 680 A - Bear and Five Cards
// https://codeforces.com/contest/680/problem/A

/*
 * Problem: Bear and Five Cards
 * Algorithm: Brute force enumeration
 * 
 * Approach:
 * - Read 5 integers representing card values.
 * - Calculate initial sum of all cards.
 * - Check all possible pairs of identical cards and compute the sum after removing them.
 * - Check all possible triplets of identical cards and compute the sum after removing them.
 * - Return the minimum sum obtained from these operations.
 * 
 * Time Complexity: O(1) - Since we have a fixed number of cards (5), the loops are bounded and constant.
 * Space Complexity: O(1) - Only using a fixed-size vector and a few variables.
 */

#include <cstdio>
#include <vector>
const int N = 5;
int main() {
  std::vector<int> a(N);
  int sum(0);
  for (int p = 0; p < N; p++) {
    scanf("%d", &a[p]);       // Read each card value
    sum += a[p];              // Keep running total of sum
  }
  int ans(sum);               // Initialize answer with full sum

  // Check all pairs of identical cards to remove
  for (int p = 0; p < N; p++) {
    for (int q = p + 1; q < N; q++) {
      if (a[p] == a[q] && (sum - 2 * a[p]) < ans) {
        ans = sum - 2 * a[p];   // Update minimum if removing pair gives smaller sum
      }
    }
  }

  // Check all triplets of identical cards to remove
  for (int p = 0; p < N; p++) {
    for (int q = p + 1; q < N; q++) {
      for (int r = q + 1; r < N; r++) {
        if (a[p] == a[q] && a[p] == a[r] && (sum - 3 * a[p]) < ans) {
          ans = sum - 3 * a[p];   // Update minimum if removing triplet gives smaller sum
        }
      }
    }
  }

  printf("%d\n", ans);        // Output the minimum possible sum
  return 0;
}


// https://github.com/VaHiX/CodeForces/