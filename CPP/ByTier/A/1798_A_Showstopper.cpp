// Problem: CF 1798 A - Showstopper
// https://codeforces.com/contest/1798/problem/A

/*
 * Problem: Showstopper
 * Algorithms/Techniques: Greedy approach with swapping
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) per test case
 *
 * Description:
 * Given two arrays a and b of length n, we can swap elements at the same index
 * between the two arrays any number of times. We need to determine if it's possible
 * to make the last element of both arrays equal to their respective maximum values.
 * 
 * Approach:
 * - For each index, if a[i] > b[i], swap them so that a[i] <= b[i].
 * - Track maximum elements in both arrays after swaps.
 * - Check if the max elements are at the last positions of respective arrays.
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
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long mxa(0), mxb(0);
    for (long p = 0; p < n; p++) {
      // If a[p] > b[p], swap so that a[p] <= b[p]
      if (a[p] > b[p]) {
        long tmp = a[p];
        a[p] = b[p];
        b[p] = tmp;
      }
      // Keep track of maximum values in both arrays
      mxa = (mxa > a[p]) ? mxa : a[p];
      mxb = (mxb > b[p]) ? mxb : b[p];
    }
    // Check if the last element is the maximum in respective arrays
    bool res = (mxa == a.back()) && (mxb == b.back());
    puts(res ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/