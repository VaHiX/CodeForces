// Problem: CF 1490 A - Dense Array
// https://codeforces.com/contest/1490/problem/A

/*
 * Problem: Dense Array
 * Algorithm: Greedy approach with binary doubling technique
 * Time Complexity: O(n) per test case, where n is the length of the array
 * Space Complexity: O(1) - only using a constant amount of extra space
 *
 * The solution processes each adjacent pair of elements in the array.
 * For each pair, it calculates how many numbers need to be inserted
 * so that the maximum divided by the minimum is at most 2.
 * This is done by repeatedly doubling the smaller number until it is at least half of the larger.
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
    long cnt(0);
    for (long p = 1; p < n; p++) { // Iterate through adjacent pairs
      long x;
      scanf("%ld", &x);
      long a = (x < prev) ? x : prev;   // Smaller value
      long b = (x > prev) ? x : prev;   // Larger value
      while (2 * a < b) {               // While doubling the smaller doesn't satisfy condition
        a *= 2;                         // Double the smaller value
        ++cnt;                          // Increment count of numbers added
      }
      prev = x; // Move to next element
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/