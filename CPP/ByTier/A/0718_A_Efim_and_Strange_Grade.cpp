// Problem: CF 718 A - Efim and Strange Grade
// https://codeforces.com/contest/718/problem/A

/*
Purpose: This code solves the problem of finding the maximum possible grade after at most t seconds of rounding operations on a decimal number.
         Each second, the grade can be rounded to any decimal place, and the goal is to maximize the result.

Algorithm:
- Parse the input number into parts: integer part (before decimal) and fractional part (after decimal).
- For each rounding operation, identify the first digit in the fractional part that is >= 5.
- Update digits from right to left (fractional part) and integer part as needed, simulating rounding.
- Reconstruct and print the final number.

Time Complexity: O(n + t) where n is the length of the number string.
Space Complexity: O(n) for storing the digits in vectors.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  long n, t;
  std::cin >> n >> t;
  std::string s;
  std::cin >> s;
  std::vector<int> before;
  std::vector<int> after;
  bool dot(false);
  for (int p = 0; p < s.size(); p++) {
    if (s[p] == '.') {
      dot = true;
      continue;
    }
    if (!dot) {
      before.push_back(s[p] - '0'); // Store integer part
    } else if (dot) {
      after.push_back(s[p] - '0'); // Store fractional part
    }
  }
  int index(0);
  bool incrInt(false);
  // Find the first digit >= 5 (this will be the start of the rounding process)
  for (int p = 0; p < after.size(); p++) {
    if (after[p] >= 5) {
      index = p;
      break;
    }
  }
  // Perform up to t rounding steps
  while (t--) {
    if (after[index] < 5) {
      break; // No more rounding required
    }
    after[index] = 0; // Set current digit to 0
    --index; // Move to the previous digit
    if (index < 0) {
      incrInt = true; // If we go out of bounds, increment integer part
      break;
    } else {
      ++after[index]; // Increment the previous digit
    }
  }
  // Propagate carry in integer part
  for (int p = before.size() - 1; p >= 0; p--) {
    if (incrInt) {
      ++before[p];
    }
    if (before[p] > 9) {
      before[p] = 0;
      incrInt = true;
    } else {
      incrInt = false;
      break;
    }
  }
  // Print result
  if (incrInt) {
    std::cout << "1"; // If we needed to carry over to a new integer digit
  }
  for (int p = 0; p < before.size(); p++) {
    std::cout << before[p];
  }
  if (index >= 0) {
    std::cout << ".";
    for (int p = 0; p <= index; p++) {
      std::cout << after[p]; // Print fractional part up to index
    }
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/