// Problem: CF 1479 A - Searching Local Minimum
// https://codeforces.com/contest/1479/problem/A

/*
 * Purpose:
 *   Find any local minimum in a permutation of integers 1 to n using at most 100 queries.
 *   A local minimum at index i satisfies a[i] < min(a[i-1], a[i+1]), with boundaries treated as +∞.
 *
 * Algorithm:
 *   Use binary search on the indices to locate a local minimum.
 *   At each step:
 *     - Query two adjacent elements: a[mid] and a[mid+1]
 *     - If a[mid] < a[mid+1], then the local minimum must be in [l, mid]
 *     - Otherwise, it must be in [mid+1, r]
 *   Continue until l == r, which points to a local minimum.
 *
 * Time Complexity: O(log n) - binary search over n elements with 2 queries per step.
 * Space Complexity: O(1) - only a few variables used, no additional space.
 */

#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  int l = 1, r = n; // Initialize binary search range
  while (l < r) {
    int a, b, mid = (l + r) / 2; // Calculate mid-point
    cout << "? " << mid << endl;
    cin >> a; // Query value at mid
    cout << "? " << mid + 1 << endl;
    cin >> b; // Query value at mid+1
    if (a < b)
      r = mid; // Local min is in left half including mid
    else
      l = mid + 1; // Local min is in right half excluding mid
  }
  cout << "! " << l << "\n"; // Output the found local minimum index
  return 0;
}


// https://github.com/VaHiX/CodeForces/