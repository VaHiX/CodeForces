// Problem: CF 2162 A - Beautiful Average
// https://codeforces.com/contest/2162/problem/A

/*
 * Problem: Beautiful Average
 * 
 * Purpose: Find the maximum possible average value of any subarray in the given array.
 * 
 * Algorithm/Technique:
 * - Since all elements are positive integers and we want to maximize the average,
 *   the maximum average will be achieved by the maximum element in the array.
 *   This is because a single element subarray with the maximum value will have
 *   the highest average among all possible subarrays.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(n) for storing the array elements.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> v(n);
    int max = 0;  // Initialize max to 0 to compare elements
    for (int i = 0; i < n; i++) {
      cin >> v[i];
      if (v[i] > max) {  // Update max if current element is greater
        max = v[i];
      }
    }
    cout << max << '\n';  // Output the maximum element (which is the maximum average)
  }
}


// https://github.com/VaHiX/CodeForces/