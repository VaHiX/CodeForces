// Problem: CF 2125 D - Segments Covering
// https://codeforces.com/contest/2125/problem/D

/*
 * Problem: D. Segments Covering
 * 
 * Purpose: Calculate the probability that each cell in a strip of m cells is covered by exactly one segment.
 * 
 * Algorithm:
 * - Use dynamic programming with segment updates.
 * - For each segment [l, r], compute its contribution as (p/q) / ((q-p)/q) = p/(q-p), stored as w.
 * - Precompute combined probability B of all segments being valid.
 * - Build DP table where dp[x] represents the total probability of covering cells 1..x such that cell x is covered by exactly one segment.
 * - Apply inclusion-exclusion or similar logic through segment updates at each right endpoint.
 * 
 * Time Complexity: O(n log n + m)
 * Space Complexity: O(n + m)
 */

import java.io.*;
import java.util.*;
public class Main {
    static final int MOD = 998244353;
    
    // Fast modular exponentiation
    static long modexp(long a, long e) {
        long res = 1;
        a %= MOD;
        while (e > 0) {
            if ((e & 1) == 1) res = res * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return res;
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String[] nm = br.readLine().split(" ");
        int n = Integer.parseInt(nm[0]);
        int m = Integer.parseInt(nm[1]);
        
        // Group segments by their right endpoint
        @SuppressWarnings("unchecked")
        ArrayList<long[]>[] by_r = new ArrayList[m + 2];
        for (int i = 0; i <= m + 1; i++) by_r[i] = new ArrayList<>();
        
        long B = 1;
        for (int i = 0; i < n; i++) {
            String[] parts = br.readLine().split(" ");
            int l = Integer.parseInt(parts[0]);
            int r = Integer.parseInt(parts[1]);
            int p = Integer.parseInt(parts[2]);
            int q = Integer.parseInt(parts[3]);
            
            // Compute (q - p) % MOD, since we're working with probabilities
            long qp = (q - p + MOD) % MOD;
            // Modular inverse of q
            long inv_q = modexp(q, MOD - 2);
            // Multiply into overall product B
            B = B * qp % MOD * inv_q % MOD;
            
            // Invert the probability term for weighting in dp
            long inv_qp = modexp(qp, MOD - 2);
            long w = (long) p * inv_qp % MOD;
            
            // Store l and weight w for later processing
            by_r[r].add(new long[]{l, w});
        }
        
        // DP array to track how many ways we can reach each cell with a single segment covering it
        long[] dp = new long[m + 2];
        dp[0] = 1; // Base case
        
        for (int x = 1; x <= m; x++) {
            long sum = 0;
            // Process all segments ending at x
            for (long[] seg : by_r[x]) {
                int l = (int) seg[0];
                long w = seg[1];
                // Add contribution: dp[l-1] * w mod MOD
                sum = (sum + dp[l - 1] * w % MOD) % MOD;
            }
            dp[x] = sum;
        }
        
        // Final answer is dp[m] multiplied by B to get final probability
        long ans = dp[m] * B % MOD;
        out.println(ans);
        out.flush();
    }
}


// https://github.com/VaHiX/CodeForces/