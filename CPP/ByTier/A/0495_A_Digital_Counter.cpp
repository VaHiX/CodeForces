// Problem: CF 495 A - Digital Counter
// https://codeforces.com/contest/495/problem/A

/*
Purpose: This program calculates the number of "good" integers that could have been displayed on a broken digital counter.
         A "good" integer is one that, when displayed with the current (possibly broken) digits, could produce the given number n.
         Each digit is made up of 7 light sticks, and a broken stick means a digit might be misread.
         The counter always shows a two-digit number (00-99), with leading zeros allowed.

Algorithms/Techniques:
- Precomputed lookup table for number of light sticks required for each digit (0-9)
- For a given input n, we compute how many combinations of two digits (from 00 to 99) could show n,
  taking into account that some digits might be broken and cause a misread.

Time Complexity: O(1) - We perform a constant number of operations regardless of input.
Space Complexity: O(1) - We use only a fixed-size vector and a few variables.

*/

#include <cstdio>
#include <vector>
int main() {
  // Vector storing number of light sticks for each digit (0-9)
  std::vector<int> digits;
  digits.push_back(2);  // digit 0 needs 2 sticks
  digits.push_back(7);  // digit 1 needs 7 sticks
  digits.push_back(2);  // digit 2 needs 2 sticks
  digits.push_back(3);  // digit 3 needs 3 sticks
  digits.push_back(3);  // digit 4 needs 3 sticks
  digits.push_back(4);  // digit 5 needs 4 sticks
  digits.push_back(2);  // digit 6 needs 2 sticks
  digits.push_back(5);  // digit 7 needs 5 sticks
  digits.push_back(1);  // digit 8 needs 1 stick
  digits.push_back(2);  // digit 9 needs 2 sticks

  int input;
  scanf("%d\n", &input);
  // Calculate total combinations by multiplying number of ways to show tens digit
  // with number of ways to show units digit based on their light stick counts
  int output = digits[input / 10] * digits[input % 10];
  printf("%d\n", output);
  return 0;
}


// https://github.com/VaHiX/CodeForces/