

/**
 * @file 2130_E2_Interactive_RBS_Medium_Version.cpp
 * @brief Solution for Codeforces problem 2130E2 - Interactive RBS (Medium
 * Version)
 *
 * Problem: Given an interactive problem where we need to determine a valid
 * Regular Bracket Sequence (RBS) of length n, where each character is either
 * '(' or ')' and the sequence is properly nested.
 *
 * Approach:
 * 1. Find a pivot point where the sequence first becomes unbalanced using
 * binary search
 * 2. Process the sequence in chunks of 7 characters to minimize the number of
 * queries
 * 3. Use binary encoding to determine multiple brackets in a single query
 *
 * Time Complexity: O(n) queries with O(n) total characters
 * Space Complexity: O(n) additional space
 */

#include <algorithm>
#include <iostream>
#include <string>
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
  int firstUnbalancedPos = sequenceLength; // Default to the end of the sequence

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

  // If the entire sequence is balanced, use the first position as pivot
  int pivotPos =
      (firstUnbalancedPos == sequenceLength + 1) ? 1 : firstUnbalancedPos;

  // Phase 2: Process the sequence in chunks of 7 characters
  string bracketSequence;
  const int CHUNK_SIZE = 7; // Process 7 characters at a time

  for (int chunkStart = 1; chunkStart <= sequenceLength;
       chunkStart += CHUNK_SIZE) {
    int chunkEnd = min(chunkStart + CHUNK_SIZE - 1, sequenceLength);
    int chunkLength = chunkEnd - chunkStart + 1;

    // Calculate the query size: (2^(chunkLength+1) - 1) + (chunkLength - 1)
    int querySize = ((1 << (chunkLength + 1)) - 1) + (chunkLength - 1);
    cout << "? " << querySize;

    // Build the query using binary encoding
    int numRepetitions = 1;
    for (int posInChunk = 0; posInChunk < chunkLength; ++posInChunk) {
      int currentPos = chunkStart + posInChunk;

      // Add the current position 'numRepetitions' times
      for (int k = 0; k < numRepetitions; ++k) {
        cout << " " << currentPos;
      }

      // Add the pivot position 'numRepetitions + 1' times
      for (int k = 0; k < numRepetitions; ++k) {
        cout << " " << pivotPos;
      }
      cout << " " << pivotPos;

      numRepetitions *= 2; // Double the repetitions for the next position
    }
    cout << endl;

    // Get the query result and decode the bracket types
    int queryResult;
    cin >> queryResult;

    // Decode the result to determine each bracket type
    for (int posInChunk = 0; posInChunk < chunkLength; ++posInChunk) {
      // The least significant bit tells us if this is an opening or closing
      // bracket
      if (queryResult & 1) {
        bracketSequence += "(";
      } else {
        bracketSequence += ")";
      }
      queryResult >>= 1; // Move to the next bit
    }
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