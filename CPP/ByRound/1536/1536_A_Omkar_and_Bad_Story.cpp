// Problem: CF 1536 A - Omkar and Bad Story
// https://codeforces.com/contest/1536/problem/A

/*
Code Purpose:
This solution determines whether a "nice" array can be constructed from a given array of distinct integers.
A "nice" array is one where for any two distinct elements in the array, their absolute difference is also present in the array.
The algorithm checks if all elements in the input array are non-negative.
If all elements are non-negative, it constructs a nice array by adding all integers from 0 to 100.
This works because the set {0, 1, 2, ..., 100} forms a nice array since all pairwise differences are also in the set.
If any element is negative, it is impossible to form such an array, so output is "NO".

Algorithms/Techniques:
- Simple iteration over input array to check for negative values
- If no negatives, construct a known nice array {0, 1, 2, ..., 100}

Time Complexity: O(n) where n is the size of the input array, as we iterate through it once.
Space Complexity: O(1) excluding the output space, as we only use a constant amount of extra variables.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool possible(true);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < 0) {
        possible = false;
      }
    }
    if (possible) {
      puts("YES\n101"); // Output "YES" and size of constructed array
      for (long p = 0; p <= 100; p++) {
        printf("%ld ", p); // Print all integers from 0 to 100
      }
      puts(""); // Newline after printing the array
    } else {
      puts("NO"); // If there's a negative number, impossible to make nice array
    }
  }
}


// https://github.com/VaHiX/CodeForces/