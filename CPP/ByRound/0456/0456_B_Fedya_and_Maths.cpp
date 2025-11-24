// Problem: CF 456 B - Fedya and Maths
// https://codeforces.com/contest/456/problem/B

/*
B. Fedya and Maths
time limit per test
1 second
memory limit per test
256 megabytes
input
stdin
output
stdout
Fedya studies in a gymnasium. Fedya's maths hometask is to calculate the following expression:
(1^n + 2^n + 3^n + 4^n) mod 5
for given value of n. Fedya managed to complete the task. Can you? Note that given number n can be extremely large (e.g. it can exceed any integer type of your programming language).
Input
The single line contains a single integer n (0 <= n <= 10^15). The number doesn't contain any leading zeroes.
Output
Print the value of the expression without leading zeros.

Algorithms/Techniques:
- Modulo arithmetic with cyclic patterns
- Observing that the last two digits of n determine the result due to periodicity of powers modulo 5
- Time complexity: O(1) - constant time since we only look at last two digits
- Space complexity: O(1) - constant space for storing input and intermediate values

Note to the first sample:
*/

#include <cstdio>
#include <iostream>
#include <string>

int main() {
  std::string input;
  std::cin >> input;
  int N = input.size();
  int n = 0;
  if (N >= 2) {
    n = 10 * (input[N - 2] - '0');  // Extract second last digit and multiply by 10
  }
  n += input[N - 1] - '0';  // Add last digit to form the last two digits of n
  int result(0);
  if (n % 4 == 0) {
    result = (1 + 1 + 1 + 1) % 5;  // Pattern when n % 4 == 0
  } else if (n % 4 == 1) {
    result = (1 + 2 + 3 + 4) % 5;  // Pattern when n % 4 == 1
  } else if (n % 4 == 2) {
    result = (1 + 4 + 4 + 1) % 5;  // Pattern when n % 4 == 2
  } else if (n % 4 == 3) {
    result = (1 + 3 + 2 + 4) % 5;  // Pattern when n % 4 == 3
  }
  printf("%d\n", result);
  return 0;
}


// https://github.com/VaHiX/codeForces/