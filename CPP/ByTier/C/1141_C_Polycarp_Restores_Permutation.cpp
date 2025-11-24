// Problem: CF 1141 C - Polycarp Restores Permutation
// https://codeforces.com/contest/1141/problem/C

/*
C. Polycarp Restores Permutation
Problem: Restore a permutation of size n given the differences between consecutive elements.

Algorithm:
- Compute prefix sums of the difference array to reconstruct the original sequence (with an unknown offset).
- Find the minimum value in the prefix sum array and adjust all values to ensure they are in range [1, n].
- Check if the adjusted values form a valid permutation (all unique, in range [1, n]).

Time Complexity: O(n)
Space Complexity: O(n)

Input:
- n: size of permutation
- q array of differences of length n-1

Output:
- A valid permutation or -1 if impossible.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n, 0);  // Prefix sum array to reconstruct permutation
  ll x(0);  // Tracks minimum prefix sum
  for (ll p = 1; p < n; p++) {
    scanf("%lld", &a[p]);           // Read next difference
    a[p] += a[p - 1];               // Compute prefix sum
    x = (x < a[p]) ? x : a[p];      // Update minimum prefix sum
  }
  for (ll p = 0; p < n; p++) {
    a[p] -= x - 1;  // Shift values so the smallest is at least 1
  }
  std::vector<bool> b(n + 1, false);  // Used to check uniqueness in permutation
  bool possible(true);
  for (ll p = 0; p < n; p++) {
    if (a[p] > n || b[a[p]]) {  // If value out of bounds or already seen
      possible = false;
      break;
    }
    b[a[p]] = true;  // Mark value as used
  }
  if (possible) {
    for (long p = 0; p < n; p++) {
      printf("%lld ", a[p]);
    };
    puts("");
  } else {
    puts("-1");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/