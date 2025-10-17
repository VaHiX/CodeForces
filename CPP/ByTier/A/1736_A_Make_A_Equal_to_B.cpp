// Problem: CF 1736 A - Make A Equal to B
// https://codeforces.com/contest/1736/problem/A

/*
A. Make A Equal to B
Algorithms/Techniques: Greedy, Array Manipulation

Time Complexity: O(n) per test case
Space Complexity: O(n) due to the vectors storing arrays a and b

Problem Summary:
Given two binary arrays a and b of length n, we can perform two operations:
1. Flip any element of array a (a[i] = 1 - a[i])
2. Rearrange the elements of array a in any order

Goal: Find minimum number of operations to make a equal to b.

Approach:
- Count how many positions differ between a and b (diff).
- Calculate the net difference in flips needed (chg), where chg = sum(a[i] - b[i]).
  If chg is negative, take absolute value.
- The result is the minimum of:
  - chg + 1: flip one element and then rearrange
  - diff: just rearrange

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long diff(0), chg(0);
    for (long p = 0; p < n; p++) {
      diff += (a[p] != b[p]); // Count differing positions
      chg += (a[p] - b[p]);   // Net difference in values
    }
    if (chg < 0) {
      chg = -chg; // Take absolute value of net change
    }
    long res = chg + 1;
    res = (res < diff) ? res : diff;
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/