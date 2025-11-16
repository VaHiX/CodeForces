// Problem: CF 1935 E - Distance Learning Courses in MAC
// https://codeforces.com/contest/1935/problem/E

/*
Purpose: This code solves the problem of finding the maximum possible bitwise OR of grades a student can achieve from a range of distance learning courses.
Algorithms/Techniques: 
    - Sparse Table for range OR queries
    - Prefix sum technique for bit counting
    - Bit manipulation to optimize the selection of grades
Time Complexity: O(n * log n + q * log n)
Space Complexity: O(n * log n)
*/
#include <string.h>
#include <algorithm>
#include <iostream>

using i64 = long long;
constexpr int N = 2e5 + 10;
constexpr int M = 31;
constexpr int K = 21;
int ST[K][N];  // Sparse table for range OR operations
int cnt[N][M]; // Prefix count of each bit across all courses
int n;
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    // Copy previous counts to current
    memcpy(cnt[i], cnt[i - 1], sizeof(cnt[i]));
    int x, y;
    std::cin >> x >> y;
    // Compute the difference between x and y
    int diff = (x ^ y);
    // Find the highest bit set in diff
    int bit = diff > 0 ? std::__lg(diff) : -1;
    // Compute the value that is less than y and has the same highest bit set
    int val = y & ((1 << bit + 1) - 1);
    // Increment counters for bits in val
    for (int k = M - 1; k >= 0; k--)
      if ((val >> k) & 1)
        cnt[i][k]++;
    // Store the value of y minus the part of it that has same bits as x
    ST[0][i] = y - val;
  }
  // Build sparse table for range OR queries
  for (int k = 1; k < K; k++)
    for (int i = 1; i + (1 << k) - 1 <= n; i++)
      ST[k][i] = (ST[k - 1][i] | ST[k - 1][i + (1 << (k - 1))]);
  int q;
  std::cin >> q;
  while (q--) {
    int l, r;
    std::cin >> l >> r;
    // Query the sparse table for OR of range [l, r]
    int k = std::__lg(r - l + 1);
    int ans = (ST[k][l] | ST[k][r - (1 << k) + 1]);
    // Optimize ans by considering bits from high to low
    for (int bit = M - 1; bit >= 0; bit--) {
      int t = cnt[r][bit] - cnt[l - 1][bit] + (ans >> bit & 1);
      // If there are enough bits set to make a better answer,
      // set all higher bits and break
      if (t >= 2) {
        ans |= (1 << (bit + 1)) - 1;
        break;
      } else if (t == 1) {
        // If only one bit is set in this range, set this bit
        ans |= (1 << bit);
      } else {
        // Do nothing if no bit is set
        continue;
      }
    }
    std::cout << ans << " \n"[q == 0];
  }
}
int main() {
#ifdef HeratinoNelofus
  freopen("input.txt", "r", stdin);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T;
  std::cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/