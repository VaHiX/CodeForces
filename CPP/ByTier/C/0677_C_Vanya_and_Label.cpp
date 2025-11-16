// Problem: CF 677 C - Vanya and Label
// https://codeforces.com/contest/677/problem/C

/*
* Purpose: This code calculates the number of pairs of 64-based strings of length n
*          such that their bitwise AND equals the given string s.
*          Each character in the string is converted to its base-64 representation,
*          then for each bit position, we count how many bits are zero in s.
*          For each zero bit, there are 3 valid combinations from two 6-bit numbers:
*          (0,0), (0,1), (1,0) - and we multiply the result by 3 for each such bit.
*
* Algorithm: 
* 1. Convert each character of input string to a base-64 integer.
* 2. For each such integer, count how many of its 6 bits are zero.
* 3. For each zero bit, multiply result by 3 (since there are 3 ways to assign 
*    bits such that their AND gives 0).
* 4. Return final result modulo 10^9 + 7.
*
* Time Complexity: O(n), where n is the length of input string.
* Space Complexity: O(1), only using fixed size variables.
*/

#include <iostream>
#include <string>

const long long MOD = 1000000007;

// Function to count number of zero bits in 6-bit representation of a char
int nullBits(char x) {
  const int L = 6;
  int a(0);
  if ('0' <= x && x <= '9') {
    a = x - '0';  // Convert digit to int
  } else if ('A' <= x && x <= 'Z') {
    a = x - 'A' + 10;  // Convert uppercase letter to int
  } else if ('a' <= x && x <= 'z') {
    a = x - 'a' + 36;  // Convert lowercase letter to int
  } else if (x == '-') {
    a = 62;  // Special case for '-'
  } else if (x == '_') {
    a = 63;  // Special case for '_'
  }
  int nb(0);
  for (int p = 0; p < L; p++) {
    nb += (a % 2 == 0);  // Check if bit is 0
    a /= 2;  // Move to next bit
  }
  return nb;
}

int main() {
  std::string s;
  std::cin >> s;
  long long res(1);
  for (long p = 0; p < s.size(); p++) {
    int nb = nullBits(s[p]);  // Get number of zero bits for current char
    for (int q = 0; q < nb; q++) {
      res *= 3;  // Multiply by 3 for each zero bit
      res %= MOD;  // Keep result within modulo
    }
  }
  std::cout << res << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/