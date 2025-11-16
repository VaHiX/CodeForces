// Problem: CF 770 B - Maximize Sum of Digits
// https://codeforces.com/contest/770/problem/B

/*
B. Maximize Sum of Digits
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Anton has the integer x. He is interested what positive integer, which doesn't exceed x, has the maximum sum of digits.
Your task is to help Anton and to find the integer that interests him. If there are several such integers, determine the biggest of them.
Input
The first line contains the positive integer x (1 ≤ x ≤ 10^18) — the integer which Anton has.
Output
Print the positive integer which doesn't exceed x and has the maximum sum of digits. If there are several such integers, print the biggest of them. Printed integer must not contain leading zeros.

Algorithms/Techniques: Digit DP approach with greedy optimization
Time Complexity: O(log x)
Space Complexity: O(1)

The algorithm checks all possible numbers formed by reducing the last digit to 9 and keeping the rest,
and compares their digit sums to find the maximum.
*/

#include <stdint.h>
#include <iostream>

int sumDigits(int64_t a) {
  int sum(0);
  while (a > 0) {
    sum += a % 10; // Extract last digit and add to sum
    a /= 10;       // Remove last digit
  }
  return sum;
}

int main() {
  const int N = 18; // Maximum number of digits for 64-bit integer
  int64_t x;
  std::cin >> x;
  int sd = sumDigits(x); // Get initial digit sum
  int64_t res(x), div(1);
  for (int p = 0; p < N; p++) {
    int64_t cur = (x / div) * div - 1; // Form a number with one less than current digit at position p, rest 9s
    if (sumDigits(cur) > sd) {         // If this gives higher digit sum
      sd = sumDigits(cur);             // Update max sum
      res = cur;                       // Update result
    }
    if (div > x) {                     // Prevent overflow
      break;
    }
    div *= 10; // Move to next digit position
  }
  std::cout << res << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/