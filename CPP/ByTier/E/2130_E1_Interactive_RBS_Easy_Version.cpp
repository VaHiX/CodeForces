// Problem: CF 2130 E1 - Interactive RBS (Easy Version)
// https://codeforces.com/contest/2130/problem/E1

/*
 * Problem: Interactive RBS (Easy Version)
 * Purpose: Reveal a hidden bracket sequence of length n using at most 550 queries.
 * Algorithm:
 *   1. First, find the first unbalanced position using binary search:
 *      - Query substrings of increasing length starting from 1
 *      - If f(substring) > 0, it means there's a valid bracket pair -> move left
 *      - Otherwise, continue right.
 *   2. Then determine each pair of adjacent brackets using queries with 3 indices:
 *      - Each query involves 3 indices to extract 3-character patterns
 *      - Based on returned values, deduce the type of brackets: "((", "()", ")(", "))"
 *   3. Handle odd-length sequences separately by querying the last character.
 *
 * Time Complexity: O(n log n + n) = O(n log n), due to binary search (log n) and iterating through pairs
 * Space Complexity: O(n), to store the reconstructed bracket sequence
 */

#include <iostream>
#include <string>

using namespace std;
const int MAX_N = 1005;

void solveTestCase() {
  int sequenceLength;
  cin >> sequenceLength;
  int left = 1, right = sequenceLength;
  int firstUnbalancedPos = sequenceLength + 1;
  
  // Binary search to find the first unbalanced position
  while (left <= right) {
    int mid = left + ((right - left) >> 1); // Midpoint calculation using bit shift for integer division
    cout << "? " << mid;
    for (int i = 1; i <= mid; ++i) { // Query first 'mid' indices
      cout << " " << i;
    }
    cout << endl;
    int balancedSubstrings;
    cin >> balancedSubstrings;
    if (balancedSubstrings > 0) { // If some valid bracket pairs exist in this substring
      firstUnbalancedPos = mid;
      right = mid - 1; // Move left to find earlier unbalance
    } else {
      left = mid + 1; // Move right since no valid brackets found
    }
  }
  
  // If all substrings were balanced, pivot is at the beginning
  int pivotPos =
      (firstUnbalancedPos == sequenceLength + 1) ? 1 : firstUnbalancedPos;
  
  string bracketSequence;
  
  // Process pairs of characters to find patterns
  for (int i = 1; i < sequenceLength; i += 2) {
    cout << "? 12"; // Query involving 12 indices
    for (int j = 0; j < 3; ++j) {
      // Add same indices for pattern detection: i, pivotPos, pivotPos
      cout << " " << i << " " << pivotPos << " " << pivotPos;
    }
    // Additional index for the next character
    cout << " " << i + 1 << " " << pivotPos << " " << pivotPos << endl;
    int patternCode;
    cin >> patternCode;
    if (patternCode == 4) {
      bracketSequence += "(("; // Pattern indicates two opening brackets
    } else if (patternCode == 3) {
      bracketSequence += "()"; // Pattern indicates one opening, one closing
    } else if (patternCode == 1) {
      bracketSequence += ")("; // Pattern indicates one closing, one opening
    } else {
      bracketSequence += "))"; // Pattern indicates two closing brackets
    }
  }
  
  // Handle the case when length is odd
  if (sequenceLength % 2 == 1) {
    cout << "? 2 " << sequenceLength << " " << pivotPos << endl;
    int lastBracketType;
    cin >> lastBracketType;
    bracketSequence += (lastBracketType == 1) ? "(" : ")"; // Determine the final bracket
  }
  
  cout << "! " << bracketSequence << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int testCases;
  cin >> testCases;
  while (testCases--) {
    solveTestCase();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/