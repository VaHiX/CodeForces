// Problem: CF 1811 E - Living Sequence
// https://codeforces.com/contest/1811/problem/E

/*
 * Problem: E. Living Sequence
 * 
 * Description:
 * A living sequence contains all natural numbers that do not contain the digit 4.
 * Given a position k, find the k-th number in this sequence.
 * 
 * Approach:
 * This problem is solved using a digit dynamic programming (digit DP) technique
 * combined with base-9 conversion. Since we exclude the digit 4, we can map the
 * problem to base-9 numbers where 0-3 map to 0-3 and 5-9 map to 1-5 (shifted by 1
 * to account for the missing 4).
 * 
 * The idea:
 * - Convert `k` to base-9 representation.
 * - Adjust for the missing digit 4: if digit in base-9 is >= 4, we increment it
 *   by 1 (since we're shifting 5->5, 6->6, ..., 9->9 and 4->5, but 4 is excluded).
 * - Reverse the result to get the correct order.
 * 
 * Time Complexity: O(log k) per query, where k can be up to 10^12
 * Space Complexity: O(log k) for storing the string representation of result
 * 
 * Techniques:
 * - Base conversion from 10 to 9
 * - Mapping digits appropriately to avoid 4
 * - String reversal for final output
 */

#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef long long int li;
typedef pair<li, li> pi;
typedef vector<long long> vll;
typedef vector<long long int> vli;
#define pb push_back
#define fr(i, a, b) for (int i = a; i < b; i++)
#define sort(v) sort(v.begin(), v.end())
#define sortd(v) sort(v.begin(), v.end(), greater<int>())
li mod = 1e9 + 7;
li maxn = 3e5 + 7;

// Function to compute the k-th living number
string calc(li n) {
  string ans = "";
  li temp = n;
  while (temp > 0) {
    li x = temp % 9;        // Get the remainder when dividing by 9
    if (x >= 4) {           // If it's >= 4, adjust to skip 4
      x++;                  // Shift digit to account for missing 4
    }
    char s = x + '0';       // Convert to character
    ans += s;               // Append to answer
    temp /= 9;              // Move to next digit in base-9
  }
  return ans;
}

void solve() {
  li n;
  cin >> n;
  string ans = calc(n);
  reverse(ans.begin(), ans.end());  // Reverse to get the correct order
  cout << ans << "\n";
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/