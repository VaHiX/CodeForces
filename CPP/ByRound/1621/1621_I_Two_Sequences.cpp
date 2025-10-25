// Problem: CF 1621 I - Two Sequences
// https://codeforces.com/contest/1621/problem/I

/*
 * Problem: Apply iterative transformation on an array to produce sequence B,
 *          where each B_i = op(B_{i-1}), and op computes lexicographically minimum
 *          subarray of length i and appends it to the remaining prefix.
 *
 * Algorithms/Techniques:
 *   - Simulation with optimized sliding minimum computation per step
 *   - Preprocessing for efficient query answering
 *
 * Time Complexity: O(n^2) worst case due to nested operations in op function,
 *                  but effectively much worse than n^2 due to early termination
 * Space Complexity: O(n) for temporary arrays used in op and storing all B_i arrays
 *
 * Note: The op() function performs several optimizations based on maintaining 
 *       partial results of computations involving lexicographically smallest subarrays.
 */

#include <stdio.h>
#include <string.h>

#define N 100000
#define M 10
int min(int a, int b) { return a < b ? a : b; }

// op: performs transformation of array aa to produce next state in sequence
void op(int *aa, int n) {
  static int bb[N + 1], qq[N + 1], ll[N + 1], kk[N + 1], ll_[N], kk_[N];
  int n_, h, i, j;
  
  // Loop over input array and build transformed version
  for (i = 0, j = 0; j < n; i++, j++) {
    int q, r, l, k;
    
    // Maintain monotonic property using sliding window technique
    while (i > 0 && bb[i - qq[i] + 1] > aa[j])
      i %= qq[i];
      
    bb[i + 1] = aa[j];
    
    // Determine minimum position q for this window based on previous values
    q = i == 0 || bb[i - qq[i] + 1] < aa[j] ? i + 1 : qq[i];
    
    // Compute remainder and compute l, k efficiently using previous results
    if ((r = (i + 1) % q) == 0)
      l = q, k = (i + 1) / q;
    else
      l = ll[r], k = kk[r];
      
    // Store current state information
    qq[i + 1] = q, ll[i + 1] = l, kk[i + 1] = k;
    ll_[j] = l, kk_[j] = k;
  }
  
  // Backward pass to determine how many times each element is repeated or grouped
  for (i = n - 1; i >= 0; i--)
    ll_[i] = i + 1 == n || ll_[i + 1] == 1 ? ll_[i] : ll_[i] * kk_[i];
    
  // Reconstruct final array 'bb' from scratch considering grouping effect
  for (i = 0, n_ = 0; i < n && n_ < n; i++)
    for (h = i - ll_[i] + 1; h <= i && n_ < n; h++)
      bb[n_++] = aa[h];
      
  // Copy result back to original array
  memcpy(aa, bb, n * sizeof *bb);
}

int main() {
  static int aa[M][N]; // Preallocate memory for multiple copies of aa (max M arrays)
  int n, m, q, i;
  
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%d", &aa[0][i]);
    
  for (m = 2; m <= M; m++) {
    int updated;
    
    // Copy previous state to current one
    for (i = 0; i < n; i++)
      aa[m - 1][i] = aa[m - 2][i];
      
    // Apply transformation 
    op(aa[m - 1], n);
    
    updated = 0;
    // Check if current state differs from previous
    for (i = 0; i < n; i++)
      if (aa[m - 1][i] != aa[m - 2][i]) {
        updated = 1;
        break;
      }
      
    // Terminate early if no change occurred, since further steps won't modify array
    if (!updated)
      break;
  }

  scanf("%d", &q);
  while (q--) {
    int h;
    scanf("%d%d", &h, &i), i--;
    printf("%d\n", aa[min(h, m - 1)][i]);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/