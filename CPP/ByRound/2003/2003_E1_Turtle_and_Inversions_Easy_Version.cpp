// Problem: CF 2003 E1 - Turtle and Inversions (Easy Version)
// https://codeforces.com/contest/2003/problem/E1

/*
 * Problem: E1. Turtle and Inversions (Easy Version)
 *
 * Purpose:
 *   Given a permutation of length n and m intervals, find the maximum number of inversions
 *   in an "interesting" permutation. An interesting permutation must satisfy that for each interval,
 *   we can choose a split point such that max of left part is smaller than min of right part.
 *
 * Algorithm:
 *   - The key insight is to identify the valid regions where splits are possible.
 *   - By sorting intervals and using two pointers, we eliminate overlapping regions
 *     by considering overlapping intervals as one large interval.
 *   - Calculate total possible inversions in full permutation (n*(n-1)/2),
 *     then subtract invalid ranges that cannot be used to form an interesting permutation.
 *
 * Time Complexity: O(m log m) due to sorting the intervals.
 * Space Complexity: O(m) for storing the intervals.
 */

#include <iostream>
#include <utility>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int m, n;
    cin >> n >> m;
    pair<int, int> pr[m];
    for (int i = 0; i < m; i++) {
      cin >> pr[i].first >> pr[i].second; // Read interval [l_i, r_i)
    }
    long long int sum = 1LL * n * (n - 1) / 2; // Total inversions in a full permutation
    for (int i = 0, j = m - 1; i <= j; i++, j--) {
      // Subtract the invalid range that cannot be used in interesting permutations
      sum = sum - (pr[j].second - pr[i].first);
    }
    cout << sum << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/