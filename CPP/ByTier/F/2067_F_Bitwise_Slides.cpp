// Problem: CF 2067 F - Bitwise Slides
// https://codeforces.com/contest/2067/problem/F

/*
F. Bitwise Slides
Algorithms/Techniques: Dynamic Programming with XOR properties, bitmasking

Time Complexity: O(n * log(max(a_i))) where n is the length of array a and log(max(a_i)) accounts for XOR operations.
Space Complexity: O(n) for storing prefix XORs and DP states.

Problem Description:
Given an array, we need to assign one of three operations (P, Q, R) to each element such that
after each operation, P, Q, R remain non-pairwise distinct. 
We count how many valid assignment sequences there are modulo 1e9+7.
*/

#include <iostream>
#include <unordered_map>
#include <utility>

#define int long long
using namespace std;
const int N = 1e6 + 10, mod = 1e9 + 7;
int arr[N], n, t;
unordered_map<int, int> dp;

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  
  cin >> t;
  while (t--) {
    cin >> n;
    dp.clear(); // Clear DP map for new test case
    dp[0] = 1;  // Base case: prefix XOR of 0 has one way to achieve it
    
    for (int i = 1; i <= n; ++i) {
      cin >> arr[i];
      arr[i] ^= arr[i - 1]; // Compute prefix XOR
      
      // Key formula: update DP transitions based on current prefix XOR
      dp[arr[i - 1]] = 3 * dp[arr[i - 1]] + 2 * dp[arr[i]];
      dp[arr[i - 1]] %= mod;
    }
    
    int ans = 0; // Sum up all valid ways
    for (auto e : dp) {
      ans += e.second;
      ans %= mod;
    }
    
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/