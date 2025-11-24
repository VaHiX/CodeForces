// Problem: CF 538 B - Quasi Binary
// https://codeforces.com/contest/538/problem/B

/*
Purpose: 
This code solves the problem of representing a given positive integer n as a sum of the minimum number of quasibinary numbers.
A quasibinary number contains only digits 0 and 1.
The approach is to determine the maximum digit in the decimal representation of n, which gives the minimum number of quasibinary numbers required.
Each quasibinary number is constructed by placing 1s in positions where the digit is at least the current row number.

Algorithms/Techniques:
- Extract digits of input number n from right to left
- Reverse the digit sequence to process from left to right
- For each digit, determine how many quasibinary numbers are needed based on the digit's value
- Construct each quasibinary number by checking the position in each digit

Time Complexity: O(log n) - where log n is the number of digits in n, as we iterate through digits once and for each digit we process up to log n positions.

Space Complexity: O(log n) - to store the digits and the constructed quasibinary numbers.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld\n", &n);
  std::vector<int> source;  // Store digits of n in reversed order
  int maxDigit(0);  // Track the largest digit in n
  while (n > 0) {
    int d = n % 10;  // Extract last digit
    n /= 10;  // Remove last digit
    source.push_back(d);  // Add to source
    if (d > maxDigit) {  // Update maximum digit
      maxDigit = d;
    }
  }
  std::reverse(source.begin(), source.end());  // Reverse source to get normal order
  std::vector<long> numbers(maxDigit);  // Vector to hold the quasibinary numbers
  for (int s = 0; s < source.size(); s++) {  // For each digit
    int d = source[s];
    for (int p = 0; p < maxDigit; p++) {  // For each potential quasibinary number
      numbers[p] = 10 * numbers[p] + (p < d);  // Build the number by placing 1s where needed
    }
  }
  printf("%d\n", maxDigit);  // Print number of quasibinary numbers
  for (int p = 0; p < numbers.size(); p++) {  // Print all constructed quasibinary numbers
    printf("%ld ", numbers[p]);
  }
  puts("");  // Print newline
  return 0;
}


// https://github.com/VaHiX/CodeForces/