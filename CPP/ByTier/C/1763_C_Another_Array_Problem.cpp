// Problem: CF 1763 C - Another Array Problem
// https://codeforces.com/contest/1763/problem/C

/*
Purpose: This code solves the problem of finding the maximum possible sum of an array after performing a series of operations. 
Each operation allows replacing a subarray with the absolute difference of its first and last elements. 
The key insight is to determine the optimal way to apply such operations to maximize the sum.

Approaches:
- For n = 2: Only one operation is possible (replace both elements with |a[0] - a[1]|), but we can also keep original values.
- For n = 3: Check all possible results of applying one operation, as there are limited options.
- For n > 3: The maximum sum is achieved by replacing all elements with the maximum element in the array, leading to a sum of max_element * n.

Time Complexity: O(n) per test case, since reading n elements and finding max takes linear time.
Space Complexity: O(1), only using a constant amount of extra space.
*/

#include <bits/std_abs.h>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  long long t, n, x, y, z, maxx;
  cin >> t;
  while (t--) {
    cin >> n;
    maxx = 0;
    if (n == 2) {
      // For n = 2, we can either:
      // 1. Keep original values: a[0] + a[1]
      // 2. Apply operation: 2 * |a[0] - a[1]|
      cin >> x >> y;
      cout << max(abs(x - y) * 2, x + y) << endl;
    } else if (n == 3) {
      // For n = 3, check all possible operations:
      // 1. Replace [1,2] -> |a[0]-a[1]|, then [2,3] -> |a[1]-a[2]|, etc.
      // 2. Keep values: a[0] + a[1] + a[2]
      // 3. Replace all with a[0]: 3*a[0]
      // 4. Replace all with a[2]: 3*a[2]
      cin >> x >> y >> z;
      cout << max({abs(x - y) * 3, abs(y - z) * 3, x * 3, z * 3, x + y + z}) << endl;
    } else {
      // For n > 3, applying operations will only reduce values.
      // Optimal strategy is to replace all with maximum element to maximize sum.
      for (int i = 1; i <= n; ++i)
        cin >> x, maxx = max(maxx, x);
      cout << maxx * n << endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/