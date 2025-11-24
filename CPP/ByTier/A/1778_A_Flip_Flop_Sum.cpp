// Problem: CF 1778 A - Flip Flop Sum
// https://codeforces.com/contest/1778/problem/A

/*
Problem: Flip Flop Sum
Algorithms/Techniques: Greedy approach, prefix analysis
Time Complexity: O(n) where n is the length of the array
Space Complexity: O(1)

Given an array of 1s and -1s, we can perform exactly one operation:
choose index i (1 <= i < n) and flip signs of a[i] and a[i+1].
Goal: maximize the sum of the array after this operation.

Approach:
- Calculate initial sum of the array.
- Track if there are consecutive negative numbers (neg) - this can be improved by flipping
  two adjacent negatives to positives, adding 4 to the sum.
- Track if there are sign changes (z) - this indicates we have both positive and negative values,
  and flipping such pairs could improve the sum.
- If there are two consecutive negatives, flipping them gives +4 gain.
- If no sign changes, it means all elements are same (all 1s or all -1s), and flipping
  adjacent elements reduces sum by 4 because we're changing two elements from 1 to -1 or vice versa.
- Otherwise, flipping gives no benefit.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    int prev(0);
    scanf("%d", &prev);
    long s(prev);
    bool neg(0), z(0);
    for (long p = 1; p < n; p++) {
      int x;
      scanf("%d", &x);
      s += x;
      if (x < 0 && prev < 0) {        // Check for consecutive negative numbers
        neg = true;
      } else if (x * prev < 0) {      // Check for sign change
        z = true;
      }
      prev = x;
    }
    if (neg) {
      s += 4;                         // Gain from flipping two negatives to positives
    } else if (!z) {
      s -= 4;                         // Loss from flipping when all elements are same
    }
    printf("%ld\n", s);
  }
}


// https://github.com/VaHiX/codeForces/