// Problem: CF 2121 G - Gangsta
// https://codeforces.com/contest/2121/problem/G

/*
G. Gangsta
Algorithms/Techniques: Prefix sum, sorting, mathematical computation
Time complexity: O(n log n) per test case due to sorting step
Space complexity: O(n) for the prefix array f

For a binary string s of length n, we need to compute the sum of f(s[l..r]) 
for all substrings s[l..r] where l <= r and 1 <= l, r <= n.
f(p) is defined as the maximum count of any character in string p.
The approach uses prefix sums and sorting to efficiently compute contributions
of subarrays based on their balance (difference between count of '1's and '0's).
*/
#include <algorithm>
#include <iostream>
#include <string>

#define int long long
#define N 200005
using namespace std;
int t, n, ans;
string s;
int f[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> s;
    // Compute prefix sums: f[i] = count of '1's - count of '0's in s[0..i-1]
    for (int i = 1; i <= n; ++i)
      f[i] = f[i - 1] + (s[i - 1] == '1' ? 1 : -1);
    // Sort prefix sums to allow efficient calculation
    sort(f, f + n + 1);
    ans = 0;
    // Compute weighted sum of sorted prefix values
    for (int i = 0; i <= n; ++i)
      ans += f[i] * (2 * i - n);
    // Add final term involving n
    ans += n * (n + 1) * (n + 2) / 6;
    cout << (ans >> 1) << '\n'; // Divide by 2 to get the correct result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/