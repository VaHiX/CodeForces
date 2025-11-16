// Problem: CF 1788 D - Moving Dots
// https://codeforces.com/contest/1788/problem/D

/*
 * Problem: Moving Dots
 * Algorithm: Dynamic Programming with Two Pointers
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 *
 * The solution calculates the sum of distinct stopping coordinates
 * over all subsets of at least two dots. For each dot, we determine
 * how many subsets it belongs to in the final configuration using
 * two-pointer technique and precomputed powers of 2.
 */

#include <iostream>

#define ll long long
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 3e3 + 5;
int n, ans, a[maxn], pw[maxn];

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  
  // For each dot i, calculate the contribution to the answer
  for (int i = 1; i <= n; ++i) {
    int l = i - 1, r = i, len;
    
    // Process all previous dots to find valid subsets
    for (int j = i - 1; j >= 1; --j) {
      // Adjust left pointer to maintain condition: distance from j to l <= distance from j to i
      while (a[j] - a[l] <= a[i] - a[j] && l >= 1)
        l--;
      
      // Adjust right pointer to maintain condition: distance from r to i < distance from j to i  
      while (a[r] - a[i] < a[i] - a[j] && r <= n)
        r++;
      
      // Calculate number of valid subsets that include dot j
      len = l + n - r + 1;
      ans = (ans + pw[len]) % mod;
    }
  }
  cout << ans;
}

signed main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  // Precompute powers of 2 modulo 10^9 + 7
  pw[0] = 1;
  for (int i = 1; i <= maxn - 5; ++i)
    pw[i] = (pw[i - 1] << 1) % mod;
  
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/