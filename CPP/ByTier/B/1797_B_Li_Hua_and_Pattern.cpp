// Problem: CF 1797 B - Li Hua and Pattern
// https://codeforces.com/contest/1797/problem/B

/*
B. Li Hua and Pattern
time limit per test1 second
memory limit per test256 megabytes

Problem Description:
Given an n×n grid where each cell is either 0 (blue) or 1 (red), determine if it's possible to make the pattern symmetric under a 180-degree rotation by performing exactly k operations. Each operation allows flipping the color of any cell.

Algorithm:
- For a pattern to be symmetric under 180° rotation, each element at position (i, j) must equal the element at position (n-1-i, n-1-j).
- Count how many mismatches exist between these pairs.
- Since we can flip cells, each operation can fix two mismatches (by flipping both elements in a pair), or one if the pair is on the center (for odd n).
- If k is less than required operations or if remaining flips after fixing pairs is odd and board size is even (no way to balance last move), return "NO".

Time Complexity: O(n^2) per test case due to scanning all elements once.
Space Complexity: O(n^2) for storing the grid.

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<std::vector<int>> a(n, std::vector<int>(n, 0));
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < n; col++) {
        scanf("%d", &a[row][col]);
      }
    }
    long diff(0);
    // Count mismatches between symmetric positions
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < n; col++) {
        diff += (a[row][col] != a[n - 1 - row][n - 1 - col]);
      }
    }
    diff /= 2; // Each mismatch was counted twice, so divide by 2
    // Check if it's possible to fix mismatches with k operations:
    // If k < diff, not enough operations.
    // If (k - diff) is odd and n is even, impossible to balance last operation.
    if ((k < diff) || (((k - diff) % 2) && (n % 2 == 0))) {
      puts("NO");
    } else {
      puts("YES");
    }
  }
}


// https://github.com/VaHiX/codeForces/