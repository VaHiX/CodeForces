// Problem: CF 1800 F - Dasha and Nightmares
// https://codeforces.com/contest/1800/problem/F

/*
 * Problem: Dasha and Nightmares
 * 
 * Purpose:
 *   Count the number of "nightmares" formed by concatenating two words s_i and s_j,
 *   such that:
 *   1. The resulting string has odd length.
 *   2. It contains exactly 25 distinct letters.
 *   3. Each letter appears an odd number of times.
 *   
 * Approach:
 *   - Use bitmasks to represent the set of characters in each word (26 bits total).
 *   - For each word, compute its bitmask and its character presence mask.
 *   - Iterate over each of the 26 letters. For each letter, we check which words
 *     do not contain it (this allows forming an odd-length result when combining).
 *   - For words lacking a particular letter, we modify their bitmask by removing
 *     that letter (to facilitate the condition of exactly 25 letters).
 *   - Maintain a frequency map (mp) of these modified masks.
 *   - When processing a new word, check how many previous modified masks
 *     would form a valid nightmare if XOR'd with the current one.
 *   - Reinitialize the map after each letter iteration to ensure correctness.
 *   
 * Complexity:
 *   Time: O(26 * n) = O(n), since 26 is a constant.
 *   Space: O(2^25) = O(33554432) = O(1) assuming fixed-size lookup table.
 */

#include <stdio.h>
#include <iostream>

using namespace std;
typedef long long LL;
const int N = 5e6 + 5;
char s[N];
int a[N], b[N], mp[1 << 25];  // a[i]: bitmask of s_i, b[i]: presence of characters in s_i
int main() {
  int n;
  scanf("%d", &n);
  LL ans = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    for (int j = 1; s[j]; j++)
      a[i] ^= 1 << s[j] - 'a', b[i] |= 1 << s[j] - 'a';  // Build bitmask of unique chars and presence
  }
  for (int x = 0; x < 26; x++) {  // For each of the 26 letters
    for (int i = 1; i <= n; i++) {
      if (b[i] >> x & 1)
        continue;  // Skip if word already contains the letter x (as char)
      // Modify a[i] to simulate the removal of letter x (set that bit to 0)
      int v = ((a[i] >> (x + 1)) << x) | (a[i] & ((1 << x) - 1));
      mp[v]++;
      ans += mp[v ^ ((1 << 25) - 1)];  // Check how many previous v match with v^full_mask => forming 25 letters
    }
    for (int i = 1; i <= n; i++) {
      int v = ((a[i] >> (x + 1)) << x) | (a[i] & ((1 << x) - 1));
      mp[v] = 0;  // Reset map for this letter x
    }
  }
  printf("%lld", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/