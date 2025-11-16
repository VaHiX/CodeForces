// Problem: CF 1396 A - Multiples of Length
// https://codeforces.com/contest/1396/problem/A

/*
 * Problem: A. Multiples of Length
 * Purpose: Make all elements of an array equal to zero using exactly three operations.
 * Each operation selects a segment and adds multiples of the segment's length to each element.
 *
 * Algorithm:
 * 1. First operation: Apply a total adjustment to the entire array such that all elements become zero.
 *    This is done by adding -a[i] * n to each element, where n is the length of the array.
 * 2. Second operation: Adjust only the first element to make it zero, by adding a[0] * (n - 1).
 * 3. Third operation: Adjust all elements from index 2 to n, ensuring remaining elements become zero.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  // First operation: Apply adjustment to the entire array
  cout << "1 " << n << '\n';
  for (int i = 0; i < n; i++) {
    cout << -1LL * a[i] * n << " ";  // Add -a[i] * n to each element
  }
  cout << "\n1 1\n"
       << 1LL * a[0] * (n - 1) << "\n"  // Second operation: adjust first element
       << min(2, n) << " " << n << (n == 1 ? "\n0" : "\n");  // Third operation: adjust rest of array
  for (int i = 1; i < n; i++) {
    cout << 1LL * a[i] * (n - 1) << " ";  // Add a[i] * (n - 1) to each element
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/