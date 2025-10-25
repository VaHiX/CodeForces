// Problem: CF 1250 H - Happy Birthday
// https://codeforces.com/contest/1250/problem/H

/*
H. Happy Birthday

Purpose:
This program determines the smallest positive integer (age) that cannot be formed using the given counts of digit candles (0-9).
The algorithm analyzes which digits are available and identifies the first number that cannot be constructed.

Algorithms/Techniques:
- Greedy approach to find the largest possible digit that can contribute to forming numbers.
- Iteration through available digits to determine minimum unformable number.
- Linear scan for optimality in construction of smallest non-formable number.

Time Complexity: O(1) per test case (since there are only 10 digits, constant operations)
Space Complexity: O(1) (fixed-size array of 10 integers, no extra space used)

Input:
- t test cases
- For each test case: 10 integers c_0 to c_9 representing count of each digit candle

Output:
- For each test case: minimum age y such that numbers 1 to y-1 are formable but y is not.
*/

#include <cstdio>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long a[10];
    for (long p = 0; p < 10; p++) {
      scanf("%ld", a + p); // Read count of each digit (0 to 9)
    }
    int d(0); // Initialize digit index with maximum possible value
    long rep = a[0]; // Start comparison with count of '0' candles
    for (long p = 9; p >= 1; p--) { // Loop from 9 down to 1
      if (a[p] <= rep) {
        rep = a[p]; // Update rep to minimum count so far
        d = p; // Remember which digit had the minimum count
      }
    }
    if (d == 0) { // Special case for '0'
      printf("1");
    }
    for (long p = 0; p <= rep; p++) {
      printf("%d", d); // Print digit d, 'rep' times
    }
    puts(""); // New line after output
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/