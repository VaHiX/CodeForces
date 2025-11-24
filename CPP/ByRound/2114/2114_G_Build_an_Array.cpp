// Problem: CF 2114 G - Build an Array
// https://codeforces.com/contest/2114/problem/G

/*
G. Build an Array
Algorithm: Greedy + Preprocessing + Simulation
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem involves determining if we can construct a given array of length n using exactly k operations,
where each operation adds an integer to either end of the array. After adding, any adjacent equal elements are merged
by replacing them with their sum.

Key Insight:
- Each element in the final array corresponds to a segment of original numbers that were merged together.
- We decompose each number into its odd part (c[i]) and power of 2 factor (b[i]).
- Using prefix and suffix arrays, we compute max possible contribution for placing an element at index i.

Approach:
1. Decompose all numbers into odd part and its power of 2 component.
2. Compute prefix and suffix contribution arrays to determine maximum possible values at each position.
3. For each element in the array, evaluate total contribution from left, current, and right parts.
4. Check if maximum total contribution is >= k.

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int _;
  cin >> _;
  while (_--) {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
      cin >> a[i];
    
    // b[i] will store the power of 2 factor of a[i]
    vector<ll> b(n, 1), c = a;
    for (int i = 0; i < n; i++)
      while (c[i] % 2 == 0)
        c[i] /= 2, b[i] *= 2; // Decompose a[i] into odd part and power of 2

    // d[i]: prefix sum of contribution from left side up to i
    vector<ll> d(n, 0), e(n, 0);
    for (int i = 1; i < n; i++) {
      d[i] = d[i - 1];
      if ((c[i] != c[i - 1]) || (b[i] > b[i - 1]))
        d[i] += b[i - 1]; // If current element differs or has larger power of 2, add previous
      else
        d[i] += b[i - 1] - 2ll * b[i] + 1; // Otherwise, account for merging effect
    }

    // e[i]: suffix sum of contribution from right side starting from i
    for (int i = n - 2; i > -1; i--) {
      e[i] = e[i + 1];
      if ((c[i] != c[i + 1]) || (b[i] > b[i + 1]))
        e[i] += b[i + 1]; // If next element differs or has larger power of 2, add next
      else
        e[i] += b[i + 1] - 2ll * b[i] + 1; // Otherwise, account for merging effect
    }

    ll ans = 0;
    for (int i = 0; i < n; i++)
      ans = max(ans, b[i] + d[i] + e[i]); // Max contribution of placing element at index i

    if (ans < k)
      cout << "NO\n";
    else
      cout << "YES\n";
  }
}


// https://github.com/VaHiX/codeForces/