// Problem: CF 2061 E - Kevin and And
// https://codeforces.com/contest/2061/problem/E

/*
E. Kevin and And
Problem: Minimize the sum of an array after performing at most k bitwise AND operations with magic values.

Algorithms/Techniques:
- Bit manipulation
- Subset enumeration
- Greedy optimization with sorting

Time Complexity: O(n * 2^m + 2^m * m + k * log(k))
Space Complexity: O(2^m + k)

The solution uses subset enumeration to precompute all possible results of AND operations
between elements in 'a' and combinations of magic values. Then, for each element,
we find the minimum value achievable using a certain number of operations.
Finally, we use a greedy strategy to select the best improvements up to k steps.
*/

#include <algorithm>
#include <iostream>

using namespace std;
const int kMaxN = 1e5 + 1;
int t, n, m, k, C, a[kMaxN], b[2000], c[2000], mi[11], z[kMaxN * 10];
long long ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t, b[0] = (1 << 30) - 1; t--;) {
    cin >> n >> m >> k, ans = C = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i]; // Read array elements
    }
    for (int i = 0; i < m; i++) {
      cin >> b[1 << i]; // Initialize magic values for single-bit subsets
    }
    // Precompute all subset masks and their AND results using bit manipulation
    for (int i = 1; i < (1 << m); i++) {
      c[i] = c[i ^ (i & (-i))] + 1, b[i] = b[i & (-i)] & b[i ^ (i & (-i))]; // Compute subset size and its AND result
    }
    for (int i = 1; i <= n; i++) {
      fill(mi, mi + m + 1, 2e9); // Reset minimum cost array for current element
      for (int j = 0; j < (1 << m); j++) {
        mi[c[j]] = min(mi[c[j]], (a[i] & b[j])); // Store the minimal result of AND with j operations
      }
      ans += a[i]; // Start with original value
      for (int j = 1; j <= m; j++) {
        z[++C] = mi[j - 1] - mi[j]; // Compute gain in case of j operations
      }
    }
    sort(z + 1, z + C + 1); // Sort gains in ascending order
    for (; k--; ans -= z[C--]) {
    } // Greedily apply top gains up to k times
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/