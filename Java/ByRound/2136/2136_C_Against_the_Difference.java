// Problem: CF 2136 C - Against the Difference
// https://codeforces.com/contest/2136/problem/C

/*
 * Problem: C. Against the Difference
 * 
 * Purpose:
 *   This code finds the length of the longest "neat" subsequence from a given array.
 *   A neat subsequence is one that can be split into blocks, where each block consists
 *   of equal elements and the value of the element equals the size of the block.
 *   
 * Algorithm:
 *   - Dynamic Programming with preprocessing:
 *     For each position i in the array, we compute the maximum length of a neat subsequence
 *     ending at or before this position.
 *     - We maintain a list of positions for each possible element value.
 *     - Using these lists, we determine if a block of size k can form a valid extension
 *       to a previous neat subsequence.
 *   
 * Time Complexity: O(n)
 *   Each element is processed once, and for each element, we only do constant-time operations
 *   involving list lookups and updates to dp array.
 *   
 * Space Complexity: O(n)
 *   We use arrays/presumably lists of size up to n for dp, p, and a.
 */

import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter w = new PrintWriter(System.out);
        int t = Integer.parseInt(r.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(r.readLine());
            StringTokenizer st = new StringTokenizer(r.readLine());
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = Integer.parseInt(st.nextToken());
            }
            
            // p[v] will store all indices where value v appears
            @SuppressWarnings("unchecked")
            List<Integer>[] p = new ArrayList[n + 1];
            for (int i = 0; i <= n; i++) {
                p[i] = new ArrayList<>();
            }
            
            // dp[i] represents the maximum length of neat subsequence in first i elements
            int[] dp = new int[n + 1];
            
            // Iterate through array to build up dp table
            for (int i = 1; i <= n; i++) {
                // Start with previous best result
                dp[i] = dp[i - 1];
                
                // Current value
                int v = a[i - 1];
                
                // Add current index to list of positions for this value
                p[v].add(i - 1);
                
                // If we have enough occurrences of value v to form a block of size v,
                // consider forming a new block ending at current position
                if (p[v].size() >= v) {
                    int j = p[v].get(p[v].size() - v); // Get the start index of this potential block
                    dp[i] = Math.max(dp[i], dp[j] + v); // Update max length
                }
            }
            
            w.println(dp[n]);
        }
        w.flush();
    }
}


// https://github.com/VaHiX/codeForces/