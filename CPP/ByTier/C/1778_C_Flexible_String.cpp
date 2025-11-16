// Problem: CF 1778 C - Flexible String
// https://codeforces.com/contest/1778/problem/C

/*
Algorithm: Bitmask Dynamic Programming
This problem uses bitmasking to try all possible combinations of at most k characters from the unique characters in string `a` that can be added to set Q. For each valid combination, it calculates how many substrings match between `a` and `b`.

The main idea is:
1. Map each character in `a` to a unique index (0 to p-1) where p is number of unique characters in `a`.
2. For every subset of these indices (represented by a bitmask) with size at most k:
   - Try to make `a` match `b` by using the characters in the subset for replacement.
   - Count how many matching substrings are possible.
3. Return the maximum such count.

Time Complexity: O(2^p * n)
Space Complexity: O(1) excluding input storage

where p is the number of unique characters in `a` (at most 10), and n is the length of the strings.

*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int tk;
  cin >> tk;
  while (tk--) {
    int a, k;
    string s, sa;
    cin >> a >> k >> s >> sa;
    int ka[26], p = 0;
    memset(ka, -1, sizeof(ka));
    for (int i = 0; i < a; i++) {
      if (ka[s[i] - 'a'] == -1)
        ka[s[i] - 'a'] = p++;  // Assign a unique index to each character in `a`
    }
    ll ans = 0;
    for (int i = 0; i < (1 << p); i++) {  // Iterate through all subsets of unique characters
      int r = 0;
      for (int j = 0; j < p; j++) {
        if (i & (1 << j))
          r++;  // Count number of characters selected in the subset
      }
      if (r > k || r < min(p, k))  // Skip invalid subsets
        continue;
      int t = 0;
      ll tmp = 0;
      for (int j = 0; j < a; j++) {
        if (s[j] == sa[j] ||
            (ka[s[j] - 'a'] != -1 && (i & (1 << ka[s[j] - 'a'])))) {
          tmp += ++t;  // Extend current matching substring count
        } else
          t = 0;  // Reset current matching substring count
      }
      ans = max(tmp, ans);
    }
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/