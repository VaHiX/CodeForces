// Problem: CF 672 A - Summer Camp
// https://codeforces.com/contest/672/problem/A

/*
 * Purpose: Find the nth digit in the concatenated sequence of all positive integers (12345678910111213...).
 * Algorithm: Iterate through integers starting from 1, extract each digit, and count until reaching the nth digit.
 * Time Complexity: O(log n * n) where n is up to 1000, so effectively O(1) due to small constraints.
 * Space Complexity: O(log n) for storing digits of a number, which is also effectively O(1) due to small constraint.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
const int N = 1000;

// Function to extract digits of a number and return them in order
std::vector<int> getDigits(int x) {
  std::vector<int> res;
  while (x > 0) {
    res.push_back(x % 10); // Extract last digit
    x /= 10;               // Remove last digit
  }
  std::reverse(res.begin(), res.end()); // Reverse to get correct order
  return res;
}

int main() {
  int n;
  scanf("%d\n", &n);
  int counter(0), ans(-1); // counter tracks how many digits we've seen, ans stores result

  for (int p = 1; p <= N; p++) { // Iterate through numbers 1 to 1000
    std::vector<int> digits = getDigits(p); // Get digits of current number
    for (int q = 0; q < digits.size(); q++) { // Process each digit of the current number
      if (++counter >= n) { // Increment counter and check if we've reached target
        ans = digits[q]; // Save the required digit
        break;
      }
    }
    if (ans >= 0) { // If we found the answer, stop searching
      break;
    }
  }
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/