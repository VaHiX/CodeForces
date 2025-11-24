// Problem: CF 630 L - Cracking the Code
// https://codeforces.com/contest/630/problem/L

/*
 * Code to crack the activation code of a program based on a specific algorithm.
 *
 * Algorithm:
 * 1. Take a 5-digit number as input.
 * 2. Rearrange its digits in order: <1st><3rd><5th><4th><2nd> to form a new number.
 * 3. Raise this new number to the 5th power.
 * 4. Output the last 5 digits of the result.
 *
 * Time Complexity: O(1) - The operations are constant time since we deal with fixed-size inputs (5 digits).
 * Space Complexity: O(1) - Only a fixed amount of memory is used (a vector of size 5, and a few variables).
 */

#include <cstdio>
#include <vector>

int main() {
  const int D = 5;  // Number of digits in input
  const int P = 5;  // Power to raise the shuffled number to
  const int M = 100000;  // Modulus to get last 5 digits

  long x;
  scanf("%ld\n", &x);  // Read the 5-digit number

  std::vector<int> dv(D, 0);  // Array to store individual digits
  for (int p = 0; p < D; p++) {  // Extract digits from right to left
    dv[p] = x % 10;
    x /= 10;
  }

  // Rearrange the digits according to the rule: <1st><3rd><5th><4th><2nd>
  long long y = 10000 * dv[D - 1] + 1000 * dv[D - 3] + 100 * dv[0] +
                10 * dv[D - 4] + dv[D - 2];

  long long ans(1);  // Initialize result as 1
  for (int p = 0; p < P; p++) {  // Raise y to the 5th power, with modulo at each step
    ans *= y;
    ans %= M;
  }

  printf("%05lld\n", ans);  // Print result with leading zeros if needed
  return 0;
}


// https://github.com/VaHiX/CodeForces/