// Problem: CF 1748 C - Zero-Sum Prefixes
// https://codeforces.com/contest/1748/problem/C

/* 
 * Problem: Zero-Sum Prefixes
 * 
 * Algorithm/Technique:
 * - Use prefix sums to identify zero-sum prefixes.
 * - Traverse the array from right to left to determine how many zero-sum prefixes can be formed.
 * - When encountering a zero, we can change it to any value to maximize zero-sum prefixes.
 * - A map is used to count occurrences of prefix sums to determine maximum score.
 * 
 * Time Complexity: O(n log n) per test case due to map operations.
 * Space Complexity: O(n) for storing prefix sums and map.
 */

#include <algorithm>
#include <iostream>
#include <map>

using namespace std;
#define int long long
const int N = 200010;
int t, n, a[N], sum[N];
signed main() {
  cin >> t;
  while (t--) {
    cin >> n;
    sum[0] = 0;
    for (int i = 1; i <= n; i++)
      cin >> a[i], sum[i] = sum[i - 1] + a[i]; // Compute prefix sums
    
    int cnt = 0, ans = 0;
    map<int, int> mp;
    for (int i = n; i > 0; i--) {
      mp[sum[i]]++; // Count occurrence of current prefix sum
      ans = max(ans, mp[sum[i]]); // Track maximum count of any prefix sum
      if (!a[i]) { // If current element is zero, reset map and add max count to result
        mp.clear();
        cnt += ans;
        ans = 0;
      }
    }
    cnt += mp[0]; // Add any remaining zero-sum prefixes
    cout << cnt << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/