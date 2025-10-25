// Problem: CF 1729 D - Friends and the Restaurant
// https://codeforces.com/contest/1729/problem/D

/*
 * Problem: D. Friends and the Restaurant
 * Purpose: Given n friends, each with a planned spending (x_i) and budget (y_i),
 *          find the maximum number of days they can visit the restaurant such that:
 *          - Each day, at least two friends visit
 *          - Total budget of the group >= Total spending of the group
 *          - No friend visits more than once
 *
 * Algorithm:
 * 1. For each friend compute the difference: diff = y_i - x_i
 * 2. Separate differences into negative (deficit) and positive (surplus) values
 * 3. Sort negatives in descending order, positives in ascending order
 * 4. Try to pair a deficit with a surplus to balance it, greedily
 * 5. Remaining friends (with zero diff) can form groups of two each
 *
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the difference arrays
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
    std::vector<long> x(n), y(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &x[p]);
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &y[p]);
    }
    std::vector<long> pos, neg;
    long cnt(0), rem(0);
    for (long p = 0; p < n; p++) {
      long diff = y[p] - x[p]; // Compute budget vs spending difference
      if (diff < 0) {
        neg.push_back(diff);  // Store deficit cases
      } else if (diff > 0) {
        pos.push_back(diff);  // Store surplus cases
        ++rem;
      } else {
        ++rem;  // Zero difference - can be paired or left alone
      }
    }
    sort(neg.rbegin(), neg.rend()); // Sort deficits in descending order (largest first)
    sort(pos.begin(), pos.end());   // Sort surpluses in ascending order (smallest first)
    long idx(0);
    for (long p = 0; p < neg.size(); p++) {
      while ((idx < pos.size()) && (pos[idx] + neg[p] < 0)) {
        ++idx;  // Find smallest surplus that can cover current deficit
      }
      if ((idx < pos.size()) && (pos[idx] + neg[p] >= 0)) {
        ++idx;
        ++cnt;   // Successfully paired a deficit with a surplus
        --rem;
      }
    }
    cnt += rem / 2; // Remaining friends can form groups of two each
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/