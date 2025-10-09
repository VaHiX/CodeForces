// Problem: CF 2132 D - From 1 to Infinity
// https://codeforces.com/contest/2132/problem/D

/*
D. From 1 to Infinity
Algorithm: Digit enumeration and mathematical summation
Time Complexity: O(log k) per test case
Space Complexity: O(1)

This problem involves finding the sum of digits in the first k digits of the infinite sequence formed by concatenating all positive integers (123456789101112...).

Approach:
1. First, we determine which number contains the k-th digit by counting how many digits are contributed by numbers with different digit lengths (1-digit, 2-digit, etc.).
2. Then, locate the exact number and digit within that number.
3. Finally, calculate the sum of all digits from the beginning of the sequence up to the k-th digit using mathematical formulas for digit sums in ranges.

The algorithm uses:
- Binary-like search or direct calculation to find where the k-th digit falls
- Mathematical computation for efficient summation of digits in prefix ranges
*/

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
using ll = long long;

void calculateDigitSum(ll n) {
  ll numbersInRange = 9;         // Number of numbers with current digit count
  ll digitsPerNumber = 1;        // Digits per number in current range
  ll totalDigits = 0;            // Total digits accounted for so far

  while (n > numbersInRange * digitsPerNumber) {
    n -= numbersInRange * digitsPerNumber;         // Subtract digits from this range
    totalDigits += numbersInRange * digitsPerNumber;
    numbersInRange *= 10;                          // Move to next digit group (1->10->100...)
    digitsPerNumber++;                             // Increase digits per number
  }

  ll number = (numbersInRange / 9) + ((n - 1) / digitsPerNumber); // Find actual number containing k-th digit
  string numberStr = to_string(number);                           // Convert to string for easy access

  ll digitSum = 0;
  for (int i = 0; i < (n - 1) % digitsPerNumber + 1; i++) {
    digitSum += numberStr[i] - '0';  // Accumulate sum of digits up to the target
  }

  ll cumulativeSum = 0;
  ll powerOfTen = numbersInRange / 9;       // Starting power of ten for range calculations
  ll remainingDigits = digitsPerNumber;     // Remaining digits in current number
  ll prefixSum = 0;                         // Prefix digit sum

  for (int i = 0; i < numberStr.size(); i++) {
    ll currentDigit = numberStr[i] - '0';                           // Current digit value
    digitSum += currentDigit * (remainingDigits - 1) * powerOfTen * 9 / 2;  // Sum from higher-order digits
    digitSum += currentDigit * (2 * prefixSum + currentDigit - 1) / 2 * powerOfTen; // Sum from lower-order digits
    powerOfTen /= 10;
    remainingDigits--;
    prefixSum += currentDigit;
  }

  cout << digitSum << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int testCases;
  cin >> testCases;
  while (testCases--) {
    ll position;
    cin >> position;
    calculateDigitSum(position);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/