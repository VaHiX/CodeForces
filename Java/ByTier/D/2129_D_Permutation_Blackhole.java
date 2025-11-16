// Problem: CF 2129 D - Permutation Blackhole
// https://codeforces.com/contest/2129/problem/D

/*
 * Problem: D. Permutation Blackhole
 * 
 * Purpose:
 * This code counts how many permutations of length n can produce a given partial coloring sequence s,
 * where each cell's score corresponds to the number of steps it took for the nearest black cell
 * to be colored after this cell was colored.
 * 
 * Algorithm:
 * Dynamic Programming with memoization, using a 4D DP state:
 * dp[l][r][leftScore][rightScore] represents the number of ways to construct valid permutations
 * on subarray [l, r], where the leftmost element has a "score" of leftScore and rightmost has score rightScore.
 * 
 * Techniques:
 * - Precomputed factorials and inverse factorials for combination computations
 * - Modular exponentiation for inverse elements
 * - Segment tree-like decomposition with binary splitting and dynamic updates
 *
 * Time Complexity:
 * O(n^3 * log^2) per test case (due to cubic DP with logarithmic scoring)
 * 
 * Space Complexity:
 * O(n^2 * log^2) for the 4D DP array.
 */

import java.io.*;
import java.util.*;
public class Main {
    static final long MOD = 998244353L;
    static final int MAXN = 110;
    static final int LOG = 12;
    static long[] fact = new long[MAXN];
    static long[] invFact = new long[MAXN];
    static long modPow(long a, long e) {
        long r = 1 % MOD;
        while (e > 0) {
            if ((e & 1) == 1) r = (r * a) % MOD;
            a = (a * a) % MOD;
            e >>= 1;
        }
        return r;
    }
    static void initFactorials() {
        fact[0] = 1;
        for (int i = 1; i < MAXN; i++) fact[i] = (fact[i - 1] * i) % MOD;
        invFact[MAXN - 1] = modPow(fact[MAXN - 1], MOD - 2);
        for (int i = MAXN - 2; i >= 0; i--) invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
    static long comb(int n, int k) {
        if (k < 0 || k > n || n < 0) return 0;
        return (((fact[n] * invFact[k]) % MOD) * invFact[n - k]) % MOD;
    }
    public static void main(String[] args) throws Exception {
        initFactorials();
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int T = fs.nextInt();
        while (T-- > 0) {
            int n = fs.nextInt();
            int[] s = new int[n + 1];
            for (int i = 1; i <= n; i++) s[i] = fs.nextInt();
            long[][][][] dp = new long[n + 3][n + 3][LOG][LOG];
            for (int i = 1; i <= n + 1; i++) dp[i][i - 1][0][0] = 1;
            if (n >= 1) dp[1][1][0][1] = (s[1] == -1 || s[1] < 1) ? 1L : 0L;
            for (int i = 2; i <= n; i++) dp[i][i][1][0] = (s[i] == -1 || s[i] < 1) ? 1L : 0L;
            for (int len = 2; len <= n; len++) {
                for (int l = 1; l + len - 1 <= n; l++) {
                    int r = l + len - 1;
                    for (int x = 0; x < LOG; x++)
                        Arrays.fill(dp[l][r][x], 0);
                    for (int k = l; k <= r; k++) {
                        int tagLeft = 0, tagRight = 0;
                        if (l == 1 && r == n) {
                        } else if (l == 1) tagRight = 1;
                        else if (r == n) tagLeft = 1;
                        else {
                            int distLeft = Math.abs((l - 1) - k);
                            int distRight = Math.abs(k - (r + 1));
                            if (distLeft <= distRight) tagLeft = 1;
                            else tagRight = 1;
                        }
                        long waysChoose = comb(r - l, k - l);
                        if (s[k] == -1) {
                            for (int ii = 0; ii < LOG; ii++) {
                                for (int jj = 0; jj < LOG; jj++) {
                                    if (ii - tagLeft < 0 || jj - tagRight < 0) continue;
                                    long sumL = 0, sumR = 0;
                                    for (int kl = 0; kl < LOG; kl++) {
                                        sumL += dp[l][k - 1][ii - tagLeft][kl];
                                        if (sumL >= MOD) sumL -= MOD;
                                    }
                                    for (int kr = 0; kr < LOG; kr++) {
                                        sumR += dp[k + 1][r][kr][jj - tagRight];
                                        if (sumR >= MOD) sumR -= MOD;
                                    }
                                    if (sumL == 0 || sumR == 0) continue;
                                    dp[l][r][ii][jj] = (dp[l][r][ii][jj] + ((sumL * sumR) % MOD) * waysChoose) % MOD;
                                }
                            }
                        } else {
                            for (int ii = 0; ii < LOG; ii++) {
                                for (int jj = 0; jj < LOG; jj++) {
                                    if (ii - tagLeft < 0 || jj - tagRight < 0) continue;
                                    long cur = 0;
                                    for (int leftSplit = 0; leftSplit < LOG; leftSplit++) {
                                        int rightSplit = s[k] - leftSplit;
                                        if (rightSplit < 0 || rightSplit >= LOG) continue;
                                        long A = dp[l][k - 1][ii - tagLeft][leftSplit];
                                        if (A == 0) continue;
                                        long B = dp[k + 1][r][rightSplit][jj - tagRight];
                                        if (B == 0) continue;
                                        cur += (A * B) % MOD;
                                        if (cur >= MOD) cur -= MOD;
                                    }
                                    if (cur != 0)
                                        dp[l][r][ii][jj] = (dp[l][r][ii][jj] + cur * waysChoose) % MOD;
                                }
                            }
                        }
                    }
                }
            }
            out.append(dp[1][n][0][0] % MOD).append('\n');
        }
        System.out.print(out.toString());
    }
    static class FastScanner {
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        private final InputStream in;
        FastScanner(InputStream in) { this.in = in; }
        private int readByte() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len < 0) return -1;
            }
            return buffer[ptr++];
        }
        private boolean isWhiteSpace(int n) {
            return n == ' ' || n == '\n' || n == '\r' || n == '\t' || n == -1;
        }
        public String next() throws IOException {
            StringBuilder sb = new StringBuilder();
            int n = readByte();
            while (isWhiteSpace(n)) n = readByte();
            if (n == -1) throw new NoSuchElementException();
            while (!isWhiteSpace(n)) {
                sb.append((char)n);
                n = readByte();
            }
            return sb.toString();
        }
        public int nextInt() throws IOException {
            int num = 0, sign = 1;
            int n = readByte();
            while (isWhiteSpace(n)) n = readByte();
            if (n == '-') {
                sign = -1;
                n = readByte();
            }
            while (!isWhiteSpace(n)) {
                if (n < '0' || n > '9') throw new InputMismatchException();
                num = num * 10 + (n - '0');
                n = readByte();
            }
            return num * sign;
        }
    }
}


// https://github.com/VaHiX/CodeForces/