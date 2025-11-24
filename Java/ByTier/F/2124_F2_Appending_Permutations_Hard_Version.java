// Problem: CF 2124 F2 - Appending Permutations (Hard Version)
// https://codeforces.com/contest/2124/problem/F2

/**
 * F2. Appending Permutations (Hard Version)
 * 
 * Problem Summary:
 * - We construct an array of length n by appending cyclic shifts of [1,2,...,s] for various s.
 * - Each operation appends a permutation like [r, r+1, ..., s, 1, 2, ..., r-1].
 * - There are m restrictions: a[i] != x.
 * - Count how many valid permutations can be made modulo 998244353.
 * 
 * Algorithm:
 * - Dynamic Programming on positions with tracking of chains and close values.
 * - Process rows from bottom to top (n down to 1).
 * - Use prefix sums and segment-style calculation for efficiency.
 * - Chain length computation helps determine how far we can go from a given position.
 * 
 * Time Complexity: O(n^3), due to nested loops over the array dimensions.
 * Space Complexity: O(n^2), used for storing dp, chain, suffClose arrays.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MOD = 998244353;
    
    static final class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        FastScanner(InputStream is) { in = is; }
        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        int nextInt() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return Integer.MIN_VALUE;
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            int val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }

    static int idx(int i, int j, int cols) {
        return i * cols + j;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        int t = fs.nextInt();
        StringBuilder sb = new StringBuilder();
        while (t-- > 0) {
            int n = fs.nextInt();
            int m = fs.nextInt();
            int cols = n + 2;
            int size = (n + 2) * cols; 
            byte[] forb = new byte[size];
            for (int k = 0; k < m; k++) {
                int i = fs.nextInt();
                int x = fs.nextInt();
                forb[idx(i, x, cols)] = 1;
            }
            short[] chain = new short[size];
            // Compute chain lengths from bottom to top: chain[i][j] = max k such that 
            // there's a valid extension starting at (i,j) with step size k.
            for (int i = n; i >= 1; i--) {
                int base_i = i * cols;
                int base_ip1 = (i + 1) * cols;
                for (int j = n; j >= 1; j--) {
                    int id = base_i + j;
                    if (forb[id] == 1) {
                        chain[id] = 0;
                    } else {
                        // Transition: if we can extend from (i+1, j+1), take next chain value.
                        int idNext = base_ip1 + (j + 1);
                        short nxt = (short) ( (i + 1 <= n && j + 1 <= n) ? chain[idNext] : 0 );
                        chain[id] = (short) (1 + nxt);
                    }
                }
            }
            
            // dp[i][j]: number of ways to build final array ending at this position.
            int[] dp = new int[size];
            // suffClose[i][j]: suffix sum of dp values for close positions.
            int[] suffClose = new int[size];
            // dp2[i]: total number of valid arrays when processing row i.
            int[] dp2 = new int[n + 3];
            dp2[n + 1] = 1; // Base case: no more elements to place.

            for (int i = n; i >= 1; i--) {
                int base_i = i * cols;
                int base_ip1 = (i + 1) * cols;
                int chain1 = chain[base_i + 1]; 
                
                // First compute suffClose array forward:
                for (int j = 1; j <= n; j++) {
                    int closeVal = 0;
                    if (chain1 >= j) {
                        int pos = i + j;
                        if (pos <= n + 1) closeVal = dp2[pos];
                    }
                    int val = closeVal + suffClose[base_ip1 + j];
                    if (val >= MOD) val -= MOD;
                    suffClose[base_i + j] = val;
                }

                // Then compute actual dp values:
                for (int j = 2; j <= n; j++) {
                    int c = chain[base_i + j];
                    if (c <= 0) {
                        dp[base_i + j] = 0;
                        continue;
                    }
                    int L = i + 1;
                    int R = i + c;
                    if (L > n + 1) {
                        dp[base_i + j] = 0;
                        continue;
                    }
                    if (R > n + 1) R = n + 1;
                    
                    // Sum over range [L, R] using prefix sums.
                    int s1 = suffClose[L * cols + (j - 1)];
                    int s2 = 0;
                    int rp1 = R + 1;
                    if (rp1 <= n + 1) s2 = suffClose[rp1 * cols + (j - 1)];
                    int sum = s1 - s2;
                    if (sum < 0) sum += MOD;
                    dp[base_i + j] = sum;
                }

                // Accumulate results for row i into dp2[i]:
                long acc = 0L;
                int maxL = chain1;
                for (int klen = 1; klen <= maxL; klen++) {
                    int idxp = i + klen;
                    int part = (idxp <= n + 1) ? dp2[idxp] : 0;
                    int sub = 0;
                    if (idxp <= n) {
                        int jidx = klen + 1;
                        if (jidx <= n) sub = dp[idxp * cols + jidx];
                    }
                    int add = part - sub;
                    if (add < 0) add += MOD;
                    acc += add;
                    if (acc >= (1L << 62)) acc %= MOD; 
                }
                int dpi1 = (int) (acc % MOD);
                dp[base_i + 1] = dpi1;

                // Update suffix sum for dp2[i]:
                long rowSum = 0;
                for (int j = 1; j <= n; j++) {
                    rowSum += dp[base_i + j];
                    if (rowSum >= (1L << 62)) rowSum %= MOD;
                }
                dp2[i] = (int) (rowSum % MOD);
            }
            sb.append(dp2[1]).append('\n');
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/CodeForces/