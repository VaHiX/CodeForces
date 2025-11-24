// Problem: CF 1006 B - Polycarp's Practice
// https://codeforces.com/contest/1006/problem/B

/*
 * Code Purpose: This program solves the problem of distributing 'n' problems across 'k' days 
 * such that each day has at least one problem, problems are solved in order, and the total 
 * profit (sum of maximum difficulties per day) is maximized.
 * 
 * Algorithm: Greedy approach
 * - Sort all problems by difficulty in descending order
 * - Assign the first k problems (highest difficulties) to k days
 * - Adjust the last day to cover all remaining problems
 * 
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing vector of pairs and results
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<std::pair<long, long>> v(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &v[p].first);
    v[p].second = p + 1;
  }
  sort(v.rbegin(), v.rend()); // Sort by difficulty in descending order
  std::vector<long> w(k);
  long total(0);
  for (long p = 0; p < k; p++) {
    total += v[p].first; // Sum up the top k difficulties
    w[p] = v[p].second;  // Store the problem indices
  }
  printf("%ld\n", total);
  sort(w.begin(), w.end()); // Sort indices in ascending order
  w[k - 1] = n; // Adjust last day to cover all problems
  for (long p = 0; p < k; p++) {
    printf("%ld ", w[p] - ((p == 0) ? 0 : w[p - 1])); // Print number of problems per day
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/