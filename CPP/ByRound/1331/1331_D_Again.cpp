// Problem: CF 1331 D - Again?
// https://codeforces.com/contest/1331/problem/D

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::string s;           // Declare string to store input hexadecimal number
  std::cin >> s;           // Read the 7-digit hexadecimal number from input
  int n = (s[s.size() - 1] - '0');  // Extract the last digit and convert to integer
  printf("%d\n", n % 2);   // Output 0 if even, 1 if odd (check if last digit is even or odd)
  return 0;
}

/*
Problem: D. Again?
Purpose: Determines if the last digit of a 7-digit hexadecimal number is even or odd.
Algorithm: Extract the last character of the string, convert it to integer, and check if it's even (0) or odd (1).
Time Complexity: O(1) - Constant time as we only access the last character
Space Complexity: O(1) - Constant space as we only store a fixed-size string and integer
*/

// https://github.com/VaHiX/codeForces/