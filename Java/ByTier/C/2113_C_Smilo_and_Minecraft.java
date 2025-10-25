// Problem: CF 2113 C - Smilo and Minecraft
// https://codeforces.com/contest/2113/problem/C

/*
C. Smilo and Minecraft

Problem Description:
Smilo is playing Minecraft and wants to maximize the amount of gold collected by detonating dynamite in empty cells.
When dynamite explodes at position (x, y), it affects a square of side 2k+1 centered at that point.
Gold ore ('g') inside this square disappears if strictly inside, but gold on the boundary is collected.
Dynamite can only be placed in empty cells ('.').

Approach:
- Use prefix sums to quickly calculate how many gold pieces are present in any horizontal segment.
- For each empty cell, simulate placing dynamite and compute how much gold will be collected using precomputed row-wise sums.
- This allows efficient calculation of the total gold collected from a square explosion centered at (x, y).

Time Complexity: O(n * m)
Space Complexity: O(n * m)

Algorithms/Techniques:
- Prefix Sum technique for fast range queries
- Brute force over all empty cells with optimized sum computation
 */

import java.util.Arrays;
import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int t = sc.nextInt();
    while (t-- > 0) {
      fx(sc);
    }
  }

  public static void fx(Scanner sc) {
    int n = sc.nextInt();   // number of rows
    int m = sc.nextInt();   // number of columns
    int k = sc.nextInt();   // explosion radius parameter
    sc.nextLine();          // consume newline after reading k

    char[][] arr = new char[n][m];  // input grid

    for (int i = 0; i < n; i++) {
      String str = sc.nextLine();
      for (int j = 0; j < m; j++) {
        arr[i][j] = str.charAt(j);
      }
    }

    // Precompute prefix sums of 'g' in each row
    int[][] dp = new int[n][m];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (arr[i][j] == 'g') {
          dp[i][j] = 1;
        }
        if (j > 0) {
          dp[i][j] += dp[i][j - 1];  // prefix sum along rows
        }
      }
    }

    int res = Integer.MAX_VALUE;   // stores minimum gold loss for placing dynamite
    int total = 0;                 // total gold in grid

    // For every cell, determine how many 'g' pieces can be saved when placing dynamite
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (arr[i][j] == 'g')
          total++;
        if (arr[i][j] == '.') {           // try placing dynamite here
          int t_res = count(dp, k, j, i); // compute gold loss when explosion occurs at (i,j)
          res = Math.min(res, t_res);
        }
      }
    }

    if (res == Integer.MAX_VALUE)
      res = 0;

    System.out.println(total - res);   // total minus minimum loss gives maximum collectible gold
  }

  // Calculate how many gold cells would be lost by exploding at position (x,y) with radius k
  static int count(int[][] arr, int k, int x, int y) {
    int n = arr.length;
    int m = arr[0].length;

    int t = Math.max(0, y - (k - 1));        // topmost affected row
    int b = Math.min(n - 1, y + (k - 1));    // bottommost affected row
    int l = Math.max(-1, x - (k));           // leftmost affected column (-1 indicates no left boundary)
    int r = Math.min(m - 1, x + (k - 1));    // rightmost affected column

    int res = 0;
    for (int i = t; i <= b; i++) {
      int h = 0;
      if (l != -1) h = arr[i][l];   // prefix sum up to l
      res += Math.abs(h - arr[i][r]); // difference gives number of 'g' in range [l+1, r]
    }

    return res;
  }
}


// https://github.com/VaHiX/CodeForces/