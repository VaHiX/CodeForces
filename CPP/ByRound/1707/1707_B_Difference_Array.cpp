// Problem: CF 1707 B - Difference Array
// https://codeforces.com/contest/1707/problem/B

/*
Algorithm: Difference Array Simulation
This problem simulates a process where we repeatedly compute the differences between adjacent elements,
sort the differences, and replace the array with the sorted differences until only one element remains.

Approach:
1. For each test case, we start with an array 'a' of size n.
2. We perform n-1 operations:
   - Compute differences between adjacent elements.
   - Sort the differences.
   - Replace the array with the sorted differences.
3. Finally, output the last remaining element.

Time Complexity: O(n^2 * log n) in the worst case due to repeated sorting and difference updates.
Space Complexity: O(n) for storing the array.

*/
#include <algorithm>
#include <iostream>

using namespace std;
int a[100001];
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    int l = 1;  // left pointer to track non-zero elements
    for (int i = 1; i < n; i++) {
      // Update all elements with difference from previous element
      for (int j = n; j >= l; j--)
        a[j] -= a[j - 1];
      a[i] = 0;  // Set the i-th element to 0 after difference calculation
      sort(a + l, a + n + 1);  // Sort the valid portion of array
      while (a[l] == 0 && l <= n)
        l++;  // Move the left pointer to skip zeros
    }
    cout << a[n] << endl;  // Output the final remaining element
  }
}


// https://github.com/VaHiX/CodeForces/