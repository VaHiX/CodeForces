/**
 * @file 2130_B_Pathless.cpp
 * @brief Solution for Codeforces problem 2130B - Pathless
 *
 * Problem: Given an array of integers (0s, 1s, and 2s), determine if it's
 * possible to partition the array into three parts (all 0s, then all 2s, then
 * all 1s) such that the sum of elements equals the target sum 's'. If not
 * possible, return -1.
 *
 * Approach:
 * 1. For each test case:
 *    a. Calculate the current sum of the array
 *    b. Check if the target sum is achievable based on the current sum
 *    c. If achievable, partition the array into 0s, 2s, and 1s
 *    d. Output the partitioned array or -1 if not possible
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the partitioned arrays
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * @brief Solves a single test case of the problem
 * @param arraySize The size of the input array
 * @param targetSum The target sum to achieve
 */
void solveTestCase(int arraySize, int targetSum) {
  vector<int> numbers(arraySize);
  int currentSum = 0;

  // Read input and calculate initial sum
  for (int i = 0; i < arraySize; ++i) {
    cin >> numbers[i];
    currentSum += numbers[i];
  }

  int remaining = targetSum - currentSum;

  // Check if the target sum is achievable
  if (targetSum < currentSum || remaining == 1) {
    // Categorize numbers into separate vectors
    vector<int> zeros, twos, ones;

    for (int num : numbers) {
      switch (num) {
      case 0:
        zeros.push_back(num);
        break;
      case 1:
        ones.push_back(num);
        break;
      case 2:
        twos.push_back(num);
        break;
      default:
        break; // Shouldn't happen per problem constraints
      }
    }

    // Output the partitioned array
    for (int num : zeros)
      cout << num << ' ';
    for (int num : twos)
      cout << num << ' ';
    for (int num : ones)
      cout << num << ' ';
    cout << '\n';
  } else {
    // No valid partition exists
    cout << "-1\n";
  }
}

int main() {
  // Improve I/O performance
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int numTestCases;
  cin >> numTestCases;

  while (numTestCases--) {
    int arraySize, targetSum;
    cin >> arraySize >> targetSum;
    solveTestCase(arraySize, targetSum);
  }

  return 0;
}