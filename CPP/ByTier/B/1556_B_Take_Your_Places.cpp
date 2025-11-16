// Problem: CF 1556 B - Take Your Places!
// https://codeforces.com/contest/1556/problem/B

/*
 * Problem: B. Take Your Places!
 * Purpose: Given an array of integers, find the minimum number of adjacent swaps
 *          required to make sure that no two adjacent elements have the same parity.
 *          Return -1 if impossible.
 *
 * Algorithm:
 * 1. For each element, determine whether it's odd or even.
 * 2. Try to arrange elements such that odd and even numbers alternate.
 * 3. We consider two possible valid arrangements:
 *    a) Odd at odd indices (1,3,5...) and even at even indices (2,4,6...)
 *    b) Even at odd indices (1,3,5...) and odd at even indices (2,4,6...)
 * 4. For each arrangement, calculate the minimum number of swaps needed to bring
 *    each element to its correct position.
 * 5. If the counts of odds and evens do not allow for a valid alternating pattern,
 *    return -1.
 *
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(1), constant extra space.
 */

#include <bits/std_abs.h>
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long oddpos(1), evenpos(2), oddcount(0), evencount(0), oddfirst(0),
        evenfirst(0);
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % 2) { // If number is odd
        oddfirst += std::abs(p - oddpos);   // Calculate swaps needed to move this odd number to an odd position
        evenfirst += std::abs(p - evenpos); // Calculate swaps needed to move this odd number to an even position
        oddpos += 2;                        // Next odd position (1, 3, 5, ...)
        evenpos += 2;                       // Next even position (2, 4, 6, ...)
        ++oddcount;                         // Increment count of odd numbers
      } else {                              // If number is even
        ++evencount;                        // Increment count of even numbers
      }
    }
    long res(-1);
    if (oddcount == evencount) {
      res = (oddfirst < evenfirst ? oddfirst : evenfirst); // Choose the arrangement with fewer swaps
    } else if (oddcount == evencount + 1) {
      res = oddfirst; // Must start with odd at index 1
    } else if (oddcount + 1 == evencount) {
      res = evenfirst; // Must start with even at index 1
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/