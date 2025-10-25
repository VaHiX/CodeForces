// Problem: CF 1979 A - Guess the Maximum
// https://codeforces.com/contest/1979/problem/A

/*
Problem: A. Guess the Maximum
Algorithm/Techniques: Prefix maximum, greedy approach
Time Complexity: O(n) per test case
Space Complexity: O(1)

Alice and Bob play a game with an array of integers. Bob chooses a subsegment and finds its maximum.
Alice wins if this maximum is strictly greater than some value k that she chooses.
We need to find the maximum k such that Alice is guaranteed to win regardless of which subsegment Bob picks.

The key insight is that for Alice to be guaranteed to win, every possible subarray's maximum must be > k.
This means we find the smallest maximum among all subarrays, and then k = smallest_max - 1.
We can compute this efficiently by keeping track of prefix maxima and updating the global minimum of these maxima.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev;
    scanf("%ld", &prev);
    long mx(1e9 + 7); // Initialize with a large number to find min
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      long cur = (x > prev ? x : prev); // Current max of the interval ending at p
      mx = (mx < cur ? mx : cur);       // Keep track of minimum among all such interval maxes
      prev = x;                         // Update previous for next iteration
    }
    printf("%ld\n", mx - 1);
  }
}


// https://github.com/VaHiX/codeForces/