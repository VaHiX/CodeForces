// Problem: CF 2004 G - Substring Compression
// https://codeforces.com/contest/2004/problem/G

/*
 * Problem: G. Substring Compression
 * 
 * Purpose: 
 *   For each substring of length k in the given string s, compute the minimum 
 *   length of the string after applying the compression operation defined as:
 *   1. Split the string into an even number of non-empty substrings.
 *   2. Concatenate them in the form t2*t1, t4*t3, ..., where * means repetition.
 *   Return the minimal possible length after this process.
 * 
 * Approach:
 *   - Use a divide-and-conquer algorithm to process all substrings efficiently.
 *   - For each recursive segment, compute the left and right parts of a potential split
 *     and calculate minimal cost for valid splits.
 *   - The algorithm uses dynamic programming with precomputed values for optimal
 *     splitting points.
 * 
 * Time Complexity: O(n * k * log(n))
 * Space Complexity: O(n * k)
 * 
 * Techniques:
 *   - Divide and conquer
 *   - Dynamic Programming
 *   - Preprocessing of prefix/suffix costs
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 200005;
int n, k;
char s[N];
int L[N][10], R[N][10];
int res[N];

// Function to calculate minimal cost for compressing a substring
void calc(int l, int r) {
  if (r - l + 1 < k)
    return;  // Not enough length to form a valid split
  int m = (l + r) / 2;
  for (int d = 0; d <= 9; ++d) {
    for (int x = 0; x <= 9; ++x) {
      L[m + 1][x] = 1e9;  // Initialize left DP table
      R[m][x] = 1e9;      // Initialize right DP table
    }
    L[m + 1][d] = 0;        // Base case for left side
    R[m][d] = 0;            // Base case for right side
    
    // Compute L[i][p] for prefix costs from m down to l
    for (int i = m; i >= l && i >= m - k + 1; --i) {
      L[i][0] = L[i + 1][s[i] - '0'];  // Transition: if we end at digit s[i]
      for (int p = 1; p <= 9; ++p)
        L[i][p] = p + min(L[i + 1][0], L[i + 1][p]);  // Cost to switch to digit p
    }
    
    // Compute R[i][p] for suffix costs from m+1 up to r
    for (int i = m + 1; i <= r && i <= m + k - 1; ++i) {
      R[i][0] = 1e9;  // Initialize for transitions
      for (int p = 1; p <= 9; ++p) {
        R[i][0] = min(R[i][0], p + R[i - 1][p]);  // Transition to digit 0
        R[i][p] = R[i - 1][p] + p;  // Cost of staying at digit p
        if (s[i] - '0' == p)
          R[i][p] = min(R[i][p], R[i - 1][0]);  // Switch to digit 0 if matches
      }
    }
    
    // For all valid splits within current segment, update res array
    for (int i = max(l, m - k + 1); i <= m; ++i)
      if (i + k - 1 <= r)
        res[i] = min(res[i], L[i][0] + R[i + k - 1][0]);
  }
  calc(l, m - 1);  // Recursively process left half
  calc(m + 1, r);  // Recursively process right half
}

int main() {
  scanf("%d%d%s", &n, &k, s + 1);  // Read input and adjust indexing to 1-based
  for (int i = 0; i < N; ++i)
    res[i] = 1e9;  // Initialize result array with large number
  calc(1, n);  // Start divide and conquer process
  for (int i = 1; i <= n - k + 1; ++i)
    printf("%d ", res[i]);  // Output final results
  return 0;
}


// https://github.com/VaHiX/CodeForces/