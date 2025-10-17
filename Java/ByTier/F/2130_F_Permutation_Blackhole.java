// Problem: CF 2130 F - Permutation Blackhole
// https://codeforces.com/contest/2130/problem/F

/*
 * Problem: F. Permutation Blackhole
 * 
 * Algorithm: Dynamic Programming with Segment Tree-like approach
 * 
 * Time Complexity: O(n^4 * log^2(n)) where n <= 100
 * Space Complexity: O(n^2 * log^2(n)) 
 * 
 * This solution uses a 4D dynamic programming approach to count valid permutations
 * that can produce a given coloring sequence. The DP state tracks the number of ways
 * to color segments [l, r] with specific boundary conditions.
 * 
 * The key idea is to recursively split the permutation into left and right parts,
 * and for each split point determine how the score of that point depends on the
 * nearest black cells from left and right sides.
 * 
 * The scoring is based on the rule: when coloring a cell p[i], the score of
 * the nearest black cell is incremented.
 * 
 * State: dp[l][r][xi][yj] represents the number of ways to color segment [l,r]
 * with left boundary contribution xi and right boundary contribution yj.
 * 
 * The DP transition considers all possible split points k in [l,r] and calculates
 * valid combinations of left and right segments, accounting for fixed scores.
 * 
 * The implementation uses modular arithmetic and precomputed factorials for binomial coefficients.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final int MAXN = 110;
    static final int LOGN = 10; 
    static final long MOD = 998244353L;
    static long[] fac = new long[MAXN];
    static long[] ifac = new long[MAXN];
    
    // Fast exponentiation for modular arithmetic
    static long modpow(long a, long e) {
        long res = 1;
        while (e > 0) {
            if ((e & 1) == 1) res = (res * a) % MOD;
            a = (a * a) % MOD;
            e >>= 1;
        }
        return res;
    }
    
    // Precompute factorials and inverse factorials for combinations
    static void initComb() {
        fac[0] = 1;
        for (int i = 1; i < MAXN; ++i) fac[i] = fac[i - 1] * i % MOD;
        ifac[MAXN - 1] = modpow(fac[MAXN - 1], MOD - 2);
        for (int i = MAXN - 2; i >= 0; --i) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
    }
    
    // Compute combination C(n, k) mod MOD
    static long C(int n, int k) {
        if (n < 0 || k < 0 || k > n) return 0;
        return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
    }
    
    // Fast input scanner
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
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }
    
    public static void main(String[] args) throws Exception {
        initComb();
        FastScanner fs = new FastScanner(System.in);
        int T = fs.nextInt();
        StringBuilder sb = new StringBuilder();
        while (T-- > 0) {
            int n = fs.nextInt();
            int[] s = new int[n + 1];
            for (int i = 1; i <= n; ++i) s[i] = fs.nextInt();
            
            // dp[l][r][xi][yj] = number of ways to color segment [l,r] 
            // with left boundary contribution xi and right boundary contribution yj
            long[][][][] dp = new long[n + 3][n + 3][LOGN][LOGN];
            
            // Initialize for base cases
            for (int i = 1; i <= n + 1; ++i) {
                if (i - 1 >= 1 && i <= n) {
                    // This section doesn't actually add anything but keeps logic consistent
                }
                if (i <= n + 1) {
                    // Set the base case dp[i][i-1][0][0] = 1 if i >= 2
                    if (0 < LOGN && 0 < LOGN) dp[i][i - 1][0][0] = 1;
                }
            }
            
            // Base case for i=1 (start of sequence)
            if (1 < LOGN && 0 < LOGN) {
                dp[1][1][0][1] = (s[1] < 1) ? 1 : 0;
            }
            
            // Base case for i=2 to n (each element by itself)
            for (int i = 2; i <= n; ++i) {
                if (1 < LOGN && 0 < LOGN) {
                    dp[i][i][1][0] = (s[i] < 1) ? 1 : 0;
                }
            }
            
            // Main DP loop
            for (int len = 2; len <= n; ++len) {
                for (int l = 1; l + len - 1 <= n; ++l) {
                    int r = l + len - 1;
                    for (int xi = 0; xi < LOGN; ++xi) {
                        for (int yj = 0; yj < LOGN; ++yj) {
                            long ways = 0;
                            
                            // For each possible split point k
                            for (int k = l; k <= r; ++k) {
                                // Tag variables to determine left/right boundaries' contribution
                                int tagl = 0, tagr = 0;
                                
                                if (l == 1 && r == n) {
                                    // Special case for full array - no boundary effect
                                    tagl = tagr = 0;
                                } else if (l == 1) {
                                    // Left boundary is free - contribute
                                    tagr = 1; tagl = 0;
                                } else if (r == n) {
                                    // Right boundary is free - contribute
                                    tagl = 1; tagr = 0;
                                } else {
                                    // Calculate distance to adjacent boundaries
                                    int dl = Math.abs((l - 1) - k); 
                                    int dr = Math.abs(k - (r + 1));
                                    if (dl <= dr) tagl = 1; // Left contributes one
                                    else tagr = 1; // Right contributes one
                                }
                                
                                // Skip invalid states
                                if (xi - tagl < 0 || yj - tagr < 0) continue;
                                
                                // Define left and right segments
                                int leftL = l, leftR = k - 1;
                                int rightL = k + 1, rightR = r;
                                
                                // Compute binomial coefficient for choosing k from [l,r]
                                long comb = C(r - l, k - l);
                                
                                // If score at k is unfixed (-1)
                                if (s[k] == -1) {
                                    long sumLeft = 0;
                                    for (int a = 0; a < LOGN; ++a) {
                                        sumLeft += dp[leftL][leftR][xi - tagl][a];
                                        if (sumLeft >= MOD) sumLeft -= MOD;
                                    }
                                    long sumRight = 0;
                                    for (int b = 0; b < LOGN; ++b) {
                                        sumRight += dp[rightL][rightR][b][yj - tagr];
                                        if (sumRight >= MOD) sumRight -= MOD;
                                    }
                                    long add = (sumLeft * sumRight) % MOD;
                                    add = add * comb % MOD;
                                    ways += add;
                                    if (ways >= MOD) ways -= MOD;
                                } else {
                                    // Fixed score case
                                    int sk = s[k];
                                    for (int a = 0; a < LOGN; ++a) {
                                        int needRight = sk - a;
                                        if (needRight < 0 || needRight >= LOGN) continue;
                                        long leftVal = dp[leftL][leftR][xi - tagl][a];
                                        if (leftVal == 0) continue;
                                        long rightVal = dp[rightL][rightR][needRight][yj - tagr];
                                        if (rightVal == 0) continue;
                                        long add = leftVal * rightVal % MOD;
                                        add = add * comb % MOD;
                                        ways += add;
                                        if (ways >= MOD) ways -= MOD;
                                    }
                                }
                            }
                            dp[l][r][xi][yj] = ways % MOD;
                        }
                    }
                }
            }
            
            // Extract final answer
            long ans = dp[1][n][0][0] % MOD;
            sb.append(ans).append('\n');
        }
        System.out.print(sb.toString());
    }
}


// https://github.com/VaHiX/CodeForces/