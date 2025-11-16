// Problem: CF 846 A - Curriculum Vitae
// https://codeforces.com/contest/846/problem/A

/*
 * Problem: Curriculum Vitae
 * 
 * Purpose: Given a sequence of 0s and 1s representing unsuccessful and successful games,
 *          find the maximum number of games that can be kept such that no unsuccessful
 *          game comes right after a successful one.
 * 
 * Algorithm: 
 *   - Precompute prefix counts of 0s (left array) and suffix counts of 1s (right array)
 *   - For each position, calculate how many games can be kept if we remove all 0s
 *     before this position and all 1s after this position, then take maximum.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 *   - Prefix and suffix arrays for efficient computation
 *   - Greedy approach to maximize count under constraint
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<int> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%d", &a[p]);
  }
  std::vector<long> left(n);
  left[0] = (a[0] == 0);  // Count of 0s from start up to index 0
  for (long p = 1; p < n; p++) {
    left[p] = left[p - 1] + (a[p] == 0);  // Accumulate count of 0s
  }
  std::vector<long> right(n);
  right[n - 1] = (a[n - 1] == 1);  // Count of 1s from end down to index n-1
  for (long p = n - 2; p >= 0; p--) {
    right[p] = right[p + 1] + (a[p] == 1);  // Accumulate count of 1s
  }
  long total(0);
  for (long p = 0; p < n; p++) {
    long cand = left[p] + right[p];  // Total count if we keep prefix 0s and suffix 1s
    total = (total > cand) ? total : cand;  // Keep maximum
  }
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/