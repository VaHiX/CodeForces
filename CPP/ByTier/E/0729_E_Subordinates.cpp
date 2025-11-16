// Problem: CF 729 E - Subordinates
// https://codeforces.com/contest/729/problem/E

/*
 * Problem: E. Subordinates
 * 
 * Purpose: Given a company hierarchy with n workers and a chief (id s), each worker reports
 *          how many superiors (including indirect) they have. Some workers may have made mistakes.
 *          The task is to find the minimum number of workers that could have made a mistake.
 * 
 * Algorithm:
 *   - For each reported number of superiors, we analyze if it's consistent with a tree structure.
 *   - We use a count array (b) to store how many workers reported each number of superiors.
 *   - The solution corrects inconsistencies by adjusting the count array and counting required corrections.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 *   - Tree structure validation
 *   - Greedy adjustment of values in count array
 *   - Simulation of corrections
 */

#include <cstdio>
#include <vector>
int main() {
  long n, s;
  scanf("%ld %ld", &n, &s);
  std::vector<long> a(n);
  long M(2); // Maximum value in a, initialized to 2 for safety
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    M = (M > a[p]) ? M : a[p]; // Track maximum reported value
  }
  std::vector<long> b(M + 1); // Count of workers reporting each number of superiors
  for (long p = 0; p < n; p++) {
    ++b[a[p]]; // Increment count for that number of superiors
  }
  long count(0); // Number of corrections needed
  --s; // Convert to 0-based index
  if (a[s] != 0) { // If chief reported non-zero superiors, adjust
    ++b[0];
    --b[a[s]];
    ++count;
  }
  long left(1), right(M);
  // Ensure that the root has at least one worker
  while (b[0] > 1) {
    while (left < b.size() && b[left] > 0) {
      ++left;
    }
    --b[0];
    ++b[left];
    ++count;
  }
  left = 1;
  right = b.size() - 1;
  // Distribute corrections to fix inconsistencies
  while (left < right) {
    while (left < b.size() && b[left] > 0) {
      ++left;
    }
    while (right > 0 && b[right] == 0) {
      --right;
    }
    if (left < right) {
      b[left] = 1;
      --b[right];
      ++count;
    }
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/