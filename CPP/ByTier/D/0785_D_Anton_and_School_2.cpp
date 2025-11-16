// Problem: CF 785 D - Anton and School - 2
// https://codeforces.com/contest/785/problem/D

/*
 * Problem: Anton and School - 2
 * Algorithm: Dynamic Programming with Combinatorics
 * 
 * Purpose: Given a bracket sequence, count the number of distinct subsequences
 * that form a Regular Simple Bracket Sequence (RSBS). An RSBS must:
 *   1. Not be empty
 *   2. Have even length
 *   3. Start with '(' and end with ')'
 * 
 * Approach:
 *   - Use dynamic programming to count valid subsequences
 *   - For each '(' we encounter, calculate how many valid subsequences can be formed
 *     by choosing positions that pair it with a ')' later in the sequence
 *   - Combination formula C(n, k) is used to count combinations of valid pairings
 *   - Precompute factorials and modular inverses for efficient combination calculation
 * 
 * Time Complexity: O(n), where n is the length of the input string
 * Space Complexity: O(n), for storing precomputed factorials and inverses
 */

#include <stdio.h>
#include <string.h>

#define int long long
const int maxn = 2e5 + 5;
const int mod = 1e9 + 7;
int n, num1, num2, ans, inv[maxn], mul[maxn];
char s[maxn];

// Precompute factorials and modular inverses for combinations
void init() {
  inv[0] = inv[1] = mul[0] = mul[1] = 1;
  for (int i = 2; i <= n; i++) {
    mul[i] = mul[i - 1] * i % mod;
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
  }
  for (int i = 2; i <= n; i++)
    inv[i] = inv[i - 1] * inv[i] % mod;
}

// Calculate combination C(x, y) using precomputed values
int C(int x, int y) { return mul[x] * inv[y] % mod * inv[x - y] % mod; }

signed main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  init();
  
  // Count total number of ')' in the string
  for (int i = 1; i <= n; i++)
    if (s[i] == ')')
      num2++;
  
  // Iterate through characters to count valid subsequences
  for (int i = 1; i <= n; i++) {
    if (s[i] == '(') {
      num1++; // increment count of '('
      // Add number of ways to choose a valid pairing for this '('
      ans = (ans + C(num1 + num2 - 1, num1)) % mod;
    } else
      num2--; // decrement count of remaining ')'
  }
  
  printf("%lld", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/