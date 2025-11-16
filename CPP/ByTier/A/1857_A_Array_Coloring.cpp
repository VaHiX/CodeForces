// Problem: CF 1857 A - Array Coloring
// https://codeforces.com/contest/1857/problem/A

/*
 * Problem: Array Coloring
 * Algorithm/Techniques: Greedy, Parity Analysis
 *
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(1), only using a constant amount of extra space.
 *
 * Description:
 * Given an array of integers, determine if it's possible to split the elements
 * into two non-empty groups such that both group sums have the same parity
 * (both even or both odd). This is possible if and only if the total sum
 * of the array is even. If the total sum is even, we can always partition
 * the array to achieve equal parity sums.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0); // s holds the sum of all elements in current test case
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += x; // accumulate the sum
    }
    // If total sum is odd, it's impossible to split into two equal parity groups
    puts(s % 2 ? "NO" : "YES");
  }
}


// https://github.com/VaHiX/codeForces/