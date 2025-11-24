// Problem: CF 1903 D1 - Maximum And Queries (easy version)
// https://codeforces.com/contest/1903/problem/D1

/*
Algorithm/Techniques: Bit Manipulation, Greedy
Time Complexity: O(n * log(max_value) + q * log(max_value)) where max_value <= 1e6 and log(max_value) is at most 62
Space Complexity: O(n) for storing arrays a, a2, b, c
*/

#include <iostream>

#define int long long
#define endl '\n'
using namespace std;
const int N = 2e5;
int n, q, k, a[N + 10], b[N + 10], c[N + 10], a2[N + 10];
int turnon(int x, int y) { return (x | ((int)1 << y)); }
int getbit(int x, int y) { return ((x >> y) & 1); }
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a2[i] = a[i]; // Store original array for reuse in queries
  }
  while (q--) {
    cin >> k;
    // Restore original array for each query
    for (int i = 1; i <= n; i++)
      a[i] = a2[i];
    // Reset bit tracking array
    for (int i = 1; i <= n; i++)
      b[i] = 0;
    // Special case: if only one element, just add all k to it
    if (n == 1) {
      cout << (a[1] + k) << endl;
      continue;
    }
    int res = 0; // Resulting maximum AND value
    // Iterate from most significant bit (61) down to 0
    for (int i = 61; i >= 0; i--) {
      int tmp = 0; // Number of operations needed to set bit i
      // Copy current state of array a to c
      for (int i = 1; i <= n; i++)
        c[i] = a[i];
      // Try to set bit i in each element by adding necessary increments
      for (int j = 1; j <= n; j++) {
        if (getbit(a[j], i)) // Skip if bit i is already set
          continue;
        // Calculate new value after trying to set bit i
        int x = turnon(a[j], i) & turnon(b[j], i);
        c[j] = x;
        tmp += x - a[j]; // Count operations needed
        if (tmp > k) // Early termination if we go over k operations
          break;
      }
      // If we can afford the operations to set bit i
      if (k - tmp >= 0) {
        // Update the array with new values
        for (int i = 1; i <= n; i++)
          a[i] = c[i];
        // Set bit i in result
        res += ((int)1 << i);
        k -= tmp; // Reduce remaining operations
      }
      // Update bit tracking array to remember which bits have been set so far
      for (int j = 1; j <= n; j++) {
        if (getbit(a[j], i))
          b[j] = turnon(b[j], i);
      }
    }
    cout << res << endl;
  }
}


// https://github.com/VaHiX/CodeForces/