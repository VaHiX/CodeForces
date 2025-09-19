

/**
 * @file 2130_E1_Interactive_RBS_Easy_Version.cpp
 * @brief Solution for Codeforces problem 2130E1 - Interactive RBS (Easy
 * Version)
 *
 * Problem: Given an interactive problem where we need to determine a valid
 * Regular Bracket Sequence (RBS) of length n, where each character is either
 * '(' or ')' and the sequence is properly nested.
 *
 * Approach:
 * 1. Find the first position where the sequence becomes unbalanced using binary
 * search
 * 2. Use this position to determine a pivot point
 * 3. Determine the bracket types for pairs of positions using a clever encoding
 * scheme
 * 4. Handle the last position separately if n is odd
 *
 * Time Complexity: O(n) queries with O(1) per query
 * Space Complexity: O(n) for storing the result
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Maximum sequence length
const int MAX_N = 1005;

/**
 * @brief Solves a single test case of the problem
 */
void solveTestCase() {
  int sequenceLength;
  cin >> sequenceLength;

  // Phase 1: Find the first position where the sequence becomes unbalanced
  int left = 1, right = sequenceLength;
  int firstUnbalancedPos = sequenceLength + 1; // Default to one past the end

  while (left <= right) {
    int mid = left + ((right - left) >> 1);

    // Query the first 'mid' positions
    cout << "? " << mid;
    for (int i = 1; i <= mid; ++i) {
      cout << " " << i;
    }
    cout << endl;

    int balancedSubstrings;
    cin >> balancedSubstrings;

    if (balancedSubstrings > 0) {
      firstUnbalancedPos = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  // Determine the pivot position
  int pivotPos =
      (firstUnbalancedPos == sequenceLength + 1) ? 1 : firstUnbalancedPos;

  // Phase 2: Process the sequence in pairs
  string bracketSequence;

  for (int i = 1; i < sequenceLength; i += 2) {
    // Build a query that will help us determine the bracket types for positions
    // i and i+1 The query is designed to encode the bracket types in the
    // response
    cout << "? 12";

    // Add the pattern that will help us distinguish between different bracket
    // combinations
    for (int j = 0; j < 3; ++j) {
      cout << " " << i << " " << pivotPos << " " << pivotPos;
    }
    cout << " " << i + 1 << " " << pivotPos << " " << pivotPos << endl;

    // Get the encoded bracket pattern
    int patternCode;
    cin >> patternCode;

    // Map the pattern code to the corresponding bracket pair
    if (patternCode == 4) {
      bracketSequence += "((";
    } else if (patternCode == 3) {
      bracketSequence += "()";
    } else if (patternCode == 1) {
      bracketSequence += ")(";
    } else { // patternCode == 0 or 2
      bracketSequence += "))";
    }
  }

  // Handle the last position if the sequence length is odd
  if (sequenceLength % 2 == 1) {
    // Query to determine the bracket type for the last position
    cout << "? 2 " << sequenceLength << " " << pivotPos << endl;

    int lastBracketType;
    cin >> lastBracketType;

    // The response tells us if it's an opening or closing bracket
    bracketSequence += (lastBracketType == 1) ? "(" : ")";
  }

  // Output the final answer
  cout << "! " << bracketSequence << endl;
}

int main() {
  // Improve I/O performance
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int testCases;
  cin >> testCases;

  while (testCases--) {
    solveTestCase();
  }

  return 0;
}