// Problem: CF 2131 G - Wafu!
// https://codeforces.com/contest/2131/problem/G

/**
 * Problem: G. Wafu!
 * Purpose: Simulate a process where elements are removed and added to a set,
 *          computing a score based on the minimum element at each step modulo 10^9 + 7.
 * 
 * Algorithm:
 * - Uses precomputed DP values for fast computation of contributions from small values.
 * - For large k, uses recursive DFS approach with memoization for efficiency.
 * - Sorts initial set and processes elements according to their size and available operations.
 * 
 * Time Complexity: O(n log n + 30 * log k) per test case
 * Space Complexity: O(30) for DP array and recursion stack depth up to log k
 */
import java.io.*;
import java.util.*;
public class Main {
    static final long MOD = 1_000_000_007L;
    static long[] dp = new long[31]; // Precomputed values for small i
    static long dfs(int v, long k) { // Recursive DFS to compute contribution of value v with k operations
        if (k == 0) return 1L; // Base case: no more operations
        long ans = (v + 1L) % MOD;
        v = Math.min(v - 1, 30); // Limit v to prevent overflow, since dp[30] covers all needed cases
        k -= 1;
        for (int j = 0; j <= v; ++j) {
            long need = 1L << j; // Compute how many operations needed for level j
            if (k >= need) { // If we have enough operations to go through this level
                ans = ans * dp[j] % MOD;
                k -= need;
            } else { // Otherwise, recursively compute
                ans = ans * dfs(j, k) % MOD;
                break;
            }
        }
        return ans % MOD;
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        dp[0] = 1L; // Base case for DP
        for (int i = 1; i <= 30; ++i) {
            long val = i + 1L; // Start with the value itself as multiplier
            for (int j = 0; j < i; ++j) {
                val = (val * dp[j]) % MOD; // Multiply by all previous DP values
            }
            dp[i] = val;
        }
        int t = fs.nextInt();
        StringBuilder sb = new StringBuilder();
        while (t-- > 0) {
            int n = fs.nextInt();
            long k = fs.nextLong();
            int[] s = new int[n];
            for (int i = 0; i < n; ++i) s[i] = fs.nextInt() - 1; // Convert to zero-based indexing
            Arrays.sort(s);
            long ans = 1L;
            boolean done = false;
            for (int i = 0; i < n; ++i) {
                int v = s[i];
                if (v <= 30 && k >= (1L << v)) { // Use DP table for small values and enough operations
                    k -= (1L << v);
                    ans = ans * dp[v] % MOD;
                } else { // Recursively compute for remaining operations
                    ans = ans * dfs(v, k) % MOD;
                    done = true;
                    break;
                }
            }
            sb.append(ans % MOD).append('\n');
        }
        System.out.print(sb.toString());
    }
    static class FastScanner {
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
            while (c > ' ') { val = val * 10 + (c - '0'); c = read(); }
            return val * sign;
        }
        long nextLong() throws IOException {
            int c;
            while ((c = read()) <= ' ') if (c == -1) return Long.MIN_VALUE;
            int sign = 1;
            if (c == '-') { sign = -1; c = read(); }
            long val = 0;
            while (c > ' ') { val = val * 10 + (c - '0'); c = read(); }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/codeForces/