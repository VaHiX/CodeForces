/**
 * Problem: CF2132D - From 1 to Infinity
 *
 * This program calculates the sum of digits of numbers from 1 to n, where n can
 * be very large. It uses mathematical patterns to efficiently compute the sum
 * without iterating through each number.
 *
 * Approach:
 * 1. Find the range where the target digit sequence lies
 * 2. Calculate the sum using mathematical formulas for digit sums
 * 3. Optimize the calculation using precomputed values and patterns
 *
 * Time Complexity: O(log10(n))
 *   - The main loop runs in logarithmic time relative to the input number
 *   - Each iteration processes a power of 10 more digits
 *
 * Space Complexity: O(1)
 *   - Uses constant extra space regardless of input size
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * Calculates the sum of digits for numbers from 1 to the number containing the
 * nth digit
 * @param n The position of the digit to find
 */
void calculateDigitSum(ll n) {
  // Initialize variables to track the current range
  ll numbersInRange =
      9; // Number of numbers in current range (1-digit: 9, 2-digit: 90, etc.)
  ll digitsPerNumber = 1; // Number of digits in current range
  ll totalDigits = 0;     // Total digits processed so far

  // Find the range where the nth digit is located
  while (n > numbersInRange * digitsPerNumber) {
    n -= numbersInRange * digitsPerNumber;
    totalDigits += numbersInRange * digitsPerNumber;
    numbersInRange *= 10;
    digitsPerNumber++;
  }

  // Calculate the exact number containing the nth digit
  ll number = (numbersInRange / 9) + ((n - 1) / digitsPerNumber);
  string numberStr = to_string(number);

  // Calculate the digit at position n
  ll digitSum = 0;
  for (int i = 0; i < (n - 1) % digitsPerNumber + 1; i++) {
    digitSum += numberStr[i] - '0';
  }

  // Calculate the sum of all digits up to the current number
  ll cumulativeSum = 0;
  ll powerOfTen = numbersInRange / 9; // 1, 10, 100, etc.
  ll remainingDigits = digitsPerNumber;
  ll prefixSum = 0; // Sum of digits before current position

  for (int i = 0; i < numberStr.size(); i++) {
    ll currentDigit = numberStr[i] - '0';

    // Add sum of all digits at current position for all numbers in range
    digitSum += currentDigit * (remainingDigits - 1) * powerOfTen * 9 / 2;

    // Add sum of prefix digits multiplied by the count of numbers
    digitSum +=
        currentDigit * (2 * prefixSum + currentDigit - 1) / 2 * powerOfTen;

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