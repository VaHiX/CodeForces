// Problem: CF 899 B - Months and Years
// https://codeforces.com/contest/899/problem/B

/*
 * Purpose: Determine if a sequence of n integers can represent the number of days
 *          in n consecutive months according to the Gregorian calendar.
 *
 * Algorithm: Precompute all possible 36-month sequences (12 months repeated twice)
 *            to cover all possible year transitions (including leap years).
 *            Then slide a window of size n over this sequence to check if
 *            the input matches any subsequence.
 *
 * Time Complexity: O(36 * n) = O(n), since 36 is a constant
 * Space Complexity: O(1), only using fixed-size arrays and variables
 */

#include <cstdio>

int main() {
  // Precomputed array of days in months, repeated twice to handle year transitions
  const int arr[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
                     31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
                     31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int n;
  scanf("%d", &n);
  int a[37]; // Input array to store the sequence of days
  for (int p = 0; p < n; p++) {
    scanf("%d", a + p);
  }
  bool possible(true);
  // Slide a window of size n over the 36-month sequence
  for (int p = 0; p < 36; p++) {
    possible = true;
    for (int q = 0; q < n; q++) {
      // Compare input sequence with the current window
      if (a[q] != arr[(p + q) % 36]) {
        possible = false;
        break;
      }
    }
    if (possible) {
      break;
    }
  }
  puts(possible ? "Yes" : "No");
  return 0;
}


// https://github.com/VaHiX/CodeForces/