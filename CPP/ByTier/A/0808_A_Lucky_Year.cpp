// Problem: CF 808 A - Lucky Year
// https://codeforces.com/contest/808/problem/A

/*
Purpose: Determine the number of years until the next "lucky" year.
         A lucky year contains at most one non-zero digit.
         For example: 100, 40000, 5 are lucky; 12, 3001 are not.

Algorithm:
    1. Extract the most significant digit (msb) of the input year n.
    2. Create the next possible lucky number by increasing the msb by 1
       and padding with zeros to match the original number's length.
    3. Return the difference between this new lucky number and the current year.

Time Complexity: O(log n) - where log n represents the number of digits in n.
Space Complexity: O(1) - only using a constant amount of extra space.

Techniques:
    - Digit manipulation to extract most significant digit
    - Mathematical computation to construct next lucky number
*/

#include <cstdio>
int main() {
  long long n;
  scanf("%lld", &n);
  int count(0), msb(0);
  long long q = n, r(1);
  while (q > 0) {
    msb = (q % 10);  // Extract the last digit (least significant)
    r *= 10;         // Shift r to the left to account for next digit
    q /= 10;         // Remove the last digit from q
  }
  r /= 10;             // Adjust r to represent the correct power of 10
  r *= (msb + 1);      // Create next lucky number by incrementing msb
  printf("%lld\n", r - n);  // Output the difference
  return 0;
}


// https://github.com/VaHiX/CodeForces/