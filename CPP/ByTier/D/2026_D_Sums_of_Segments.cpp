// Problem: CF 2026 D - Sums of Segments
// https://codeforces.com/contest/2026/problem/D

/*
D. Sums of Segments

Purpose:
This program efficiently computes the sum of elements in a specific subsequence 'b', which is constructed from all possible contiguous subarrays of input array 'a'. The key technique involves precomputing prefix sums and cumulative sums to answer range queries in O(log n) time.

Algorithms/Techniques:
- Prefix Sum Array Construction
- Binary Search for efficient query handling
- Preprocessing using cumulative sums

Time Complexity: O(n^2 + q * log n)
Space Complexity: O(n^2)

*/

#include <stdio.h>
using namespace std;
typedef long long ll;

int n, q, a[300003], s[300003]; // s[i] = prefix sum of a up to index i
ll c[300003], t[300003];       // c[i] = prefix sum of s[1..i], t[i] = prefix sum of cumulative sums

// calc(x): returns the sum of first x elements in b (after preprocessing)
ll calc(ll x) {
  int l = 0, r = n + 1;
  while (l + 1 < r) {
    int mid = (l + r) >> 1;
    // Binary search to find where prefix sum exceeds x
    if (1ll * (n + n - mid + 1) * mid / 2 <= x)
      l = mid;
    else
      r = mid;
  }
  x -= 1ll * (n + n - l + 1) * l / 2; // adjust x to be offset within current group
  // Calculate sum of elements in range using precomputed values
  ll sum = t[l] + c[x + l] - c[l] - x * s[l];
  return sum;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), s[i] = s[i - 1] + a[i], c[i] = c[i - 1] + s[i];

  // Precompute t[i]: sum of all elements in subarrays starting from i+1 to n
  for (int i = 1; i <= n; i++)
    t[i] = t[i - 1] + c[n] - c[i - 1] - 1ll * s[i - 1] * (n - i + 1);

  scanf("%d", &q);
  while (q--) {
    ll l, r;
    scanf("%lld%lld", &l, &r);
    printf("%lld\n", calc(r) - calc(l - 1));
  }
}


// https://github.com/VaHiX/codeForces/