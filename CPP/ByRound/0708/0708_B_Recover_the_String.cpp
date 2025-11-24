// Problem: CF 708 B - Recover the String
// https://codeforces.com/contest/708/problem/B

/*
 * Problem: Recover the String
 * 
 * Given four integers a00, a01, a10, a11 representing the number of subsequences
 * of length 2 in a binary string s, construct any valid string s or determine
 * that no such string exists.
 * 
 * Algorithm:
 * 1. Check for trivial case where all counts are zero (output "0").
 * 2. Use mathematical deduction to determine number of 0s and 1s in the string:
 *    - If a00 = x(x-1)/2, then number of 0s is x
 *    - If a11 = y(y-1)/2, then number of 1s is y
 * 3. Validate if the given counts are consistent with each other.
 * 4. Build the string greedily by choosing to place 0 or 1 based on remaining
 *    counts to satisfy a01 and a10 constraints.
 * 
 * Time Complexity: O(1) - we compute the values in constant time (as a00, a11
 *          can have at most sqrt(1e9) values for iterations).
 * Space Complexity: O(1) - only using a few variables.
 */

#include <cstdio>
int main() {
  long zz, zn, nz, nn;
  scanf("%ld %ld %ld %ld", &zz, &zn, &nz, &nn);
  if (zz + nz + zn + nn == 0) {
    puts("0");
    return 0;
  }
  long zeros(0), ones(0), num0(0), num1(0);
  // Determine the number of zeros by checking increasing triangular numbers
  while (num0 + zeros <= zz) {
    num0 += zeros;
    ++zeros;
  }
  // Determine the number of ones by checking increasing triangular numbers
  while (num1 + ones <= nn) {
    num1 += ones;
    ++ones;
  }
  // Special case handling for edge conditions
  if (nz == 0 && zn == 0 && zz == 0) {
    zeros = 0;
  }
  if (nn == 0 && nz == 0 && zn == 0) {
    ones = 0;
  }
  long length = ones + zeros;
  // Check consistency of the given values
  if (ones * zeros != nz + zn || num0 != zz || num1 != nn) {
    puts("Impossible");
    return 0;
  }
  // Construct the string greedily
  while (length--) {
    if (zn >= ones) {
      printf("0");
      zn -= ones;
      --zeros;
    } else {
      printf("1");
      nz -= zeros;
      --ones;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/