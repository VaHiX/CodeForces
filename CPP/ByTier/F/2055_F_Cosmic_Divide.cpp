// Problem: CF 2055 F - Cosmic Divide
// https://codeforces.com/contest/2055/problem/F

/*
F. Cosmic Divide

Purpose:
This code determines whether a given convex polyomino can be partitioned into two disjoint connected polyominoes that are congruent to each other (i.e., one is a translation of the other).

Approach:
- For each test case, we parse row-wise column ranges.
- If area is odd, impossible; but problem guarantees even.
- We check for special patterns using Z-algorithm on differences between row positions.
- Uses the Z-algorithm for pattern matching to find valid symmetric partitions.

Time Complexity:
O(n) amortized per test case due to repeated use of Z-algorithm and linear traversals over n elements.

Space Complexity:
O(N) where N = 200000, which is sufficient to handle up to 2*10^5 rows in a single test case.

Algorithms/Techniques:
- Z-algorithm (linear time pattern matching)
- Symmetric partition detection using difference arrays
- Handling of reflections by rotating the problem space.
*/

#include <stdio.h>
#include <string.h>
#define N 200000

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
int abs_(int a) { return a > 0 ? a : -a; }

// Z-algorithm implementation to compute the Z-array of an array of integers.
void zzz(int *aa, int *zz, int n) {
  int i, l, r;
  memset(zz, 0, n * sizeof *zz); // Initialize Z-array with zeros
  for (i = 1, l = 0, r = 0; i < n; i++) // Process from index 1 onwards
    if (i + zz[i - l] < r)
      zz[i] = zz[i - l]; // Use previously computed value if possible
    else {
      l = i, r = max(r, i); // Start new z-box
      while (r < n && aa[r] == aa[r - l])
        r++; // Expand box as long as match continues
      zz[i] = r - l; // Length of current match
    }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    static int ll[N], rr[N], aa[N * 2], zzl[N], zzr[N], zz[N * 2], cc[N];
    int n, h, i, k, c, d, tmp, yes;
    long long area, sum;
    scanf("%d", &n);
    area = 0;
    
    // Read row segments and calculate total area
    for (i = 0; i < n; i++) {
      scanf("%d%d", &ll[i], &rr[i]);
      area += rr[i] - ll[i] + 1;
    }
    
    c = rr[0] - ll[0] + 1; // Width of first row
    yes = 1;
    
    // Basic sanity checks for partition possibility
    if (c % 2 != 0)
      yes = 0;
    for (i = 0; i < n; i++)
      if (rr[i] - ll[i] + 1 != c || i > 0 && abs_(ll[i] - ll[i - 1]) >= c / 2) {
        yes = 0;
        break;
      }
    if (yes) {
      printf("YES\n");
      continue;
    }
    
    yes = 0;
    for (h = 0; h < 2; h++) { // Loop to consider reflections
      // Convert differences into arrays for Z-algorithm input
      for (i = n - 1; i > 0; i--)
        aa[n - 1 - i] = ll[i] - ll[i - 1];
      
      zzz(aa, zzl, n - 1); // Compute Z array of left differences
      
      for (i = 0; i + 1 < n; i++)
        aa[i] = rr[i + 1] - rr[i]; // Compute right differences
      
      zzz(aa, zzr, n - 1); // Compute Z array of right differences
      
      for (i = 0; i + 1 < n; i++)
        aa[i] = ll[i + 1] - ll[i]; // Reuse aa for left differences again
      
      for (i = 0; i + 1 < n; i++)
        aa[n - 1 + i] = rr[i + 1] - rr[i]; // Append right differences to second half
      
      zzz(aa, zz, (n - 1) * 2); // Compute Z array of combined difference array
      
      sum = 0;
      
      // Try all possible partitions k from 1 to n - 1
      for (k = 1; k < n; k++) {
        sum += rr[n - k] - ll[k - 1];
        
        // Check if the proposed split leads to equal areas
        if (k * 2 >= n &&
            sum + (long long)(c - (rr[n - k] - ll[0])) * k == area / 2) {
          
          d = rr[n - k] - rr[0]; // Determine shift amount from last row
          
          // Validate structural consistency using precomputed Z values
          if (ll[n - 1] - ll[k - 1] != d ||
              (k == 1 ? 0 : zzl[n - k]) < n - k - 1)
            continue;

          if ((k + 1 == n ? 0 : zzr[n - k]) < n - k - 1)
            continue;

          // Additional check using full combined z-array
          if (k * 2 > n + 1 &&
              zz[(n - 1) * 2 - (k * 2 - n - 1)] < k * 2 - n - 1)
            continue;
          
          yes = 1;
          
          // Validate the partition validity based on segments and connectivity
          for (i = 0; i < n; i++) {
            cc[i] = rr[i] - ll[i] + 1; // Segment length of each row
            if (i >= n - k)
              cc[i] -= cc[i - (n - k)]; // Subtract from previous row if applicable
            if ((i < k ? cc[i] <= 0 : cc[i] != 0)) {
              yes = 0;
              break;
            }
          }
          
          for (i = 0; i + n - k < k; i++)
            if (ll[i + n - k] + cc[i + n - k] != ll[i] + d) { // Translation consistency checks
              yes = 0;
              break;
            }
          
          for (i = 0; i + 1 < k; i++)
            if (max(ll[i], ll[i + 1]) >
                min(ll[i] + cc[i] - 1, ll[i + 1] + cc[i + 1] - 1)) { // Overlap check
              yes = 0;
              break;
            }
          
          if (yes)
            goto out; // Found a valid partition
        }
      }
      
      // Reflect the problem space by flipping l and r values
      for (i = 0; i < n; i++)
        tmp = -ll[i], ll[i] = -rr[i], rr[i] = tmp;
    }

  out:
    printf(yes ? "YES\n" : "NO\n");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/