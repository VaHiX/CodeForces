// Problem: CF 1704 B - Luke is a Foodie
// https://codeforces.com/contest/1704/problem/B

/*
B. Luke is a Foodie
Problem Description:
Given n piles of food with sizes a_i and a fixed integer x, Luke can eat a pile if |v - a_i| <= x where v is his food affinity.
Luke can set v initially and change it before eating each pile. Find minimum number of changes needed to eat all piles.

Algorithm:
Greedy interval merging approach:
- For each pile, compute the valid range [a_i - x, a_i + x] for acceptable values of v
- Maintain overlapping intervals: if current pile's range doesn't overlap with previous merged range, increment change count and start a new interval
- Time complexity: O(n) per test case
- Space complexity: O(1)

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    long cnt(0), low(0), high(2e9 + 7); // cnt: changes; low/high: current valid interval bounds
    for (long p = 0; p < n; p++) {
      long cur;
      scanf("%ld", &cur);
      long left = cur - x;   // Left boundary of valid v range for current pile
      long right = cur + x;  // Right boundary of valid v range for current pile
      low = (low > left) ? low : left;       // Update lower bound to max of current and new
      high = (high < right) ? high : right;  // Update upper bound to min of current and new
      if (low > high) {                      // If no overlap between intervals, we need a change
        ++cnt;
        low = left;
        high = right;
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/