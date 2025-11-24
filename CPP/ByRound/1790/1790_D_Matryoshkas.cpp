// Problem: CF 1790 D - Matryoshkas
// https://codeforces.com/contest/1790/problem/D

/*
D. Matryoshkas
Algorithm: Greedy approach with sorting and sliding window-like logic to minimize number of sets.
Time Complexity: O(n log n) per test case due to sorting; overall O(n log n) for all test cases given the constraint on total n.
Space Complexity: O(n) for storing the vector of sizes.

Problem Description:
Given a sequence of doll sizes, determine the minimum number of non-overlapping sets
such that each set forms a consecutive sequence of integers [s, s+1, ..., s+m-1].
Each doll must be used exactly once, and we want to minimize the number of such sets.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n, 0);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    sort(v.begin(), v.end()); // Sort the sizes to process in order
    v.push_back(1e9 + 3);     // Sentinel value to handle last group properly
    long prev(v[0]), cur(1), cnt(0), run(0);
    for (long p = 1; p <= n; p++) {
      if (v[p] == prev) {
        ++cur;  // Count frequency of current element
      } else {
        if (cur < run) {
          cnt += (run - cur);   // We need to add more elements from previous sets to match current set size
          run = cur;
        } else {
          run = cur;
        }
        if (v[p] > prev + 1) {    // Gap detected — new set required
          cnt += run;             // Add all remaining elements in the current run as a new set
          run = 0;
        }
        cur = 1;    // Reset counter for next element
      }
      prev = v[p];
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/