// Problem: CF 1165 E - Two Arrays and Sum of Functions
// https://codeforces.com/contest/1165/problem/E

/*
E. Two Arrays and Sum of Functions
Algorithms/Techniques: Sorting, Greedy, Math
Time Complexity: O(n log n)
Space Complexity: O(n)

The problem asks to minimize the sum of all subarray sums f(l,r) by optimally rearranging array b.
- For each element a[i], it contributes to f(l,r) when l <= i <= r.
- The number of such subarrays is (i+1)*(n-i), since there are (i+1) choices for left boundary and (n-i) choices for right boundary.
- To minimize the total sum, we should pair largest a[i] with smallest b[j] and so on.
- This results in sorting a[] and b[], then pairing a[i] with b[n-1-i].
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 2e5 + 20, MOD = 998244353;
int n;
long long a[N], b[N], ans;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%lld", &a[i]), a[i] *= 1ll * (i + 1) * (n - i); // Compute contribution of each a[i]
  for (int i = 0; i < n; i++)
    scanf("%lld", &b[i]);
  sort(a, a + n), sort(b, b + n); // Sort both arrays
  for (int i = 0; i < n; i++) {
    a[i] %= MOD;
    ans += 1ll * a[i] * b[n - i - 1]; // Pair largest a with smallest b to minimize sum
    ans %= MOD;
  }
  printf("%lld", ans);
}


// https://github.com/VaHiX/codeForces/