// Problem: CF 1879 D - Sum of XOR Functions
// https://codeforces.com/contest/1879/problem/D

/*
Purpose: Calculate the sum of XOR functions over all subarrays, multiplied by the length of each subarray.
         The formula is: sum_{l=1}^n sum_{r=l}^n f(l,r) * (r-l+1), where f(l,r) is XOR of elements from l to r.

Algorithms/Techniques:
- Bitwise manipulation and prefix XOR concept
- For each bit position, compute how many times that bit contributes to the final answer
- Use dynamic programming approach to count subarrays ending at each index for both 0 and 1 bits

Time Complexity: O(30 * n) = O(n) since 30 is a constant (number of bits in integer)
Space Complexity: O(1) - only using fixed size arrays and variables

*/
#include <ctype.h>
#include <stdio.h>
#include <array>
#include <iostream>
#include <utility>

#define ll long long
using namespace std;
const int N = 3e5 + 5;
const int M = 30;
const int MOD = 998244353;
int n;
int a[N];
char getch() {
  static char buf[100000], *s1, *s2;
  return (s1 == s2) && (s2 = (s1 = buf) + fread(buf, 1, 100000, stdin)),
         s1 == s2 ? EOF : *s1++;
}
int read() {
  int x = 0;
  char ch = 0;
  while (!isdigit(ch))
    ch = getch();
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getch();
  return x;
}
void init() {}
void charming() {
  init();
  n = read();
  for (int i = 1; i <= n; ++i)
    a[i] = read();
  int ans = 0, nans;
  for (int i = 0; i < M; ++i) {
    nans = 0;
    array<int, 2> cnt = {0, 0}, sum = {0, 0};
    for (int j = 1, chk; j <= n; ++j) {
      chk = ((a[j] >> i) & 1);  // Extract i-th bit of a[j]
      if (chk == 0) {
        ++cnt[0], sum[0] = (sum[0] + cnt[0]) % MOD;  // Update for bit 0
        sum[1] = (sum[1] + cnt[1]) % MOD;            // Update for bit 1
      } else {
        swap(cnt[0], cnt[1]), ++cnt[1];              // Swap and increment cnt[1] when bit is 1
        swap(sum[0], sum[1]);                        // Swap sums accordingly
        sum[0] = (sum[0] + cnt[0]) % MOD;            // Update new sum[0]
        sum[1] = (sum[1] + cnt[1]) % MOD;            // Update new sum[1]
      }
      nans = (nans + sum[1]) % MOD; // Accumulate contribution of current bit
    }
    ans = (ans + 1ll * nans * (1 << i) % MOD) % MOD; // Add contribution of this bit to total answer
  }
  cout << ans << endl;
}
signed main() {
  charming();
  return 0;
}


// https://github.com/VaHiX/CodeForces/