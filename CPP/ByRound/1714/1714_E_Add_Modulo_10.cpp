// Problem: CF 1714 E - Add Modulo 10
// https://codeforces.com/contest/1714/problem/E

/*
Code Purpose:
This code determines whether it's possible to make all elements of an array equal by repeatedly applying an operation that adds the last digit of an element to itself. The core idea is to analyze the behavior of numbers under the operation and classify them based on their cycles or final states.

Algorithms/Techniques:
- Simulation of the operation: For each number, keep applying the operation until it reaches a stable form (ending in 0 or 2).
- Classification of numbers based on their final digit and pattern of growth.
- Check conditions that determine if all array elements can be made equal.

Time Complexity: O(n), where n is the total number of elements across all test cases.
Space Complexity: O(1), as only a constant amount of extra space is used.

*/
#include <cstdio>
long getnext(long x) { return x + (x % 10); } // Helper function to perform the operation
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool z(false), two(false), twelve(false); // Flags to track patterns
    long mn(1e9), mx(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // Reduce x to its terminal state by applying operation
      while ((x % 10 != 0) && (x % 10 != 2)) {
        x = getnext(x);
      }
      // Classify the terminal state
      if (x % 10 == 0) {
        z = true; // Terminal state ends in 0
      } else if (x % 20 == 2) {
        two = true; // Terminal state ends in 2 (like 2, 22, 42, ...)
      } else {
        twelve = true; // Other terminal state (like 12, 32, 52, ...)
      }
      mn = (mn < x ? mn : x);  // Keep track of minimum terminal value
      mx = (mx > x ? mx : x);  // Keep track of maximum terminal value
    }
    // Determine if it's possible to make all equal based on the flags and terminal values
    bool possible = (z && mn == mx && !two && !twelve) ||
                    (!z && two && !twelve) || (!z && !two && twelve);
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/CodeForces/