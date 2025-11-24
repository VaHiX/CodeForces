// Problem: CF 2121 F - Yamakasi
// https://codeforces.com/contest/2121/problem/F

/*
F. Yamakasi

Algorithm: Two-pointer technique with prefix sums and map for counting valid subarrays.
Time Complexity: O(n) amortized per test case, where n is the size of the array.
Space Complexity: O(n) for storing prefix sums and map usage.

Problem:
Count the number of subsegments whose sum equals s and maximum value equals x.

Approach:
- Use two pointers (l and r) to maintain a sliding window.
- For each right pointer r, check if current element exceeds x; if so, reset the window.
- If a[r] == x, we start counting valid left endpoints from l to r.
- Maintain prefix sums and use a map to store how many times each sum has occurred.
- When processing a[r], we look for how many previous prefix sums equal (sum[r] - s).
  This gives us valid segments ending at r with sum s.
*/

#include <iostream>
#include <map>

using namespace std;
const int N = 2e5 + 10;
int a[N];
long long sum[N];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, x;
    long long s;
    cin >> n >> s >> x;
    for (int i = 1; i <= n; i++)
      cin >> a[i], sum[i] = sum[i - 1] + a[i];
    long long ans = 0;
    map<long long, int> cnt;
    int l = 1;
    for (int r = 1; r <= n; r++) {
      // If element is greater than x, reset the window
      if (a[r] > x)
        cnt.clear(), l = r + 1;
      // If element equals x, update map with new prefix sums from left to r
      else if (a[r] == x) {
        for (; l <= r; l++)
          cnt[sum[l - 1]]++;
      }
      // Count how many subarrays ending at r have sum s
      ans += cnt[sum[r] - s];
    }
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/