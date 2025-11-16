// Problem: CF 2137 E - Mexification
// https://codeforces.com/contest/2137/problem/E

/*
E. Mexification

Algorithms/Techniques: 
- MEX (Minimum Excluded) computation using frequency counting
- Optimization using cycle detection for large k values
- Efficient array manipulation and iteration

Time Complexity:
- O(n) per test case, where n is the size of the array.
  The solve function runs in O(n), and since k can be up to 10^9,
  we reduce k to at most 4 using cyclicity.

Space Complexity:
- O(n) for auxiliary arrays c and a

The problem involves applying a transformation k times on an array where each element
is replaced by the MEX of all other elements. Due to the nature of MEX operations, 
the sequence of transformations becomes periodic after at most 2 steps, so we optimize
by reducing k modulo 2 + 2 = 4.
*/

#include <algorithm>
#include <iostream>

using namespace std;
long long a[200000], c[200001];

void solve(long long n) {
  long long i, cmex;
  for (i = 0; i <= n; i++)
    c[i] = 0; // Reset frequency array
  for (i = 0; i < n; i++)
    c[a[i]]++; // Count occurrences of each element
  cmex = -1;
  for (i = 0; i <= n; i++) {
    if (!c[i]) { // Find the smallest non-negative integer not present
      cmex = i;
      break;
    }
  }
  for (i = 0; i < n; i++) {
    if (c[a[i]] == 1) // If current element appears only once
      a[i] = min(a[i], cmex); // Replace with min of itself and cmex
    else
      a[i] = cmex; // Otherwise replace with cmex directly
  }
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T;
  long long n, k, i, ans;
  for (cin >> T; T > 0; T--) {
    cin >> n >> k;
    for (i = 0; i < n; i++)
      cin >> a[i]; // Read array elements
    if (k > 1)
      k = k % 2 + 2; // Reduce k to small value due to cycle property
    for (i = 0; i < k; i++)
      solve(n); // Apply transformation k times
    ans = 0;
    for (i = 0; i < n; i++)
      ans += a[i]; // Compute final sum
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/