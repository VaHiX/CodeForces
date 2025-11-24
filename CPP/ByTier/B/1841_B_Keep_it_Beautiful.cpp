// Problem: CF 1841 B - Keep it Beautiful
// https://codeforces.com/contest/1841/problem/B

/*
 * Problem: B. Keep it Beautiful
 * Algorithm: Linear simulation with tracking of array beauty property.
 *            For each new element, determine if appending it keeps the array beautiful.
 *            A beautiful array can be rotated to form a non-decreasing sequence.
 *
 * Time Complexity: O(q) amortized per test case, since we process each element once.
 * Space Complexity: O(1) extra space (excluding input/output).
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long first;
    scanf("%ld", &first);
    printf("1"); // First element always makes a beautiful array
    long cur(first); // Current value in the sequence being built
    bool drop(false); // Flag indicating whether we've seen a decreasing point
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (!drop && x >= cur) {
        // If we haven't dropped yet and current element is not smaller than previous,
        // append it and continue
        printf("1");
        cur = x;
      } else if (!drop) {
        // We hit a drop point: check if the new value can "reset" us to valid state
        if (x <= first) {
          // If current value is less than or equal to first, we may enter a new part of array
          printf("1");
          drop = true;
          cur = x;
        } else {
          // Otherwise it breaks the beauty condition
          printf("0");
        }
      } else if (drop) {
        // Already in a dropped segment: check if current value is valid for continuation
        if (cur <= x && x <= first) {
          // Valid range between previous and first element
          printf("1");
          cur = x;
        } else {
          // Value breaks condition
          printf("0");
        }
      }
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/