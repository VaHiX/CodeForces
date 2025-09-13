/**
 * Problem: CF2131E - Adjacent XOR
 *
 * This program determines if array A can be transformed into array B using
 * adjacent XOR operations. In one operation, you can choose an index i (1 ≤ i <
 * n) and set A[i] = A[i] XOR A[i+1]. The operation can be performed any number
 * of times (including zero).
 *
 * Approach:
 * 1. The last element of A must match the last element of B since it can't be
 * modified.
 * 2. For each element from second last to first, check if it can be transformed
 * into the target value using the XOR operation with either the original or
 * modified next element.
 * 3. The transformation is possible if all elements can be matched through this
 * process.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the arrays
 */

#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 200001;

/**
 * Determines if array A can be transformed into array B using adjacent XOR
 * operations
 * @param n: Number of elements in the arrays
 * @param a: The original array A
 * @param b: The target array B
 * @return: true if transformation is possible, false otherwise
 */
bool can_transform(int n, const vector<int> &a, const vector<int> &b) {
  // The last element must match exactly as it can't be modified
  if (a[n - 1] != b[n - 1]) {
    return false;
  }

  // Check each element from second last to first
  for (int i = n - 2; i >= 0; i--) {
    // Check if the current element can be transformed into b[i] by:
    // 1. Already matching
    // 2. XOR with next element in A
    // 3. XOR with next element in B (if it was modified)
    if (a[i] != b[i] && (a[i] ^ a[i + 1]) != b[i] &&
        (a[i] ^ b[i + 1]) != b[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  // Optimize I/O operations
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int test_cases;
  cin >> test_cases;

  while (test_cases--) {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
      cin >> b[i];
    }

    if (can_transform(n, a, b)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

  return 0;
}