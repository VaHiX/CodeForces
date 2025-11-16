// Problem: CF 1808 C - Unlucky Numbers
// https://codeforces.com/contest/1808/problem/C

/*
 * Problem: Unlucky Numbers
 * Purpose: Find the number in range [l, r] with maximum difference between max and min digits (i.e., "unluckiest").
 * Algorithm: Digit Dynamic Programming (Digit DP) with pruning.
 * 
 * Approach:
 * - Use digit DP to iterate all numbers in [l, r] and find the one with maximum digit difference.
 * - The core idea is to build numbers digit by digit, track upper and lower bounds, and evaluate
 *   the luckiness of each constructed number.
 * - Special cases handled:
 *   - Single digit numbers.
 *   - When len1 < len2 by more than 1 (construct smallest number with one more digit).
 * 
 * Time Complexity: O(log(r) * 2^10) ≈ O(log(r)), since there are at most 10 possible digits.
 * Space Complexity: O(log(r)), for storing digits of l and r.
 */

#include <stdio.h>
#include <algorithm>

#define int long long
using namespace std;

int l, r, val, ans, len1, len2, c[105], a[105], b[105], T;

// Function to compute maximum and minimum digits and update result accordingly
void work(int len, int pos) {
  int mx = 0, mn = 0x3f3f3f3f; // Initialize max and min
  for (int i = pos; i <= len; i++)
    mx = max(mx, c[i]), mn = min(mn, c[i]); // Find max and min in current suffix
  if (mx - mn < ans) { // If current luckiness is less than best so far
    ans = mx - mn;
    val = 0;
    for (int i = len; i >= pos; i--)
      val = val * 10 + c[i]; // Build the number from right to left
    for (int i = pos - 1; i >= 1; i--)
      val = val * 10 + c[pos]; // Fill remaining digits with same digit as last valid digit
  }
}

// Digit DP function to generate all valid numbers in range
void dfs(int pos, int lim1, int lim2, int len) {
  if (!pos || (!lim1 && !lim2)) {
    work(len, pos + 1); // Evaluate current number when we reach end
    return;
  }
  
  int st, ed;
  if (lim1)
    st = a[pos]; // Lower bound from l
  else if (pos == len)
    st = 1; // Minimum valid digit for first digit
  else
    st = 0; // Other positions can be 0
    
  if (lim2)
    ed = b[pos]; // Upper bound from r
  else
    ed = 9; // Can use up to 9
    
  for (int i = st; i <= ed; i++) {
    c[pos] = i; // Set current digit
    dfs(pos - 1, lim1 & (i == st), lim2 & (i == ed), len); // Recurse
  }
}

// Main function
signed main() {
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld%lld", &l, &r);
    ans = 15; // Initialize with a large value
    len1 = 0;
    len2 = 0;
    val = 0;
    
    // Convert l into digits array (a)
    for (int i = l; i; i = i / 10)
      a[++len1] = i % 10;
    
    // Convert r into digits array (b)
    for (int i = r; i; i = i / 10)
      b[++len2] = i % 10;
    
    // Handle base cases
    if (len1 == 1) {
      printf("%d\n", a[1]); // Single digit number is itself
      continue;
    }
    
    if (len2 - len1 > 1) {
      for (int i = 1; i <= len1 + 1; i++)
        printf("1"); // Construct smallest number with one extra digit
      printf("\n");
      continue;
    }
    
    // Perform DFS based on length of the range
    if (len1 == len2)
      dfs(len1, 1, 1, len1);
    else {
      dfs(len1, 1, 0, len1); // Check lower bound first
      dfs(len2, 0, 1, len2); // Then upper bound
    }
    
    printf("%lld\n", val); // Print result
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/