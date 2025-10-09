// Problem: CF 2008 E - Alternating String
// https://codeforces.com/contest/2008/problem/E

/*
E. Alternating String

Purpose:
This code solves the problem of transforming a given string into an "alternating string", where all even-positioned characters are the same and all odd-positioned characters are the same, and the total length is even. The solution uses two types of operations: deleting one character or changing one character. It computes the minimum number of operations needed for each test case.

Algorithms/Techniques:
- Preprocessing to count frequency of characters at even and odd positions.
- For even-length strings: directly compute minimal changes needed.
- For odd-length strings: iterate backwards to simulate removing each character, then recompute cost.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1) since we use fixed-size arrays (26 elements max).
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
#define ll long long
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = n;
    int cnt[2][26]{}; // cnt[0] counts chars at even indices, cnt[1] at odd
    for (int i = 0; i < n; i++) {
      cnt[i % 2][s[i] - 'a']++; // Count frequency of each letter at even/odd positions
    }
    if (n % 2 == 0) {
      // For even-length string: no deletion possible, just compute minimal changes
      ans = n - *max_element(cnt[0], cnt[0] + 26) -
            *max_element(cnt[1], cnt[1] + 26);
    } else {
      // For odd-length string: try deleting each character one by one and compute optimal result
      for (int i = n - 1; i >= 0; i--) {
        cnt[i % 2][s[i] - 'a']--; // Remove current character from count
        ans = min(ans, n - *max_element(cnt[0], cnt[0] + 26) -
                           *max_element(cnt[1], cnt[1] + 26));
        cnt[(i + 1) % 2][s[i] - 'a']++; // Restore it back for next iteration
      }
    }
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/codeForces/