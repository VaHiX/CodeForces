// Problem: CF 507 A - Amr and Music
// https://codeforces.com/contest/507/problem/A

/*
 * Problem: Amr and Music
 * Algorithm: Greedy approach
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing instrument data and result
 *
 * Approach:
 * - Sort instruments by the number of days needed to learn them (ascending).
 * - Greedily select the instruments with the least days until time runs out.
 * - Output the count of selected instruments and their indices.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n, k;
  scanf("%ld %ld\n", &n, &k);
  std::vector<std::pair<long, long>> days(n);
  for (long p = 0; p < n; p++) {
    long temp;
    scanf("%ld", &temp);
    // Store days required and original index (1-based)
    days[p] = std::pair<long, long>(temp, 1 + p);
  }
  // Sort instruments by the number of days needed (greedy choice)
  sort(days.begin(), days.end());
  std::vector<long> learn;
  long remTime(k); // Remaining time available
  for (long p = 0; p < n; p++) {
    // If current instrument requires more time than remaining, skip
    if (days[p].first > remTime) {
      break;
    }
    remTime -= days[p].first; // Deduct the time needed for this instrument
    learn.push_back(days[p].second); // Add instrument index to learning list
  }
  // Output the number of instruments that can be learned
  printf("%ld\n", learn.size());
  // Output the indices of instruments to be learned
  for (long p = 0; p < learn.size(); p++) {
    printf("%ld ", learn[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/