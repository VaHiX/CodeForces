// Problem: CF 1177 B - Digits Sequence (Hard Edition)
// https://codeforces.com/contest/1177/problem/B

/*
Algorithm: Digit Sequence (Hard Edition)
Approach:
- The problem requires finding the k-th digit in the infinite sequence formed by concatenating all positive integers.
- We use a mathematical approach to determine:
  1. How many digits the number at position k has.
  2. Which specific number contains the k-th digit.
  3. Which digit within that number is the answer.

Time Complexity: O(log k) - Since we iterate through the digit lengths (1, 2, 3, ...) up to the point where the k-th digit lies.
Space Complexity: O(1) - Only using a constant amount of extra space.

Techniques:
- Binary search or direct calculation using digit length groups.
- Efficient calculation of ranges of numbers with the same digit count.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll k;
  scanf("%lld", &k);
  ll num(9), pow(1), len(1);
  bool done(false);
  while (true) {
    if (k <= len * num) { // If k falls within this group of numbers having 'len' digits
      ll x = (pow - 1) + (k + len - 1) / len; // Calculate the number that contains the k-th digit
      ll y = k % len; // Position of the digit within that number (1-based)
      if (y == 0) {
        y = len; // Adjust if it's the last digit of the number
      }
      for (ll u = y; u < len; u++) { // Move x to the correct digit
        x /= 10;
      }
      printf("%lld\n", x % 10); // Output the last digit after moving x
      break;
    }
    k -= len * num; // Move k to the next digit group
    ++len; // Increase the number of digits
    pow *= 10; // Update the power of 10 for range calculation
    num *= 10; // Update count of numbers with current digit length
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/