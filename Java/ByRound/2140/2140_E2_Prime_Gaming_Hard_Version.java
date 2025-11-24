// Problem: CF 2140 E2 - Prime Gaming (Hard Version)
// https://codeforces.com/contest/2140/problem/E2

/*
 * E2. Prime Gaming (Hard Version)
 *
 * Problem Description:
 * Given n piles of stones and a range [1, m], each pile can contain between 1 and m stones.
 * Players (Alice and Bob) play optimally in a game where on each turn they remove a good pile,
 * minimizing/maximizing the final stone count x.
 * Return sum of all possible values of x over valid configurations modulo 10^9+7.
 *
 * Approach:
 * - Dynamic Programming with bitmask for game state.
 * - Game tree evaluation based on who plays (Alice or Bob).
 * - Precompute winning counts W[r] of configurations with exactly r stones.
 * - Compute polynomial sums F[r] = sum_s=(0)^(m-1) (s)^r * (m-s)^(n-r)
 * - Final answer: sum_(r=0)^(n) W[r] * F[r]
 *
 * Time Complexity:
 * O(n * 2^n + n * m) per test case, due to DP construction and polynomial sums.
 * Space Complexity:
 * O(2^n + n) due to bitmask DP array and auxiliary arrays.
 */

import java.io.*;
import java.util.*;

public class Main {
    static final long MOD = 1_000_000_007L;

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int t = fs.nextInt();
        while (t-- > 0) {
            int n = fs.nextInt();
            int m = fs.nextInt();
            int k = fs.nextInt();
            int gmask = 0;
            for (int i = 0; i < k; i++) gmask |= 1 << (fs.nextInt() - 1); // Mark good positions in bitmask
            boolean[] dpFinal = buildDP(n, gmask);
            long[] W = winningCounts(dpFinal, n);
            long[] F = polySums(n, m);
            long ans = 0;
            for (int r = 0; r <= n; r++) {
                ans += (W[r] % MOD) * F[r] % MOD;
                if (ans >= MOD) ans -= MOD;
            }
            out.append(ans % MOD).append('\n');
        }
        System.out.print(out.toString());
    }

    // Builds dynamic programming table using game theory: alice maximizes, bob minimizes
    static boolean[] buildDP(int n, int gmask) {
        boolean[] prev = new boolean[2];
        prev[1] = true;
        if (n == 1) return prev;

        for (int p = 2; p <= n; p++) {
            int[] moves = goodMovesUpTo(gmask, p); // Get all good indices up to current pile size
            boolean alice = ((n - p) & 1) == 0;    // True if Alice plays, else Bob
            int size = 1 << p;
            boolean[] cur = new boolean[size];
            if (alice) { // Alice tries to win (maximize)
                for (int mask = 0; mask < size; mask++) {
                    boolean val = false;
                    for (int mv : moves) {
                        if (prev[removeBit(mask, mv)]) {
                            val = true;
                            break;
                        }
                    }
                    cur[mask] = val;
                }
            } else { // Bob tries to lose (minimize)
                for (int mask = 0; mask < size; mask++) {
                    boolean val = true;
                    for (int mv : moves) {
                        if (!prev[removeBit(mask, mv)]) {
                            val = false;
                            break;
                        }
                    }
                    cur[mask] = val;
                }
            }
            prev = cur;
        }
        return prev;
    }

    // Find all good indices in [0, p), which are marked bits in gmask
    static int[] goodMovesUpTo(int gmask, int p) {
        int limited = gmask & ((1 << p) - 1); // Mask of positions less than p
        int cnt = Integer.bitCount(limited);
        int[] res = new int[cnt];
        int idx = 0;
        for (int i = 0; i < p; i++) if (((limited >> i) & 1) == 1) res[idx++] = i;
        return res;
    }

    // Remove the i-th bit from mask
    static int removeBit(int mask, int i) {
        int lower = mask & ((1 << i) - 1);   // Lower part (bits < i)
        int higher = (mask >>> (i + 1)) << i; // Higher part shifted down to fill gap
        return lower | higher;
    }

    // Count number of winning configurations by stone count r
    static long[] winningCounts(boolean[] dp, int n) {
        long[] W = new long[n + 1];
        int lim = 1 << n;
        for (int mask = 0; mask < lim; mask++) if (dp[mask]) W[Integer.bitCount(mask)]++; // Count by population
        return W;
    }

    // Precompute polynomial sums F[r] using binomial expansion idea
    static long[] polySums(int n, int m) {
        long[] F = new long[n + 1];
        long[] aPow = new long[n + 1];
        long[] bPow = new long[n + 1];
        for (int s = 0; s < m; s++) {
            long a = s % MOD;
            long b = (m - s) % MOD;
            aPow[0] = 1;
            bPow[0] = 1;
            for (int e = 1; e <= n; e++) {
                aPow[e] = (aPow[e - 1] * a) % MOD;
                bPow[e] = (bPow[e - 1] * b) % MOD;
            }
            for (int r = 0; r <= n; r++) {
                F[r] += (bPow[r] * aPow[n - r]) % MOD;
                if (F[r] >= MOD) F[r] -= MOD;
            }
        }
        return F;
    }

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
            int c, s = 1, x = 0;
            do c = read(); while (c <= ' ');
            if (c == '-') { s = -1; c = read(); }
            while (c > ' ') {
                x = x * 10 + (c - '0');
                c = read();
            }
            return x * s;
        }
    }
}


// https://github.com/VaHiX/codeForces/
