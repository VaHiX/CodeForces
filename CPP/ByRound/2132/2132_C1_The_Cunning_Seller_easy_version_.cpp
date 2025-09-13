/**
 * Problem: CF2132C1 - The Cunning Seller (Easy Version)
 *
 * This program calculates a special sum based on the ternary (base-3)
 * representation of a number. For each digit in the ternary representation, it
 * calculates a weighted sum where the weight depends on the digit's position
 * and value.
 *
 * Approach:
 * 1. Convert the number to base-3 (ternary)
 * 2. For each digit in the ternary representation, calculate its contribution
 * to the sum
 * 3. The contribution is calculated as: digit * (3^position + 3^(position-1) *
 * position)
 *
 * Time Complexity: O(T * log₃(n))
 *   - T: Number of test cases
 *   - For each test case, we process each digit of n in base-3
 *
 * Space Complexity: O(1)
 *   - Uses constant extra space regardless of input size
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  // Optimize I/O operations
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int testCases;
  cin >> testCases;

  while (testCases--) {
    ll number;
    cin >> number;

    ll result = 0;         // Stores the final result
    ll position = 0;       // Current digit position (0-based from right)
    ll positionWeight = 1; // 3^position

    while (number > 0) {
      int digit = number % 3; // Get current ternary digit

      // Calculate contribution of current digit to the result
      // The formula is: digit * (3^position + 3^(position-1) * position)
      // Which simplifies to: digit * positionWeight * (1 + position/3)
      result += digit * (positionWeight + (positionWeight / 3) * position);

      // Move to next digit
      number /= 3;
      position++;
      positionWeight *= 3;
    }

    cout << result << "\n";
  }

  return 0;
}