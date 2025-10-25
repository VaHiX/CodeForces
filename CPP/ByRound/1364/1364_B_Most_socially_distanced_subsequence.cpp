// Problem: CF 1364 B - Most socially-distanced subsequence
// https://codeforces.com/contest/1364/problem/B

/*
B. Most socially-distanced subsequence
Algorithm: Greedy approach to find the most "socially-distanced" subsequence
Time Complexity: O(n) per test case
Space Complexity: O(n) for the vector storage

The problem asks to find a subsequence of a permutation such that:
1. The sum of absolute differences between consecutive elements is maximized.
2. Among all such subsequences, we want the one with minimum length (at least 2).

Key insight:
To maximize sum of absolute differences |a[i]-a[i+1]|, we should alternate between local maxima and minima.
However, we can achieve maximum difference by simply choosing the first and last elements,
which gives the maximum possible sum for any valid subsequence.

But there's a smarter greedy approach:
We iterate through the array. For each element, we want to include it in the result if:
- It's the first element (always include)
- It's the last element (always include)
- Or, it's a local extremum (either a peak or valley), meaning the trend changes.
This is checked by comparing (a[p - 1] < a[p]) != (a[p] < a[p + 1]).

In simpler terms, if an element is not a local maximum or minimum, we skip it,
because including it won't add to the total difference maximally compared to
an optimal subsequence built from extremes only.

The algorithm effectively builds a subsequence by picking all elements where the direction of increase/decrease changes.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> ans;
    // Check if current element should be included in the answer
    // Include if it's first, last or a local extremum
    for (long p = 0; p < n; p++) {
      if (p == 0 || p + 1 == n || (a[p - 1] < a[p]) != (a[p] < a[p + 1])) {
        ans.push_back(a[p]);
      }
    }
    printf("%ld\n", ans.size());
    for (long p = 0; p < ans.size(); p++) {
      printf("%ld ", ans[p]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/