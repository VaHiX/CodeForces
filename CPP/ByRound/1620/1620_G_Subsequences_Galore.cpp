// Problem: CF 1620 G - Subsequences Galore
// https://codeforces.com/contest/1620/problem/G

/*
Algorithm/Technique:
- This problem uses inclusion-exclusion principle and subset enumeration to compute the number of distinct subsequences in all possible subsequences of given sorted strings.
- For each subset of the input strings, we calculate how many distinct subsequences are possible.
- The key insight is to use bit manipulation and dynamic programming on subsets.
- We precompute for each subset the number of unique subsequences using the fact that the strings are sorted.
- The final answer is computed by taking XOR of all values after applying the given formula.

Time Complexity: O(2^n * n * 26 + 2^n * n)
Space Complexity: O(2^n + n * 26)
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int M = 998244353;
int n, m;
char c[200004];
int cnt[23][26]; // cnt[i][j] stores count of character 'a'+j in string i
int mn[26], f[8400000]; // mn[j] stores minimum count of char 'a'+j in selected subset; f[i] stores number of distinct subsequences for subset i
ll ans;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", c), m = strlen(c);
    for (int j = 0; j < m; j++)
      cnt[i][c[j] - 'a']++; // Count each character in each string
  }
  for (int i = 1; i < (1 << n); i++) { // Iterate through all non-empty subsets
    for (int j = 0; j < 26; j++)
      mn[j] = 1e9; // Initialize for each subset
    for (int j = 0; j < n; j++)
      if (i >> j & 1) // If j-th string is included in subset
        for (int k = 0; k < 26; k++)
          mn[k] = min(mn[k], cnt[j][k]); // Get minimum count for each character
    f[i] = __builtin_parity(i) ? 1 : M - 1; // Parity check to determine sign
    for (int j = 0; j < 26; j++)
      f[i] = (ll)f[i] * (mn[j] + 1) % M; // Multiply possibilities for each character
  }
  for (int i = 0; i < n; i++) // Apply inclusion-exclusion principle using subset DP
    for (int j = 0; j < (1 << n); j++)
      if (j >> i & 1) // If string i is included in subset j
        (f[j] += f[j ^ (1 << i)]) %= M; // Add the value from removing this string from subset
  for (int i = 1; i < (1 << n); i++) { // Compute final result with given formula
    int tmp = 0;
    for (int j = 0; j < n; j++)
      if (i >> j & 1) // If string j is included
        tmp += j + 1; // Add its 1-indexed position
    tmp *= __builtin_popcount(i); // Multiply by number of strings in subset
    ans ^= (ll)tmp * f[i]; // XOR all results
  }
  printf("%lld", ans);
}


// https://github.com/VaHiX/CodeForces/