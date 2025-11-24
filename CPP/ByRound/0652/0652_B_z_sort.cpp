// Problem: CF 652 B - z-sort
// https://codeforces.com/contest/652/problem/B

/*
 * Z-Sort Problem Solution
 *
 * Algorithm/Technique:
 * - Sort the array first.
 * - Then, rearrange elements in a specific pattern:
 *   - For even indices (0, 2, 4, ...), place elements from the beginning of the sorted array.
 *   - For odd indices (1, 3, 5, ...), place elements from the end of the sorted array.
 * - This ensures that the conditions for z-sort are satisfied:
 *   - Even indices: a[i] >= a[i-1] (non-decreasing)
 *   - Odd indices: a[i] <= a[i-1] (non-increasing)
 *
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(1) if we don't count input/output, otherwise O(n) for the array
 */

#include <algorithm>
#include <iostream>

using namespace std;

int n, a[1111]; // Array to store input elements, size 1111 is sufficient for n <= 1000

int main() {
  cin >> n; // Read number of elements
  for (int i = 0; i < n; i++) {
    cin >> a[i]; // Read each element
  }
  sort(a, a + n); // Sort the array in ascending order
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0)
      // For even indices, take elements from the start of the sorted array (i/2)
      cout << a[i / 2] << ' ';
    else
      // For odd indices, take elements from the end of the sorted array (n - i/2 - 1)
      cout << a[n - i / 2 - 1] << ' ';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/