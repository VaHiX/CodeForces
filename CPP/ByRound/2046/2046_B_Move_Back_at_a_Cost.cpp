// Problem: CF 2046 B - Move Back at a Cost
// https://codeforces.com/contest/2046/problem/B

/*
B. Move Back at a Cost
Algorithms/Techniques: Greedy, Simulation, Sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for the array and auxiliary arrays

The problem asks to find the lexicographically smallest array by performing operations where we can increase an element and move it to the back.
This greedy approach processes from right to left, increasing elements when necessary to ensure non-decreasing order,
then adjusts remaining elements to minimize the final result.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int t, n, a[100005], mn, mnn, f[100005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    mn = mnn = 2e9; // Initialize min values to large number
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      f[i] = 0; // Mark array to track processed elements
    }
    for (int i = n - 1; i >= 0; i--) {
      if (mn > a[i])
        mn = a[i]; // Track minimum from right
      if (a[i] > mn) { // If current element is greater than min seen so far
        a[i]++;       // Increment it
        f[i] = 1;     // Mark that this element was incremented
        mnn = min(mnn, a[i]); // Update global minimum after increment
      }
    }
    for (int i = n - 1; i >= 0; i--)
      if (f[i] == 0 && a[i] > mnn) // For unmarked elements that are still greater than min
        a[i]++; // Increment them to reduce lexicographic value
    sort(a, a + n); // Sort result for final output
    for (int i = 0; i < n; i++)
      cout << a[i] << " ";
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/