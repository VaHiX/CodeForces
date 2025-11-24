// Problem: CF 2144 E2 - Looking at Towers (difficult version)
// https://codeforces.com/contest/2144/problem/E2

/*
 * Problem: E2. Looking at Towers (difficult version)
 * Purpose: Count subsequences where the left and right visible towers are the same as the original array.
 * Algorithms/Techniques:
 *   - Fenwick Tree (Binary Indexed Tree) for efficient prefix sum queries and updates
 *   - Dynamic Programming with preprocessing of left and right visibility
 *   - Modular arithmetic with precomputed powers and inverses
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n)
 */
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
#define oo 1000000000
#define mod 998244353
const int N = 300010;
int n, arr[N], po[N], inv[N];
struct Fenwick {
  int n;
  vector<long long> bit;
  Fenwick(int n = 0) { init(n); }
  void init(int n_) {
    n = n_;
    bit.assign(n + 1, 0LL);
  }
  explicit Fenwick(const vector<long long> &a) { build(a); }
  void build(const vector<long long> &a) {
    n = (int)a.size();
    bit.assign(n + 1, 0LL);
    for (int i = 1; i <= n; ++i) {
      bit[i] += a[i - 1];
      int j = i + (i & -i);
      if (j <= n)
        bit[j] += bit[i];
    }
  }
  void add(int i, long long delta) {
    for (; i <= n; i += i & -i)
      bit[i] += delta;
  }
  long long sum(int i) const {
    long long res = 0;
    for (; i > 0; i -= i & -i)
      res += bit[i];
    return res;
  }
  long long rangeSum(int l, int r) const {
    if (r < l)
      return 0;
    return sum(r) - sum(l - 1);
  }
};
inline void add(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
}
inline void sub(int &x, int y) {
  x -= y;
  if (x < 0)
    x += mod;
}
vector<int> get() {
  vector<int> v;
  for (int i = 0; i < n; i++) {
    if ((int)v.size() == 0 || arr[i] > v.back())
      v.push_back(arr[i]);
  }
  Fenwick f1((int)v.size());
  vector<int> dp((int)v.size());
  vector<int> ret(n);
  for (int idx, cur1, cur2, cur_dp, i = 0; i < n; i++) {
    idx = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
    if (idx < (int)v.size() && v[idx] == arr[i]) { // If current element is among the unique valid heights
      cur1 = f1.rangeSum(1, idx + 1); // Count of elements <= arr[i] encountered so far from left
      cur2 = (idx == 0 ? 0 : f1.rangeSum(1, idx)); // Count of smaller elements before position i from left
      cur_dp = (idx == 0 ? 1 : (long long)po[cur2] * dp[idx - 1] % mod); // Dynamic programming computation
      if (idx == (int)v.size() - 1) // If this is the maximum element in sorted height list
        ret[i] = cur_dp;
      add(dp[idx], (long long)cur_dp * inv[cur1 + 1] % mod); // Update dp for current level
    }
    if (idx < (int)v.size())
      f1.add(idx + 1, 1); // Mark that element at position idx is now seen
  }
  return ret;
}
void solve() {
  scanf("%d", &n);
  int mx = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
    mx = max(mx, arr[i]); // Find maximum element to determine which elements are "tallest"
  }
  vector<int> a = get(); // Compute contribution from left
  reverse(arr, arr + n); // Reverse the array for right-to-left processing
  vector<int> b = get(); // Compute contribution from right
  reverse(b.begin(), b.end()); // Re-reverse to align with original order
  reverse(arr, arr + n);
  int ans = 0;
  int sum = 0;
  for (int cur, i = n - 1; i >= 0; i--) {
    if (arr[i] != mx) { // If current element is not maximum, update sum
      sum = (long long)sum * 2 % mod;
      continue; // Skip processing since it's not a "tallest" element
    }
    cur = sum; // Initial contribution of previous elements
    add(cur, b[i]); // Add the right-hand side contribution at index i
    add(ans, (long long)a[i] * cur % mod); // Accumulate answer with current product
    sum = (long long)sum * 2 % mod; // Double the sum for next iteration
    add(sum, b[i]); // Add the effect of element at position i to the accumulated sum
  }
  printf("%d\n", ans);
}
int main() {
  int in = (mod + 1) / 2;
  po[0] = inv[0] = 1;
  for (int i = 1; i < N; i++) {
    po[i] = (long long)2 * po[i - 1] % mod; // Precompute powers of 2 modulo mod
    inv[i] = (long long)in * inv[i - 1] % mod; // Precompute inverses of powers of 2 
  }
  int t = 1;
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/