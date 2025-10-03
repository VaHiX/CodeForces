// Problem: CF 2124 H - Longest Good Subsequence
// https://codeforces.com/contest/2124/problem/H

/*
H. Longest Good Subsequence
Algorithm: Dynamic Programming with Optimization using Preprocessing
Time Complexity: O(n^2) per test case
Space Complexity: O(n^2) for DP table and auxiliary arrays

This problem asks to find the length of the longest "good" subsequence in an array.
A good subsequence satisfies:
- Each element b_i is between 1 and i (inclusive, 1-indexed).
- There exists a permutation p such that for each i, b_i is the smallest index where 
  min(p[b_i], ..., p[i]) = p[i].

The approach uses dynamic programming:
- dp[i][j] stores the maximum length of good subsequence ending at position j with last element i.
- We iterate from right to left to build up valid subsequences and track the optimal previous positions.

Key techniques used:
1. Two-dimensional DP with optimized state transitions
2. Preprocessing with auxiliary array kk to track indices efficiently
3. Memoization for overlapping subproblems

*/
import java.util.*;
public class Main {
    static final int N = 15000;
    static int max(int a, int b) {
        return a > b ? a : b;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        int[] aa = new int[N];
        int[] kk = new int[N]; // Used to store last seen index for each value
        int[][] dp = new int[N][N]; // dp[i][j] represents max length of good subseq ending at j, with last element i
        
        while (t-- > 0) {
            int n = sc.nextInt();
            for (int i = 0; i < n; i++) {
                aa[i] = sc.nextInt() - 1; // Convert to 0-based indexing
            }
            int ans = 0;
            for (int i = n - 1; i >= 0; i--) {
                Arrays.fill(kk, 0, n, -1); // Reset kk array for current i
                for (int j = i; j < n; j++) {
                    if (i == j) {
                        dp[i][j] = -1;
                    } else {
                        dp[i][j] = dp[i][j - 1]; // Propagate from left
                    }
                    int a = aa[j];
                    // Valid condition: current element can be part of subsequence starting at i
                    if (a >= aa[i]) {
                        // If we can update dp[i][j] using this element
                        if ((i == j || dp[i][j - 1] >= a) && kk[a] == -1) {
                            kk[a] = j; // Mark index where a appeared last time
                        }
                        if (kk[a] == -1) {
                            dp[i][j] = max(dp[i][j], -1);
                        } else {
                            int prev = (kk[a] == j) ? a : dp[kk[a]][j - 1];
                            dp[i][j] = max(dp[i][j], prev + 1);
                        }
                    }
                }
                // Final check to see if we have a complete good subsequence
                if (aa[i] == 0) {
                    ans = max(ans, dp[i][n - 1]);
                }
            }
            System.out.println(ans);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/