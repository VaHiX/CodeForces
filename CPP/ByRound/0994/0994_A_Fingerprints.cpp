// Problem: CF 994 A - Fingerprints
// https://codeforces.com/contest/994/problem/A

/*
 * Problem: Fingerprints
 * 
 * Purpose: Find the longest subsequence from a given sequence that only contains
 *          digits with fingerprints on the keypad. The order of the subsequence
 *          must match the order in the original sequence.
 * 
 * Algorithm: 
 *   1. Read the sequence of digits.
 *   2. Store the fingerprinted digits in a set for O(log m) lookup.
 *   3. Iterate through the original sequence and collect all digits that are
 *      present in the fingerprint set.
 *   4. Output the collected digits in order.
 * 
 * Time Complexity: O(n * log m + k), where n is the length of the sequence,
 *                  m is the number of fingerprinted keys, and k is the size of
 *                  the result. The log m factor comes from set lookups.
 * 
 * Space Complexity: O(n + m), for storing the sequence and the set of fingerprinted digits.
 */

#include <cstdio>
#include <set>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::set<long> b;
  for (long p = 0; p < m; p++) {
    long x;
    scanf("%ld", &x);
    b.insert(x);
  }
  std::vector<long> res;
  for (long p = 0; p < n; p++) {
    // Check if the current digit has a fingerprint
    if (b.count(a[p])) {
      res.push_back(a[p]);
    }
  }
  for (long p = 0; p < res.size(); p++) {
    printf("%ld ", res[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/