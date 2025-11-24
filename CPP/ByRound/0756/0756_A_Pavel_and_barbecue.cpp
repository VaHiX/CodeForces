// Problem: CF 756 A - Pavel and barbecue
// https://codeforces.com/contest/756/problem/A

/*
 * Problem: Pavel and barbecue
 * Purpose: Determine the minimum number of changes needed in a permutation and a binary sequence
 *          so that every skewer visits every position in both directions.
 *
 * Algorithm:
 * - The problem reduces to analyzing cycles in the permutation and the parity of the number of reversals.
 * - For a permutation, we compute the number of cycles.
 * - If there is more than one cycle, at least one element in the permutation must be changed to make all skewers
 *   visit all positions.
 * - If the total number of reversals (sum of b) is even, we must change at least one element in b to make it odd,
 *   because we need the total number of reversals to be odd for all positions to be reached in both directions.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1, 0); // To store the permutation p
  std::vector<bool> visited(n + 1, 0); // To track visited nodes during cycle detection
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]);
  }
  long b(0); // Count of 1s in sequence b
  for (long p = 1; p <= n; p++) {
    int x;
    scanf("%d", &x);
    b += x;
  }
  long cycles(0); // Count of cycles in the permutation
  for (long p = 1; p <= n; p++) {
    if (visited[p]) {
      continue;
    }
    ++cycles;
    long u = p;
    while (!visited[u]) {
      visited[u] = 1;
      u = a[u];
    }
  }
  // If there is more than one cycle, we need to change at least one element in permutation.
  // If total reversals is even, we need to change one element in b to make it odd.
  long count = ((cycles > 1) ? cycles : 0) + (b % 2 == 0);
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/