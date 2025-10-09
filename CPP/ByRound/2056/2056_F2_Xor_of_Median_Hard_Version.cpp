// Problem: CF 2056 F2 - Xor of Median (Hard Version)
// https://codeforces.com/contest/2056/problem/F2

/*
F2. Xor of Median (Hard Version)
Algorithms/Techniques: 
  - Fast Walsh-Hadamard Transform (FWHT) for subset convolution
  - Bit manipulation and inclusion-exclusion principle
  - Preprocessing of good sequence properties using bitwise operations

Time Complexity: O(k * 2^l + m * 2^l), where l is the smallest integer such that 2^l >= n
Space Complexity: O(2^l)

This implementation processes multiple test cases, each with a binary string representing a number n
and an upper bound m. It computes the XOR of medians over all "good" sequences of length n,
where elements are in [0, m), and a sequence is good if for any two values i < j present,
their counts satisfy cnt[i] <= cnt[j].
*/
#include <algorithm>
#include <ctype.h>
#include <stdio.h>
using namespace std;

inline int read() {
  int res = 0, ch = getchar();
  for (; !isdigit(ch); ch = getchar()) // Skip non-digit chars
    ;
  for (; isdigit(ch); ch = getchar())
    res = (res << 3) + (res << 1) + (ch & 15); // Convert digit to number
  return res;
}

const int N = (1 << 18) + 5;
int dp[N];
char s[N];

// C(n, m): True if m is a subset of n in binary representation
inline int C(int n, int m) { return (n & m) == m; }

// S(n, m): Helper predicate for good sequence condition using bitwise operations
inline int S(int n, int m) {
  int d = m + 1 >> 1; // Right shift of (m+1)/2
  return (n - m + d - 1 & d - 1) == d - 1;
}

int main() {
  int T = read();
  while (T--) {
    int k = read(), m = read(), n = 0, l = 0;
    scanf("%s", s + 1);
    for (int i = 1; i <= k; ++i)
      n += s[i] == '1'; // Count number of 1s in binary string
    while (1 << l < n) // Find minimal l such that 2^l >= n
      ++l;
    fill(dp, dp + (1 << l), 0); // Initialize dp array to zero

    // Compute initial values using predicate S(n,i+1)
    for (int i = 0; i < n; ++i)
      dp[i] = S(n, i + 1);
    
    // Apply FWHT (Fast Walsh-Hadamard Transform) on dp
    for (int i = 0; i < l; ++i) {
      for (int s = 0; s < 1 << l; ++s) {
        if (s & 1 << i) // If bit i is set
          dp[s] ^= dp[s ^ 1 << i]; // XOR with flipped bit
      }
    }

    int ans = 0;
    for (int s = 0; s < 1 << l && s < m; ++s) {
      if (!dp[s]) continue; // Skip zero entries

      int t = m - 1 - s >> l; // Bitwise shift

      if (t % 2 == 0)
        ans ^= s;
      if (t % 4 == 0)
        ans ^= t << l;
      else if (t % 4 == 1)
        ans ^= 1 << l;
      else if (t % 4 == 2)
        ans ^= t + 1 << l;
    }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/