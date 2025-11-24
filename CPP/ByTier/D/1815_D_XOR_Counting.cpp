// Problem: CF 1815 D - XOR Counting
// https://codeforces.com/contest/1815/problem/D

/*
 * Problem: XOR Counting
 * Algorithm: Dynamic Programming with Bit Manipulation
 * 
 * Time Complexity: O(log n) per test case
 * Space Complexity: O(1)
 * 
 * Approach:
 * - For m = 1, the result is simply n.
 * - For m = 2, we use bit-by-bit dynamic programming to count how many times each bit contributes to the XOR sum.
 * - For m > 2, we observe a pattern in the contribution of bits to the XOR sum and calculate accordingly.
 * 
 * The solution handles large values of n (up to 10^18) efficiently using bit manipulation and modular arithmetic.
 */

#include <iostream>

using namespace std;
const int BASE = 998244353;
int add(int x, int y) {
  x += y;
  if (x >= BASE)
    return x - BASE;
  return x;
}
int mult(int x, int y) { return (long long)x * y % BASE; }
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int tests;
  cin >> tests;
  while (tests--) {
    long long n, m;
    cin >> n >> m;
    if (m == 1)
      cout << n % BASE << '\n';
    else if (m > 2) {
      long long k = n / 2;
      long long k2 = k + 1;
      if (k & 1)
        k2 >>= 1;
      else
        k >>= 1;
      long long v = (k % BASE) * (k2 % BASE) % BASE;
      long long a = 2 * v % BASE;
      if (n & 1)
        a = (a + ((n + 1) / 2)) % BASE;
      cout << a << '\n';
    } else {
      int cnt[2]{1, 0}, sum[2]{};
      for (int i = 0; (1LL << i) <= n; ++i) {
        int bit = (1LL << i) % BASE;
        int cnt2[2]{}, sum2[2]{};
        if (n & (1LL << i)) {
          // When the bit is set in n, we can choose either 0 or 1 for the current bit of a1 and a2
          // This updates counts and sums for both possible choices
          cnt2[0] = add(cnt2[0], cnt[0]);
          sum2[0] = add(sum2[0], add(sum[0], mult(cnt[0], bit)));
          cnt2[0] = add(cnt2[0], cnt[1]);
          sum2[0] = add(sum2[0], sum[1]);
          cnt2[1] = add(cnt2[1], cnt[1]);
          sum2[1] = add(sum2[1], sum[1]);
        } else {
          // When the bit is not set in n, we must ensure the XOR results in 0
          // This updates counts and sums accordingly
          cnt2[0] = add(cnt2[0], cnt[0]);
          sum2[0] = add(sum2[0], sum[0]);
          cnt2[1] = add(cnt2[1], cnt[0]);
          sum2[1] = add(sum2[1], sum[0]);
          cnt2[1] = add(cnt2[1], cnt[1]);
          sum2[1] = add(sum2[1], add(sum[1], mult(cnt[1], bit)));
        }
        cnt[0] = cnt2[0], cnt[1] = cnt2[1];
        sum[0] = sum2[0], sum[1] = sum2[1];
      }
      cout << sum[0] << '\n';
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/