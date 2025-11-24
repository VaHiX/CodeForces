// Problem: CF 1783 A - Make it Beautiful
// https://codeforces.com/contest/1783/problem/A

/*
 * Purpose: To reorder an array such that it becomes "beautiful".
 *          An array is beautiful if no element equals the sum of all elements before it.
 *          The array is given in non-decreasing order, and we can only reorder elements.
 *
 * Algorithm:
 *   - Sort the array first (already sorted in input, but we do it explicitly).
 *   - If all elements are the same, it's impossible to make it beautiful (because the first element
 *     cannot be sum of previous elements, but the second one will be equal to the first if all same).
 *   - Otherwise, place the largest element first, followed by the rest in original order.
 *     This strategy avoids creating a prefix sum equal to a subsequent element.
 *
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the array
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    vector<int> v;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      v.push_back(x);
    }
    sort(v.begin(), v.end());
    // If all elements are the same, there's no way to make it beautiful
    if (v[0] == v[n - 1])
      cout << "NO" << endl;
    else {
      // Place the largest element at the front to prevent sum equality
      cout << "YES" << endl;
      cout << v[n - 1] << " "; // Print the largest element first
      for (int i = 0; i < n - 1; i++)
        cout << v[i] << " "; // Print the rest in order
      cout << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/