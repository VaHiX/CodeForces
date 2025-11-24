// Problem: CF 2145 C - Monocarp's String
// https://codeforces.com/contest/2145/problem/C

/*
Algorithm: 
  - Use prefix sums to track the difference between count of 'a' and 'b' up to each position.
  - The idea is to find the shortest substring (consecutive characters) that can be removed 
    so that the remaining string has equal counts of 'a' and 'b'.
  - This is transformed into finding two positions where the prefix difference values are equal,
    with the difference being offset by the total imbalance (needed).
  - We track the last occurrence of each prefix difference value (adjusted by n to avoid negative indices).
  - For each position, we look for a previous occurrence where the difference is (current_diff - needed),
    which implies the subarray between them has a balance that can compensate the total imbalance.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for prefix array and last array.

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define int long long
void solve() {
  int n;
  string s;
  cin >> n >> s;
  s = ' ' + s; // prepend a space to make indexing easier (1-based)
  vector<int> pref(n + 1); // prefix sum array to track difference (a count - b count)
  vector<int> last(2 * n + 1, -1); // tracks last index for each prefix sum value (adjusted by n)
  
  // compute prefix sums
  for (int i = 1; i <= n; ++i) {
    pref[i] = pref[i - 1] + (s[i] == 'a' ? 1 : -1); // 1 for 'a', -1 for 'b'
  }
  
  int needed = pref[n]; // total imbalance: if > 0, we need to remove 'b's; if < 0, we need to remove 'a's

  // if the imbalance is zero, then already balanced
  if (needed == 0) {
    cout << 0 << '\n';
    return;
  }

  // initialize last with prefix value at index 0
  last[pref[0] + n] = 0;
  
  int res = 1e9; // minimum length of substring to remove
  
  // iterate through prefix sums to find valid ranges
  for (int i = 1; i <= n; ++i) {
    // calculate the difference needed to reach balance
    int cur = pref[i] - needed + n;
    
    // skip if cur is negative (invalid index)
    if (cur < 0)
      continue;
    
    // if we have seen this required difference before
    if (last[cur] != -1) {
      res = min(res, i - last[cur]); // update minimum length
    }
    
    // record the current prefix difference
    last[pref[i] + n] = i;
  }
  
  // print result: if res is still large, it's impossible to balance (return -1)
  cout << (res == n ? -1 : res) << '\n';
}
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/