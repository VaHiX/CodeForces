// Problem: CF 1943 A - MEX Game 1
// https://codeforces.com/contest/1943/problem/A

/*
 * Problem: A. MEX Game 1
 * 
 * Purpose: Given an array of integers, Alice and Bob play a game where they alternately pick elements from the array.
 * Alice picks an element and appends it to a new array `c`, then deletes it from the original array.
 * Bob just picks an element and deletes it. The goal is to find the MEX (minimum excludant) of array `c` when both play optimally.
 *
 * Algorithm:
 * - Count frequency of each number in input array.
 * - For Alice's turn (odd indices), she will try to place numbers into `c`.
 * - Bob will just remove elements without adding to `c`.
 * - Since Alice starts first and wants to maximize MEX, she will attempt to include 0, 1, 2, ... in her array.
 * - As soon as we can't put a number (i.e., count is 0), that becomes the MEX.
 * - But Bob will block Alice if he can, so after each of Alice’s turn, Bob removes one element optimally to minimize final MEX.
 * - In optimal play:
 *   - Alice wants to see all small numbers (0,1,2,...) in `c` so that the MEX is maximized.
 *   - When she encounters a number not appearing in array `a`, or when it's a duplicate, she skips until a unique count > 0.
 *   - However due to alternating turns and game mechanics described, we can solve efficiently:
 *     Use frequency counting and then determine first missing non-negative integer, accounting for turn logic.
 *
 * Time Complexity: O(n) where n is size of input array
 * Space Complexity: O(n) for storing the frequency vector
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> f(n + 1, 0); // frequency array for values 0 to n
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++f[x]; // increment count of x in frequency array
    }
    long single(0), ans(0);
    for (long p = 0; p <= n; p++) {
      if (!f[p]) {
        ans = p; // first missing number is MEX
        break;
      }
      single += (f[p] == 1); // count how many numbers appear exactly once
      if (single == 2) {
        ans = p; // if two singles found, MEX <= current value
        break;
      }
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/