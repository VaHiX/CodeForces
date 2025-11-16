// Problem: CF 843 A - Sorting by Subsequences
// https://codeforces.com/contest/843/problem/A

/*
Algorithm: Sorting by Subsequences
Approach:
This problem involves splitting a sequence into the maximum number of subsequences such that when each subsequence is sorted individually, the entire sequence becomes sorted.

The key insight is:
1. Create a sorted version of the array with indices.
2. For each element, determine where it would end up in the sorted array (its "rank").
3. We then look for cycles in the permutation formed by these ranks.
4. Each cycle forms a subsequence that needs to be sorted together to maintain the final sorted order.
5. Output each such cycle as a subsequence with its original indices.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array, ranks, and used flags

Techniques:
- Sorting with index tracking
- Cycle detection in permutations
- Greedy approach to maximize number of subsequences
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::pair<long, long>> a(n); // Store value and original index
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p].first);
    a[p].second = p;
  }
  sort(a.begin(), a.end()); // Sort by values, keeping original indices
  std::vector<bool> used(n, 0); // Track which indices have been processed
  std::vector<long> rank(n); // Maps original index to its position in sorted array
  for (long p = 0; p < n; p++) {
    rank[p] = a[p].second; // Store the original index of the element at position p in sorted array
  }
  std::vector<std::vector<long>> s; // Stores the resulting subsequences
  for (long p = 0; p < n; p++) {
    if (used[p]) {
      continue; // Skip already processed elements
    }
    long cur = p;
    std::vector<long> v;
    while (!used[cur]) {
      v.push_back(cur); // Add current index to current subsequence
      used[cur] = 1;    // Mark as used
      cur = rank[cur];  // Move to where the current element would be in sorted array
    }
    s.push_back(v); // Add the subsequence to result
  }
  printf("%ld\n", s.size()); // Print number of subsequences
  for (long p = 0; p < s.size(); p++) {
    printf("%ld ", s[p].size()); // Print size of subsequence
    for (long q = 0; q < s[p].size(); q++) {
      printf("%ld ", 1 + s[p][q]); // Print original indices (1-based)
    }
    puts(""); // New line
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/