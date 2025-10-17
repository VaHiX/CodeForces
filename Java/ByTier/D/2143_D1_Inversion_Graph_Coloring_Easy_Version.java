// Problem: CF 2143 D1 - Inversion Graph Coloring (Easy Version)
// https://codeforces.com/contest/2143/problem/D1

/*
 * Problem: D1. Inversion Graph Coloring (Easy Version)
 * Algorithm: Dynamic Programming on subsequences with state tracking of colorings
 * Time Complexity: O(n^3) per test case
 * Space Complexity: O(n^2)
 *
 * Description:
 * A good subsequence is one where we can color each element red or blue such that 
 * for any inversion (i < j and a[i] > a[j]), the two elements have different colors.
 * This means that in a good subsequence, no increasing subsequence of length 3 exists.
 * We use dynamic programming to count valid subsequences by tracking the number of 
 * ways to color prefixes with specific final two elements' colors.
 */

import java.io.*;
import java.lang.reflect.Parameter;
import java.util.ArrayList;

public class A {
    public static int pog = 1000000007;
    
    public static void main(String[] args) throws IOException {
        BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        int t = Integer.parseInt(bf.readLine());
        
        for (int ch = 0; ch < t; ch++) {
            int n = Integer.parseInt(bf.readLine());
            long[][] dp = new long[n + 1][n + 1]; // dp[i][j]: number of valid colorings ending with elements i and j
            // Initialize DP table
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= n; j++)
                    dp[i][j] = -1;
            }
            dp[0][0] = 1; // base case: empty sequence has one way to color
            
            String[] temp = bf.readLine().split(" ");
            
            for (int i = 0; i < n; i++) {
                int cur = Integer.parseInt(temp[i]);
                
                // Update dp table based on previous values for current element
                // First loop handles transitions where we extend the sequence with current element
                for (int k = cur; k >= 0; k--) {
                    for (int k2 = k; k2 >= 0; k2--) {
                        if (dp[k][k2] > -1) { // Only process valid states
                            if (dp[cur][k2] == -1) 
                                dp[cur][k2] = 0;
                            dp[cur][k2] = (dp[cur][k2] + dp[k][k2]) % pog; // Accumulate number of colorings
                        }
                    }
                }
                
                // Second loop handles transitions for elements that can be added after cur
                for (int k = cur + 1; k <= n; k++) {
                    for (int k2 = cur; k2 >= 0; k2--) {
                        if (dp[k][k2] > -1) { // Only process valid states
                            if (dp[k][cur] == -1)
                                dp[k][cur] = 0;
                            dp[k][cur] = (dp[k][cur] + dp[k][k2]) % pog; // Accumulate number of colorings
                        }
                    }
                }
            }
            
            long res = 0;
            // Sum up all valid ways to complete the coloring
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= n; j++) {
                    if (dp[i][j] > -1)
                        res = (res + dp[i][j]) % pog;
                }
            }
            bw.write(res + "\n");
        }
        bw.flush();
    }
}


// https://github.com/VaHiX/codeForces/