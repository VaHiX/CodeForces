// Problem: CF 515 C - Drazil and Factorial
// https://codeforces.com/contest/515/problem/C

/*
 * Problem: C. Drazil and Factorial
 * Purpose: Given a number consisting of digits, decompose it into digits such that 
 *          the product of factorials of these digits equals the factorial of the original number.
 *          Then, rearrange the decomposed digits to form the maximum possible number.
 * 
 * Algorithm:
 * - For each digit in the input, decompose it into prime factors that are less than or equal to 7.
 *   (because 1! = 1, 2! = 2, 3! = 6, 4! = 24 = 2^3 * 3, 5! = 120 = 2^3 * 3 * 5, 
 *    6! = 720 = 2^4 * 3^2 * 5, 7! = 5040 = 2^4 * 3^2 * 5 * 7, 8! = 40320 = 2^7 * 3^2 * 5 * 7,
 *    9! = 362880 = 2^7 * 3^4 * 5 * 7)
 * - Replace each digit with its decomposition and sort the resulting digits in descending order.
 * - Output the sorted digits to form the maximum number.
 * 
 * Time Complexity: O(n log n) where n is the number of digits in the input.
 * Space Complexity: O(n) for storing the decomposed digits.
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

// Function to decompose a digit into prime factors (2,3,5,7) and add to the existing vector
std::vector<int> addDigits(std::vector<int> prior, int input) {
  std::vector<int> output(prior);
  if (input == 2) {
    output.push_back(2);
  } else if (input == 3) {
    output.push_back(3);
  } else if (input == 4) {
    // 4! = 24 = 2 * 2 * 2 * 3 => decompose into 2,2,2,3
    output.push_back(2);
    output.push_back(2);
    output.push_back(3);
  } else if (input == 5) {
    output.push_back(5);
  } else if (input == 6) {
    // 6! = 720 = 2 * 2 * 2 * 2 * 3 * 3 * 5 => decompose into 3,5
    output.push_back(3);
    output.push_back(5);
  } else if (input == 7) {
    output.push_back(7);
  } else if (input == 8) {
    // 8! = 40320 = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 3 * 3 * 5 * 7
    output.push_back(2);
    output.push_back(2);
    output.push_back(2);
    output.push_back(7);
  } else if (input == 9) {
    // 9! = 362880 = 2 * 2 * 2 * 2 * 2 * 2 * 2 * 3 * 3 * 3 * 3 * 5 * 7
    output.push_back(2);
    output.push_back(3);
    output.push_back(3);
    output.push_back(7);
  }
  return output;
}

int main() {
  int n;
  scanf("%d\n", &n);
  std::string number;
  getline(std::cin, number);
  std::vector<int> digits;
  for (int p = 0; p < n; p++) {
    // Decompose each digit in the input number and accumulate the result in 'digits'
    digits = addDigits(digits, number[p] - '0');
  }
  // Sort digits in descending order to form the maximum number
  sort(digits.rbegin(), digits.rend());
  for (int p = 0; p < digits.size(); p++) {
    std::cout << digits[p];
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/