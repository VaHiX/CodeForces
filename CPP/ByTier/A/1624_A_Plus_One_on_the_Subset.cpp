// Problem: CF 1624 A - Plus One on the Subset
// https://codeforces.com/contest/1624/problem/A

/*
 * Problem: A. Plus One on the Subset
 * Purpose: Find the minimum number of operations to make all elements in the array equal,
 *          where each operation increases selected elements by 1.
 *
 * Algorithms/Techniques:
 *   - Sorting and difference calculation
 *   - Greedy approach (minimum operations = max value - min value)
 *
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for storing the array elements.
 */

#import <bits/stdc++.h>
using namespace std;
int n, a[9999];
int main() {
  // Loop through each test case
  for (cin >> n; cin >> n;) {
    // Read the array elements
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    
    // Sort the array to easily find min and max values
    sort(a + 1, a + n + 1);
    
    // The minimum operations needed is the difference between max and min elements
    cout << a[n] - a[1] << '\n';
  }
}


// https://github.com/VaHiX/codeForces/