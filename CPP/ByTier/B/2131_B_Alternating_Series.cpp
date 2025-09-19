/**
 * Problem: CF2131B - Alternating Series
 *
 * This program generates an alternating series of numbers based on the given
 * input n. The series alternates between -1 and 2, with the last element being
 * 2 if n is odd.
 *
 * Approach:
 * 1. For each test case, read integer n
 * 2. Generate a sequence of length n where:
 *    - Odd positions (1-based) contain -1
 *    - Even positions contain 2, except possibly the last element
 *    - If n is odd, the last element is set to 1 to make the sum 1
 * 3. Print the generated sequence
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) - output is generated on the fly
 */

#include <iostream>
using namespace std;

int main() {
  // Read number of test cases
  int num_test_cases;
  cin >> num_test_cases;

  while (num_test_cases--) {
    int sequence_length;
    cin >> sequence_length;

    // Generate the alternating series
    for (int i = 1; i <= sequence_length; i++) {
      if (i % 2 == 1) {
        // Odd position: output -1
        cout << "-1";
      } else {
        // Even position: output 2, but handle the last element specially
        if (i == sequence_length && sequence_length % 2 == 1) {
          // Last element when sequence length is odd
          cout << "1";
        } else {
          // Regular even position
          cout << "2";
        }
      }

      // Add space between numbers, but not after the last one
      if (i < sequence_length) {
        cout << " ";
      }
    }
    cout << '\n';
  }

  return 0;
}