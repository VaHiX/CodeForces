// Problem: CF 2145 G - Cost of Coloring
// https://codeforces.com/contest/2145/problem/G

/**
 * Problem: G. Cost of Coloring
 * 
 * Purpose:
 *   This code calculates the number of "beautiful" colorings of an n×m grid,
 *   where each coloring uses exactly k distinct colors and requires a minimum
 *   number of operations equal to the value i (from min(n,m) to n+m-1).
 *   
 * Algorithms/Techniques:
 *   - Dynamic Programming with generating functions
 *   - Precomputed factorials and inverse factorials for combinatorics
 *   - Modular arithmetic for large numbers
 *   
 * Time Complexity: O((n + m)^2)
 * Space Complexity: O(n + m)
 */
import java.io.*;
import java.util.*;
public class Main {
    static final int MOD = 998244353;
    static int add(int a, int b) {
        int s = a + b;
        if (s >= MOD) s -= MOD;
        return s;
    }
    static int sub(int a, int b) {
        int s = a - b;
        if (s < 0) s += MOD;
        return s;
    }
    static int mul(long a, long b) {
        return (int)((a * b) % MOD);
    }
    static int powMod(int a, long e) {
        long r = 1, x = a;
        while (e > 0) {
            if ((e & 1) != 0) r = (r * x) % MOD;
            x = (x * x) % MOD;
            e >>= 1;
        }
        return (int) r;
    }
    static int inv(int a) {
        return powMod(a, MOD - 2);
    }
    static final class Comb {
        int n;
        int[] fac, invfac, inv;
        Comb(int maxN) {
            init(maxN);
        }
        void init(int m) {
            n = m;
            fac = new int[m + 1];
            invfac = new int[m + 1];
            inv = new int[m + 1];
            fac[0] = 1;
            for (int i = 1; i <= m; i++) fac[i] = mul(fac[i - 1], i);
            invfac[m] = inv(fac[m]);
            for (int i = m; i >= 1; i--) invfac[i - 1] = mul(invfac[i], i);
            inv[0] = 0;
            for (int i = 1; i <= m; i++) inv[i] = mul(invfac[i], fac[i - 1]);
        }
        int fac(int x) { return fac[x]; }
        int invfac(int x) { return invfac[x]; }
        int invInt(int x) { return inv[x]; }
        int binom(int nn, int kk) {
            if (kk < 0 || kk > nn) return 0;
            return mul(fac[nn], mul(invfac[kk], invfac[nn - kk]));
        }
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        int n = fs.nextInt();
        int m = fs.nextInt();
        int k = fs.nextInt();
        int total = n + m;
        int N = n + m - (k - 1);
        int limit = Math.max(total * 2 + 10, N + 10);
        Comb comb = new Comb(limit);
        int[] f = new int[N + 1];
        f[0] = 1;
        for (int i = 0; i < N; i++) {
            long ans = 0;
            for (int j = 0; j <= i; j++) {
                int term = mul(k - 1, comb.invfac(j + 2)); // Coefficient from recurrence relation
                term = mul(term, j + 1);
                term = mul(term, f[i - j]);
                ans += term;
                if (ans >= (1L << 62)) ans %= MOD; // Prevent overflow
            }
            for (int j = 0; j < i; j++) {
                int term = mul(f[j + 1], j + 1);
                term = mul(term, comb.invfac(i - j + 1));
                ans -= term;
            }
            ans %= MOD;
            if (ans < 0) ans += MOD;
            f[i + 1] = mul((int) ans, comb.invInt(i + 1)); // Normalize using inverse factorial
        }
        int[] newF = new int[total + 1];
        Arrays.fill(newF, 0);
        for (int i = 0; i <= N; i++) newF[i + (k - 1)] = f[i]; // Shift indices to match original problem
        for (int i = 0; i <= total; i++) newF[i] = mul(newF[i], comb.fac(i)); // Scale by factorial for multinomial coeffs
        int[] ansArr = new int[total + 1];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int idx = total - Math.max(i, j); // Index in result array corresponds to operation count
                int fIdx = total - i - j; // Index in precomputed array for current operation count
                if (fIdx < 0 || fIdx > total) continue;
                int term = mul(comb.binom(n, i), comb.binom(m, j)); // Number of ways to choose rows and columns
                term = mul(term, newF[fIdx]); // Multiply with precomputed DP value
                ansArr[idx] = add(ansArr[idx], term); // Accumulate results into answer array
            }
        }
        StringBuilder sb = new StringBuilder();
        int start = Math.min(n, m);
        for (int i = start; i < total; i++) {
            sb.append(ansArr[i]);
            if (i + 1 == total) sb.append('\n');
            else sb.append(' ');
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
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }
}


// https://github.com/VaHiX/CodeForces/