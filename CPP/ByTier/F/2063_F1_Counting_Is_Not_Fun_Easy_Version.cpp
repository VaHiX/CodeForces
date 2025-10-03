// Problem: CF 2063 F1 - Counting Is Not Fun (Easy Version)
// https://codeforces.com/contest/2063/problem/F1

/*
Code Purpose:
This code solves a problem involving counting the number of valid balanced bracket sequences given a set of constraints. 
Each constraint specifies a "good pair" (l, r), meaning that at some point in constructing the bracket sequence, 
the opening bracket at l is matched with a closing bracket at r.

Algorithm:
- Precompute factorials and inverse factorials for combinatorial calculations.
- Use Catalan numbers to determine how many balanced bracket sequences exist for a given number of pairs.
- For each clue (l, r):
  - Process overlapping intervals by assigning IDs to segments.
  - Count the number of valid combinations using precomputed Catalan numbers per group.

Time Complexity: O(N^2) where N is the maximum number of brackets (2n), due to segment processing and interval handling.
Space Complexity: O(N) for storing factorial, inverse factorial, Catalan, ID, size, and sum arrays.

Techniques:
- Modular exponentiation for fast modular inverse
- Precomputation of factorials and Catalan numbers
- Interval merging and grouping using segment IDs
*/

#include <iostream>
#define int long long
using namespace std;
const int N = 1e6 + 5;
const int mod = 998244353;
int T, n, l, r, tot, ans;
int fac[N], inv[N], id[N], sz[N], s[N], C[N];

// Fast modular exponentiation
inline int mi(int a, int b = mod - 2) {
  int ans = 1;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

// Compute the nth Catalan number using precomputed factorials
inline int cat(int n) {
  return fac[n + n] * inv[n] % mod * inv[n] % mod * mi(n + 1) % mod;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  fac[0] = inv[0] = 1;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n * 2; ++i) {
      fac[i] = fac[i - 1] * i % mod;
      inv[i] = inv[i - 1] * mi(i) % mod;
    }
    for (int i = 0; i <= n; ++i)
      C[i] = cat(i); // Precompute Catalan numbers up to n
    tot = 1;
    cout << C[n] << " "; // Output total number of sequences before any clues
    for (int i = 1; i <= n * 2; ++i)
      id[i] = 1; // Initialize all segments to group 1
    for (int i = 1; i <= n; ++i) {
      cin >> l >> r;
      tot++; // Increment group count
      for (int j = l + 1; j < r; ++j) {
        if (id[j] == id[l])
          id[j] = tot; // Merge intervals by assigning new ID
      }
      id[l] = id[r] = 0; // Mark start and end points as merged
      for (int j = 1; j <= tot; ++j)
        s[j] = 0; // Reset counts for group sizes
      for (int j = 1; j <= n * 2; ++j)
        s[id[j]]++; // Compute size of each group
      ans = 1;
      for (int j = 1; j <= tot; ++j)
        ans = ans * C[s[j] / 2] % mod; // Multiply Catalan numbers of groups
      cout << ans << " ";
    }
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/