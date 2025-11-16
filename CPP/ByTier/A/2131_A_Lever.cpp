// Problem: CF 2131 A - Lever
// https://codeforces.com/contest/2131/problem/A

/*
 * Problem: The Lever
 * 
 * Purpose: This code determines the number of iterations required for a process
 *          that adjusts elements of array 'a' to match array 'b'. In each iteration,
 *          we can decrease an element of 'a' if it's greater than the corresponding
 *          element in 'b', and increase an element of 'a' if it's smaller.
 *          The process stops when no more decreases are possible.
 *
 * Algorithm:
 *   - For each test case, iterate through arrays 'a' and 'b'.
 *   - Compute how much we need to decrease elements in 'a' to match or go below 'b'.
 *   - The number of iterations is the sum of such differences plus one.
 *
 * Time Complexity: O(n) per test case, where n is the length of the arrays.
 * Space Complexity: O(n) for storing the input arrays.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int num_test_cases;
  cin >> num_test_cases;
  while (num_test_cases--) {
    int num_weights;
    cin >> num_weights;
    vector<int> current_weights(num_weights + 10); // Extra space for 1-based indexing
    vector<int> target_weights(num_weights + 10); // Extra space for 1-based indexing
    for (int i = 1; i <= num_weights; i++) {
      cin >> current_weights[i];
    }
    int total_difference = 0;
    for (int i = 1; i <= num_weights; i++) {
      cin >> target_weights[i];
      // Calculate how much 'current_weights[i]' exceeds 'target_weights[i]'
      total_difference += max(0, current_weights[i] - target_weights[i]);
    }
    cout << total_difference + 1 << '\n'; // Add 1 for the final iteration where no decreases were possible
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/