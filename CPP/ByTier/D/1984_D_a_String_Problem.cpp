// Problem: CF 1984 D - ''a'' String Problem
// https://codeforces.com/contest/1984/problem/D

/*
 * Problem: Count the number of nonempty strings t != "a" such that s can be partitioned
 * into substrings where each is either t or "a" and at least one equals t.
 *
 * Algorithm:
 * - Use Z-algorithm for pattern matching to find repeating patterns in the substring
 *   that starts after all leading 'a's.
 * - For each valid repeating pattern, check whether it can be used as a t-string
 *   by verifying the structure of a valid partition.
 * - Time complexity: O(N) per test case, where N is the length of the string.
 * - Space complexity: O(N), for storing the string and auxiliary arrays.
 *
 * Techniques:
 * - Z-algorithm for pattern matching
 * - Prefix counting of 'a's
 * - Efficient filtering of valid repeating substrings
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
int N;
char A[202020];     // input string
char B[202020];     // substring from first non-'a' character
int C[202020];      // prefix count of consecutive 'a's
int Z[202020];      // Z-array for Z-algorithm
int main() {
  int tc;
  scanf("%d", &tc);
  while (tc--) {
    scanf("%s", A + 1);
    N = strlen(A + 1);
    int s = 0;
    // Find the index of the first non-'a' character
    for (int i = 1; i <= N; i++) {
      if (A[i] != 'a') {
        s = i;
        break;
      }
    }
    // If all characters are 'a', answer is N - 1
    if (!s) {
      printf("%d\n", N - 1);
      continue;
    }
    int M = N - s + 1;  // Length of the part after leading 'a's
    // Copy the suffix of A into B and initialize data structures
    for (int i = 1; i <= M; i++) {
      B[i] = A[i + s - 1];
      Z[i] = 0;
      if (B[i] == 'a')
        C[i] = C[i - 1] + 1;
      else
        C[i] = 0;
    }
    int p = 1;  // Rightmost segment's left boundary in Z-algorithm
    // Z-algorithm to compute Z-array
    for (int i = 2; i <= M; i++) {
      int r = p + Z[p] - 1;
      if (r >= i)
        Z[i] = min(r - i + 1, Z[i - p + 1]);
      while (i + Z[i] <= M && B[1 + Z[i]] == B[i + Z[i]])
        Z[i]++;
      if (i + Z[i] > p + Z[p])
        p = i;
    }
    Z[1] = M;  // Special case for Z[1] = M
    vector<int> V;
    // Collect all indices where character matches first character of B
    for (int i = 1; i <= M; i++) {
      if (B[1] == B[i]) {
        V.push_back(i);
      }
    }
    ll ans = 0;
    int K = V.size();  // Number of valid start positions
    V.push_back(M + 1);
    // Check each valid period
    for (int i = 1; i <= K; i++) {
      if (K % i)  // If not evenly divisible, skip
        continue;
      bool ok = true;
      int len = V[i] - V[0] - C[V[i] - 1];  // Length of the candidate pattern
      int mn = 3 * N;
      // Verify all segments match the pattern
      for (int j = i; j < K; j += i) {
        if (Z[V[j]] < len)
          ok = false;
        if (C[V[j + i] - 1] - C[V[j] + len - 1] != V[j + i] - (V[j] + len))
          ok = false;
        mn = min(mn, C[V[j] - 1]);
      }
      if (!ok)
        continue;
      // Account for the prefix of 'a's before the pattern starts
      for (int j = 0; j < s; j++) {
        ans += min(mn, C[M]) + 1;
        mn--;
        if (mn < 0)
          break;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/