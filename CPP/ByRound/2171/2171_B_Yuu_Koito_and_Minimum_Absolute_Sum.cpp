// Problem: CF 2171 B - Yuu Koito and Minimum Absolute Sum
// https://codeforces.com/contest/2171/problem/B

/*
 * Problem: Yuu Koito and Minimum Absolute Sum
 * 
 * Purpose:
 *   Given an array with some elements as -1 (blanks), fill those blanks with non-negative integers
 *   such that the absolute value of the sum of differences in the difference array is minimized.
 *   Output the lexicographically smallest such array.
 * 
 * Approach:
 *   - For each segment of consecutive -1s, we set them to 0 to minimize impact on difference sum.
 *   - If the first or last element is -1, we can set it to match the other end to minimize difference.
 *     This ensures the total sum of differences is minimized.
 *   - The difference array b[i] = a[i+1] - a[i], so total sum = a[n] - a[1].
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array
 * 
 * Algorithms/Techniques:
 *   Greedy approach to minimize sum of differences
 *   Handling boundary cases for first and last elements when they are -1
 */

#include <bits/std_abs.h>
#include <iostream>

using namespace std;
typedef long long ll;
ll a[200010], n, tt, ans;
int main() {
  cin >> tt;
  while (tt--) {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
      cin >> a[i];
      // If current element is -1 and not first or last, set to 0
      if (i > 1 && i < n && a[i] == -1)
        a[i] = 0;
    }
    // Handle cases where first or last element is -1
    if (a[1] == -1 && a[n] == -1)
      a[1] = 0, a[n] = 0, ans = 0;
    else if (a[1] == -1)
      a[1] = a[n], ans = 0;
    else if (a[n] == -1)
      a[n] = a[1], ans = 0;
    else
      ans = abs(a[n] - a[1]);
    cout << ans << endl;
    for (ll i = 1; i <= n; i++)
      cout << a[i] << " ";
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/