

/**
 * @file 2130_D_Stay_or_Mirror.cpp
 * @brief Solution for Codeforces problem 2130D - Stay or Mirror
 *
 * Problem: Given a permutation of integers from 1 to n, we need to calculate
 * the minimum number of operations required to sort the permutation. In each
 * operation, we can either keep an element as is or replace it with its mirror
 * position in the sequence.
 *
 * Approach:
 * 1. For each element in the permutation, count how many elements after it are
 * greater than it.
 * 2. For each element, calculate the minimum between:
 *    - The count of greater elements after it (keeping it as is)
 *    - The count of elements that would be less than it if mirrored (n - v[i] -
 * count)
 * 3. Sum these minimum values to get the total minimum operations needed.
 *
 * Time Complexity: O(n^2) per test case, where n is the length of the
 * permutation Space Complexity: O(n) to store the permutation
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

/**
 * @brief Solves a single test case of the problem
 * @param n The size of the permutation
 * @param permutation The permutation of integers from 1 to n
 * @return The minimum number of operations needed to sort the permutation
 */
ll solveTestCase(int n, const vector<int> &permutation) {
  ll totalOperations = 0;

  for (int currentIdx = 0; currentIdx < n; ++currentIdx) {
    // Count number of elements after currentIdx that are greater than
    // permutation[currentIdx]
    int greaterAfter = 0;
    for (int nextIdx = currentIdx + 1; nextIdx < n; ++nextIdx) {
      if (permutation[nextIdx] > permutation[currentIdx]) {
        greaterAfter++;
      }
    }

    // Calculate the minimum operations for the current element
    int mirrorOperations = (n - permutation[currentIdx]) - greaterAfter;
    totalOperations += min(greaterAfter, mirrorOperations);
  }

  return totalOperations;
}

int main() {
  // Improve I/O performance
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int testCases;
  cin >> testCases;

  while (testCases--) {
    int n;
    cin >> n;

    vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
      cin >> permutation[i];
    }

    ll result = solveTestCase(n, permutation);
    cout << result << '\n';
  }

  return 0;
}
}