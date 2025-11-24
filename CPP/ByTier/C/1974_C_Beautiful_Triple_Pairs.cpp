// Problem: CF 1974 C - Beautiful Triple Pairs
// https://codeforces.com/contest/1974/problem/C

/*
 * Problem: Beautiful Triple Pairs
 * Algorithm: Hashing + Two-pointer technique with preprocessing
 * Time Complexity: O(n) amortized per test case
 * Space Complexity: O(n)
 *
 * The solution counts the number of "beautiful pairs" among all consecutive
 * triples in the array. A pair of triples is beautiful if exactly one element
 * differs between them.
 *
 * Approach:
 * 1. For each unique element in the array, we store all indices where it occurs.
 * 2. We process each such element and compute how many valid pairs of triples
 *    exist based on the conditions.
 * 3. The algorithm uses hashing to efficiently group elements and avoid redundant checks.
 * 4. The counting is done with careful handling of overlapping indices and avoiding double counting.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
long long t, n, a[200005], h[1000005], e[200005], b[1000005], e1[200005],
    v1[200005], h1[1000005], s1[1000005], jd2[1000005], s2[1000005], ans;
int main() {
  scanf("%lld", &t);
  for (; t; ans = 0, t--) {
    scanf("%lld", &n);
    for (long long i = 1; i <= n; i++) {
      scanf("%lld", &a[i]);
      e[i] = h[a[i]];         // Store previous occurrence of same value
      h[a[i]] = i;            // Update head of this value's indices
    }
    for (long long i = 1; i <= n; i++)
      if (h[a[i]]) {
        // Traverse all occurrences of a[i] and collect indices j where j+1 <= n
        for (long long j = h[a[i]], ith = 1; j; j = e[j])
          if (j + 1 <= n) {
            s1[a[j + 1]]++;         // Count occurrences of a[j+1]
            e1[ith] = h1[a[j + 1]]; // Store previous index for a[j+1]
            v1[ith] = j;            // Store actual index j
            h1[a[j + 1]] = ith++;   // Update head for a[j+1]
            if (j == 1)
              b[a[j + 1]]++;        // Mark start of sequence
            if (j == n - 1)
              b[a[j + 1]]++;        // Mark end of sequence
          }
        // Traverse all occurrences of a[i] again
        for (long long j = h[a[i]]; j; j = e[j])
          if (j + 1 <= n && h1[a[j + 1]]) {
            // Add number of pairs with first element different
            ans += (s1[a[j + 1]] - b[a[j + 1]]) * (s1[a[j + 1]] - 1);
            b[a[j + 1]] = 0;
            s1[a[j + 1]] = 0;
            for (long long k = h1[a[j + 1]]; k; k = e1[k])
              if (v1[k] + 2 <= n) {
                s2[a[v1[k] + 2]]++;  // Count second elements in next triple
              }
            for (long long k = h1[a[j + 1]]; k; k = e1[k])
              if (v1[k] + 2 <= n && s2[a[v1[k] + 2]]) {
                // Subtract overcounted cases
                ans -= s2[a[v1[k] + 2]] * (s2[a[v1[k] + 2]] - 1) / 2 * 3;
                s2[a[v1[k] + 2]] = 0;
              }
            h1[a[j + 1]] = 0;  // Clear memory for next iteration
          }
        // Traverse all occurrences of a[i] and collect indices j+2 <= n
        for (long long j = h[a[i]]; j; j = e[j])
          if (j + 2 <= n)
            s1[a[j + 2]]++;  // Count occurrences of a[j+2]
        for (long long j = h[a[i]]; j; j = e[j])
          if (j + 2 <= n && s1[a[j + 2]]) {
            // Add valid combinations of triples differing in third element
            ans += s1[a[j + 2]] * (s1[a[j + 2]] - 1) / 2;
            s1[a[j + 2]] = 0;
          }
        h[a[i]] = 0;  // Clear list for this element
      }
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/