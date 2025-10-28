// Problem: CF 1490 B - Balanced Remainders
// https://codeforces.com/contest/1490/problem/B

/*
B. Balanced Remainders
Algorithm: Greedy approach with remainder counting and simulation of moves.
Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(1), since we use a fixed-size array of size 3 for counting remainders.

The problem requires making an array have balanced remainders when divided by 3.
We count how many elements fall into each remainder class (0, 1, 2).
Then we simulate distributing these counts evenly among the three classes,
making moves to shift excess elements from one remainder class to another,
minimizing total moves needed.

The algorithm tracks the carry-over of excess elements from one step to the next,
and computes the minimum number of increments required.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long c[3] = {0}; // Count of elements with remainders 0, 1, 2
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++c[x % 3]; // Increment count based on remainder when divided by 3
    }
    long cnt(0), carry(0); // cnt: total moves, carry: excess elements from previous step
    for (long p = 0; p < 10; p++) { // Loop 10 times to simulate all possible remainder transitions
      cnt += carry; // Add previous carry to the move count
      c[p % 3] += carry; // Add carry to current remainder class
      carry = 0; // Reset carry for this step
      if (c[p % 3] > n / 3) { // If current class has too many elements
        long diff = c[p % 3] - n / 3; // Compute excess
        carry += diff; // Pass excess as carry to next step
        c[p % 3] -= diff; // Reduce count to target level
      }
    }
    printf("%ld\n", cnt); // Output total number of moves
  }
}


// https://github.com/VaHiX/codeForces/