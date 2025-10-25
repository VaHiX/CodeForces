// Problem: CF 1957 D - A BIT of an Inequality
// https://codeforces.com/contest/1957/problem/D

/*
 * Problem: D. A BIT of an Inequality
 * 
 * Purpose: 
 *   Count the number of tuples (x, y, z) such that 1 ≤ x ≤ y ≤ z ≤ n 
 *   and f(x, y) ⊕ f(y, z) > f(x, z), where f(l, r) = a_l ⊕ a_{l+1} ⊕ ... ⊕ a_r.
 * 
 * Algorithm:
 *   - Use prefix XOR to compute f(x, y) = s[y] ⊕ s[x-1]
 *   - For each position i, we analyze the bit at the highest position where a[i] has a 1.
 *   - For that bit, we count how many prefix XORs before i have a 1 (l1), and how many have 0 (l0).
 *   - Similarly, count how many after i (including i) have 1 (r1) and 0 (r0).
 *   - The valid combinations are when (l1, r1) or (l0, r0) pairs are chosen, contributing to the result.
 * 
 * Time Complexity: O(31 * n) = O(n) since 31 is a constant
 * Space Complexity: O(n * 31) = O(n) for the pre array storing prefix counts of bits
 */

#include <iostream>

#define i64 long long
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int a[N], s[N];
int pre[N][31]; // pre[i][j]: number of prefix XOR values up to index i with bit j set to 1

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  
  // Compute prefix XOR and bit counts
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] ^ a[i]; // Prefix XOR from index 1 to i
    for (int j = 30; j >= 0; j--)
      pre[i][j] = pre[i - 1][j] + (s[i] >> j & 1); // Count how many prefix XORs have bit j set to 1
  }
  
  i64 ans = 0;
  for (int i = 1; i <= n; i++) {
    int x = 0;
    // Find the most significant bit where a[i] is 1
    for (int j = 30; j >= 0; j--) {
      if (a[i] >> j & 1) {
        x = j;
        break;
      }
    }
    // Count elements before and after with bit x set to 1 or 0
    int l1 = pre[i - 1][x];    // Number of prefix XORs before i with bit x = 1
    int l0 = i - l1;           // Number of prefix XORs before i with bit x = 0
    int r1 = pre[n][x] - l1;   // Number of prefix XORs from i to n with bit x = 1
    int r0 = n - i + 1 - r1;   // Number of prefix XORs from i to n with bit x = 0
    // Add valid combinations
    ans += 1LL * l1 * r1 + 1LL * l0 * r0;
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/