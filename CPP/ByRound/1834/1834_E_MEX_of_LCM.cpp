// Problem: CF 1834 E - MEX of LCM
// https://codeforces.com/contest/1834/problem/E

/*
 * Problem: E. MEX of LCM
 * Algorithm: Sliding window with LCM tracking using stack-like approach
 * Time Complexity: O(n * log(max(a[i])) + m * log(m)) where n is length of array, m is up to 30*n
 * Space Complexity: O(n + m) for arrays and auxiliary space
 * 
 * The solution uses a sliding window technique to compute all possible LCMs of subsegments.
 * It maintains a stack-like structure of LCMs and prunes invalid entries (LCMs exceeding m).
 * Then it finds the smallest missing positive integer (MEX) among computed LCMs.
 */

#include <algorithm>
#include <stdio.h>
typedef long long ll;
int t;
int n;
int a[300005];
int left[300005];
int lcm[300005];
int bb, ee;
int ff[10000005], fn;

// Compute GCD using Euclidean algorithm
int gcd(int x, int y) {
  while (y) {
    const int t(x % y);
    x = y, y = t;
  }
  return x;
}

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    const int m(n * 30); // Upper bound for LCM values to consider
    bb = 1, ee = 0; // Stack pointers for LCMs
    fn = 0; // Counter for unique LCMs found
    
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      const int le(ee + 1); // Save current end index
      lcm[ee + 1] = a[i];   // Push new element as LCM
      left[ee + 1] = i;     // Store leftmost index for this LCM

      // Process stack to update LCMs with new element
      while (ee >= bb) {
        const ll nl((ll)lcm[ee] / gcd(lcm[ee], a[i]) * a[i]); // Compute new LCM
        
        if (nl > m) {
          // If exceeding limit, remove from consideration
          lcm[ee] = 0;
          bb = ee + 1;
          break;
        }
        
        if (lcm[ee] == nl) {
          // No change, exit loop
          --ee;
          break;
        }
        
        lcm[ee] = nl; // Update LCM
        --ee;         // Pop from stack
      }
      
      // Re-add elements with updated values
      for (int j = ee + 1, lst(lcm[ee]); j <= le; j++) {
        if (lcm[j] != lst) {
          lcm[++ee] = lcm[j];
          left[ee] = left[j];
          ff[++fn] = lcm[j];
          lst = lcm[j];
        }
      }
    }

    // Sort unique LCMs
    std::sort(ff + 1, ff + fn + 1);
    
    // Add sentinel value to simplify loop
    ff[++fn] = m + 1;
    
    // Find first gap in sorted LCMs
    for (int i = 1; i <= fn; i++) {
      if (ff[i] > ff[i - 1] + 1) {
        printf("%d\n", ff[i - 1] + 1);
        break;
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/