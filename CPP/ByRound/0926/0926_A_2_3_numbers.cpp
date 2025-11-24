// Problem: CF 926 A - 2-3-numbers
// https://codeforces.com/contest/926/problem/A

/*
 * Problem: Count the number of 2-3-integers in the range [l, r].
 * 2-3-integers are numbers of the form 2^x * 3^y where x, y are non-negative integers.
 * These are numbers whose only prime factors are 2 and 3.
 *
 * Approach:
 * - Generate all possible values of the form 2^x * 3^y that are <= r.
 * - For each power of 2 (a = 2^x), iterate through all powers of 3 (b = 3^y)
 *   such that a * b <= r.
 * - Count how many such products fall within [l, r].
 *
 * Time Complexity: O(log₂(r) * log₃(r)) = O(log r * log r)
 * Space Complexity: O(1)
 */

#include <iostream>
using namespace std;

long long l, r, t, a, b;

int main() {
  cin >> l >> r;
  for (a = 1; a <= r; a *= 2) {          // Iterate through all powers of 2 up to r
    for (b = 1; b <= r; b *= 3)          // For each power of 2, iterate through powers of 3
      if (l <= a * b && a * b <= r)      // Check if the product is within [l, r]
        t++;                             // Increment the count if valid
  }
  cout << t;
}


// https://github.com/VaHiX/CodeForces/