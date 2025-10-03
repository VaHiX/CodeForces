// Problem: CF 2131 G - Wafu!
// https://codeforces.com/contest/2131/problem/G

/*
G. Wafu!
Algorithms/Techniques: Dynamic programming, bit manipulation, simulation with greedy approach.

Time Complexity: O(30 * log(k) + n * log(n)) per test case
Space Complexity: O(30 + n)

The problem simulates a process where elements are removed from a set and new elements are added based on the removed value.
We precompute factorials up to 30 for efficiency.
*/

#include <algorithm>
#include <iostream>

#define M 200000
#define ll long long
#define MAXX 200500
#define mod 1000000007
using namespace std;

ll dp[31]; // Precomputed factorials: dp[i] = i!
int a[MAXX];

int main() {
  ios::sync_with_stdio(false);
  
  // Precompute factorials from 1 to 30
  for (int i = 1; i <= 30; i++) {
    dp[i] = i;
    for (int j = 1; j < i; j++)
      dp[i] = dp[i] * dp[j] % mod;
  }

  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    
    sort(a + 1, a + n + 1); // Sort the initial set
    
    ll ans = 1; // Start with score of 1
    
    for (int i = 1; i <= n; i++) {
      // If current element is greater than 30 or can't fit into k operations
      if (a[i] > 30 || (1 << (a[i] - 1)) > k) {
        if (k) {
          ans = ans * a[i] % mod; // Multiply score by this element
          k--; // Decrement remaining operations

          // For each bit position in k, check if it's set and multiply by corresponding dp value
          for (int j = 1; j <= 30; j++) {
            if (k & (1 << (j - 1))) {
              ans = ans * dp[j] % mod;
            }
          }
        }
        break; // Exit loop because remaining operations aren't enough to proceed
      } else {
        k -= (1 << (a[i] - 1)); // Reduce k by the number of operations corresponding to this element
        ans = ans * dp[a[i]] % mod; // Multiply score by factorial of current element
      }
    }
    
    cout << ans << endl;
  }
  
  return 0;
}


// https://github.com/VaHiX/codeForces/