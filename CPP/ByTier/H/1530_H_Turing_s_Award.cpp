// Problem: CF 1530 H - Turing's Award
// https://codeforces.com/contest/1530/problem/H

/*
H. Turing's Award

Problem Description:
Alan Turing is given a permutation of integers from 1 to n and writes them into cells on an infinite tape,
deciding at each step whether to move left, right, or stay in place. The goal is to maximize the length of 
the longest increasing subsequence (LIS) of the final sequence of integers written in cells.

Algorithm:
- Dynamic Programming approach with segment trees to efficiently manage updates and queries for 
  leftmost and rightmost positions where elements can be placed.
- The algorithm considers two main cases for positioning the final element:
  1. The last element `a[n]` is placed at position `n`.
  2. The last element `a[n]` is placed at any other position.

Time Complexity: O(n^2 * log n)
Space Complexity: O(n * log n)

*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 15005;
int n, ans, a[N], fl[N], fr[N], gl[N], gr[N], Cl[N], Cr[N];

// Binary Indexed Tree (Fenwick Tree) for minimum queries on left
void addl(int x, int k) {
  for (; x; x -= x & -x)
    Cl[x] = min(Cl[x], k);
}

// Binary Indexed Tree (Fenwick Tree) for maximum queries on right
void addr(int x, int k) {
  for (; x <= n; x += x & -x)
    Cr[x] = max(Cr[x], k);
}

// Get minimum value from BIT (left query)
int getl(int x) {
  int res = n + 1;
  for (; x <= n; x += x & -x)
    res = min(res, Cl[x]);
  return res;
}

// Get maximum value from BIT (right query)
int getr(int x) {
  int res = 0;
  for (; x; x -= x & -x)
    res = max(res, Cr[x]);
  return res;
}

// Dynamic programming step
void DP(int o) {
  for (int len = o;; len++) {
    int flag = 0;
    // Check if current boundaries still allow movement
    for (int i = 1; i <= n; i++)
      flag |= fl[i] <= n | fr[i] >= 1;
    if (!flag) {
      ans = max(ans, len - o);
      return;
    }
    // Reset the BITs for next iteration
    for (int i = 0; i <= n; i++)
      Cl[i] = n + 1, Cr[i] = 0;
    
    // Traverse from right to left updating positions
    for (int i = n; i >= 1; i--) {
      if (i + 1 <= n)
        addl(a[i + 1], fl[i + 1]), addr(a[i + 1], fr[i + 1]);
      if (i + len <= n)
        addl(fr[i + len], a[i + len]), addr(fl[i + len], a[i + len]);
      gl[i] = getl(a[i]);
      gr[i] = getr(a[i]);
    }
    
    // Update fl and fr for next iteration
    for (int i = 1; i <= n; i++)
      fl[i] = gl[i], fr[i] = gr[i];
  }
}

// Process a single test case
void xxx() {
  scanf("%d", &n);
  ans = 0;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  
  // Initial setup: fl and fr initialized to a[i]
  for (int i = 1; i <= n; i++)
    fl[i] = fr[i] = a[i];
  
  DP(2); // Try placing last element at multiple positions
  
  // Reset boundaries to allow movement from the end
  for (int i = 1; i < n; i++)
    fl[i] = n + 1, fr[i] = 0;
  fl[n] = fr[n] = a[n];
  
  DP(1); // Try placing last element at starting position
  
  printf("%d\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    xxx();
  return 0;
}


// https://github.com/VaHiX/codeForces/