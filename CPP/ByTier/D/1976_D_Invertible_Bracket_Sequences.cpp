// Problem: CF 1976 D - Invertible Bracket Sequences
// https://codeforces.com/contest/1976/problem/D

/*
Algorithm: 
This solution uses a prefix sum technique combined with a map to efficiently count valid subranges.
The key insight is to track the balance of brackets (where '(' contributes +1 and ')' contributes -1).
For a substring to be invertible while preserving a valid bracket sequence, the changes must maintain 
the validity of the entire sequence. The strategy is to:
1. Compute prefix balances.
2. For each position, see how many previous prefix balances can form valid pairs with the current one,
   such that when the substring between them is inverted, the overall result remains valid.
3. Maintain a map of seen balances to quickly compute valid pairs.

Time Complexity: O(N * log N) per test case due to map operations.
Space Complexity: O(N) for storing the balance array and map.

*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define FOR(i, a, b) for (int i = (signed)(a); i <= (signed)(b); i++)
#define F0R(i, a) for (int i = (signed)(0); i < (signed)(a); i++)
const int MXN = 2e5 + 10;
ll bal[MXN] = {0};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  while (T--) {
    string str;
    cin >> str;
    int N;
    N = str.length();
    F0R(i, N) bal[i] = 0;
    F0R(i, N) {
      if (i != 0)
        bal[i] = bal[i - 1];
      if (str[i] == '(')
        bal[i]++;
      else
        bal[i]--;
    }
    map<int, ll> mp;
    ll ans = 0;
    vector<int> v;
    F0R(i, N) {
      ans += mp[bal[i]]; // Count valid pairs based on current balance
      mp[bal[i]]++;      // Add current balance to map
      v.clear();
      // Iterate through map to find and remove outdated entries
      for (auto j : mp) {
        if ((j.first < (bal[i] - j.first))) {
          v.pb(j.first);
        }
        break;
      }
      for (int i : v)
        mp.erase(i); // Remove items that are no longer needed for future comparisons
    }
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/