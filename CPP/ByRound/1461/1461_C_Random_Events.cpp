// Problem: CF 1461 C - Random Events
// https://codeforces.com/contest/1461/problem/C

/*
Code Purpose:
This solution computes the probability that a permutation becomes sorted after a series of randomized sorting operations on prefixes.
Each operation sorts the prefix of length r_i with probability p_i.
The main idea is to determine how many elements from the end are already in their correct positions,
and then calculate the probability that no sorting operation disrupts this sorted state.

Algorithms/Techniques:
- Preprocessing to find the rightmost element out of place
- Probability calculation using the complement: 1 - (probability of not sorting)
- Efficient processing of events in reverse order to avoid recomputation

Time Complexity: O(n + m), where n is the length of the permutation and m is the number of experiments.
Space Complexity: O(n), to store the permutation array.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> a(n + 1);
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]);
    }
    // Find the rightmost element that is in its correct position (index == value)
    long idx(n);
    for (long p = n; p > 0; p--) {
      if (a[p] == p) {
        idx = p - 1;
      } else {
        break;
      }
    }
    // Compute the probability that the permutation remains unsorted
    long double prod(1.0);
    for (long p = 0; p < m; p++) {
      long r;
      long double prob;
      scanf("%ld %Lf", &r, &prob);
      // If the prefix length is large enough to include any unsorted part,
      // then probability of not sorting that section is (1 - prob)
      if (r >= idx) {
        prod *= (1.0 - prob);
      }
    }
    // Final answer is 1 minus the probability that the permutation stays unsorted
    long double ans = 1.0 - (idx > 0) * prod;
    printf("%.8Lf\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/