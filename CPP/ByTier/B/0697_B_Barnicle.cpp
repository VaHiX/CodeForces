// Problem: CF 697 B - Barnicle
// https://codeforces.com/contest/697/problem/B

/*
Purpose: Convert a scientific notation number of the form "a.deb" to its decimal representation.
         The algorithm processes the input string to extract the mantissa and exponent, 
         then constructs the output decimal string by handling decimal point placement and 
         trailing zeros correctly.

Algorithms/Techniques:
- String parsing to extract parts of scientific notation
- Simulation of decimal point movement based on exponent
- Handling of leading/trailing zeros and special cases like 0.000...000

Time Complexity: O(n) where n is the length of the input string x
Space Complexity: O(n) for storing the digits vector

*/
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::string x;
  std::cin >> x;
  std::vector<char> digits; // Store all digits of mantissa (excluding decimal point)
  digits.push_back(x[0]);   // First digit of mantissa
  int exp(0);               // Exponent value
  bool secondPart(false);   // Flag to indicate if we're parsing the exponent part
  bool allZeros(1);         // Check if all digits are zero

  // Loop through the string to parse mantissa and exponent
  for (int p = 2; p < x.size(); p++) {
    if (x[p] == 'e') {
      secondPart = true;   // Start parsing exponent
    } else if (secondPart) {
      exp = 10 * exp + (x[p] - '0');  // Convert exponent string to integer
    } else if ('0' <= x[p] && x[p] <= '9') {
      allZeros &= (x[p] == '0');      // Track if all digits are zero
      digits.push_back(x[p]);         // Add digit to the mantissa
    }
  }

  // Special case: if all digits are zero, output "0" followed by exponent number of zeros
  if (allZeros) {
    std::cout << digits[0];  // Print '0'
    while (exp--) {
      std::cout << '0';     // Print required number of zeros
    }
    return 0;
  }

  int index = 0;            // Cursor to traverse mantissa digits
  ++exp;                    // Adjust exponent to account for the decimal point placement

  // Special handling for the case when first digit is '0' and exp is 1
  if (digits[index] == '0' && exp == 1) {
    std::cout << '0';
    ++index;
    --exp;
  }

  // Process digits before the decimal point
  while (index < digits.size() && exp > 0) {
    if (index == 0 && digits[index] == '0') {
      ++index;
      --exp;
      continue;
    }
    std::cout << digits[index];  // Output current digit
    ++index;
    --exp;
  }

  // If exponent is still positive, append zeros
  if (exp > 0) {
    while (exp--) {
      std::cout << '0';
    }
  } else if (index < digits.size()) {
    // If there are remaining digits, output decimal point and the rest
    std::cout << ".";
    for (int p = index; p < digits.size(); p++) {
      std::cout << digits[p];
    }
  }

  return 0;
}


// https://github.com/VaHiX/CodeForces/