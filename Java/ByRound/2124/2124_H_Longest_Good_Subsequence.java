// Problem: CF 2124 H - Longest Good Subsequence
// https://codeforces.com/contest/2124/problem/H

/*
H. Longest Good Subsequence
Algorithms/Techniques: Dynamic Programming with preprocessing and memoization.

Time Complexity: O(n^2) per test case
Space Complexity: O(n^2) for DP table + O(n) for auxiliary arrays

Problem Description:
A good subsequence b of length m satisfies:
1. 1 <= b_i <= i for each 1 <= i <= m.
2. There exists a permutation p such that for each 1 <= i <= m, 
   b_i is the smallest index where min(p[b_i], ..., p[i]) = p[i].

This means b_i represents positions in which the minimum value among p[b_i] to p[i] is p[i].
We solve using dynamic programming over all possible subsequences.
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
        int[] kk = new int[N];          // Stores last occurrence of value 'a' in current window
        int[][] dp = new int[N][N];     // dp[i][j] stores the maximum length ending at i with last element at j
        while (t-- > 0) {
            int n = sc.nextInt();
            for (int i = 0; i < n; i++) {
                aa[i] = sc.nextInt() - 1;   // Convert to 0-based indexing
            }
            int ans = 0;
            for (int i = n - 1; i >= 0; i--) {
                Arrays.fill(kk, 0, n, -1);  // Reset kk array for current i
                for (int j = i; j < n; j++) {
                    if (i == j) {           // Base case: single element subsequence
                        dp[i][j] = -1;
                    } else {
                        dp[i][j] = dp[i][j - 1]; // Propagate previous value
                    }
                    int a = aa[j];
                    if (a >= aa[i]) {       // Only proceed if valid constraint is met
                        if ((i == j || dp[i][j - 1] >= a) && kk[a] == -1) {
                            kk[a] = j;      // Mark position of first occurrence of 'a' in range
                        }
                        if (kk[a] == -1) {
                            dp[i][j] = max(dp[i][j], -1);
                        } else {
                            int prev = (kk[a] == j) ? a : dp[kk[a]][j - 1];
                            dp[i][j] = max(dp[i][j], prev + 1); // Recalculate based on previous state
                        }
                    }
                }
                if (aa[i] == 0) {           // If first element is 0, update answer
                    ans = max(ans, dp[i][n - 1]);
                }
            }
            System.out.println(ans);
        }
        sc.close();
    }
}


// https://github.com/VaHiX/CodeForces/