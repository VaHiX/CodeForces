// Problem: CF 2146 F - Bubble Sort
// https://codeforces.com/contest/2146/problem/F

/**
 * Problem: Bubble Sort
 * Algorithm: Dynamic Programming with Preprocessing and Binary Search
 * Time Complexity: O(n * sqrt(n) * log(n) + m^2 * log(m))
 * Space Complexity: O(n + m)
 * 
 * This solution uses dynamic programming to count permutations satisfying
 * bubble sort round constraints. It pre-processes valid ranges for each
 * position and uses DP with range queries to compute the number of valid
 * permutations.
 */
import java.io.*;
import java.util.*;
public class Main {
    static final int MOD = 998244353;
    static final int MAXF = 2000005; 
    static final int MAXN = 1000005; 
    static long[] fac = new long[MAXF];
    static long[] inv = new long[MAXF];
    static int[] r1 = new int[MAXN];
    static int[] r2 = new int[MAXN];
    static long qpow(long base, int exp) {
        base %= MOD;
        long res = 1;
        while (exp > 0) {
            if ((exp & 1) == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return res;
    }
    static void initFactorials(int n) {
        fac[0] = 1;
        for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
        inv[n] = qpow(fac[n], MOD - 2);
        for (int i = n - 1; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % MOD;
        inv[0] = 1;
    }
    static long qry1(int l, int r, int k) {
        if (k < l) {
            return qpow((long)(k + 1), r - l + 1);
        }
        if (k > r) {
            return fac[r + 1] * inv[l] % MOD;
        }
        return fac[k + 1] * inv[l] % MOD * qpow((long)(k + 1), r - k) % MOD;
    }
    static long qry2(int l, int r, int k, int x) {
        long a = qry1(l, r, k);
        long b = qry1(l, r, x);
        long res = a - b;
        if (res < 0) res += MOD;
        return res;
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        initFactorials(MAXF - 1);
        int T = fs.nextInt();
        while (T-- > 0) {
            int n = fs.nextInt();
            int m = fs.nextInt();
            int[] vtmp = new int[m * 2 + 5];
            int vlen = 0;
            int[] ttmp = new int[m + 5];
            int tlen = 0;
            int[] kk = new int[m];
            int[] ll = new int[m];
            int[] rr = new int[m];
            for (int i = 0; i < m; i++) {
                int k = fs.nextInt();
                int l = fs.nextInt();
                int r = fs.nextInt();
                l--; // Convert to 0-based indexing
                kk[i] = k;
                ll[i] = l;
                rr[i] = r;
                if (l >= 0) vtmp[vlen++] = l;
                if (r < n) vtmp[vlen++] = r;
                ttmp[tlen++] = k;
            }
            vtmp[vlen++] = n - 1;
            ttmp[tlen++] = -1;
            ttmp[tlen++] = n - 1;
            Arrays.sort(vtmp, 0, vlen);
            int[] v = new int[vlen];
            int vn = 0;
            for (int i = 0; i < vlen; i++) {
                if (i == 0 || vtmp[i] != vtmp[i - 1]) v[vn++] = vtmp[i];
            }
            Arrays.sort(ttmp, 0, tlen);
            int[] t = new int[tlen];
            int tn = 0;
            for (int i = 0; i < tlen; i++) {
                if (i == 0 || ttmp[i] != ttmp[i - 1]) t[tn++] = ttmp[i];
            }
            int defaultR1 = tn - 1;
            for (int i = 0; i < vn; i++) {
                int pos = v[i];
                r1[pos] = defaultR1;
                r2[pos] = 0;
            }
            boolean impossible = false;
            for (int i = 0; i < m; i++) {
                if (kk[i] == n - 1 && rr[i] < n - 1) {
                    impossible = true;
                    break;
                }
            }
            if (impossible) {
                out.append("0\n");
                continue;
            }
            for (int i = 0; i < m; i++) {
                int k = kk[i];
                int l = ll[i];
                int r = rr[i];
                int pos = Arrays.binarySearch(t, 0, tn, k);
                if (pos < 0) pos = -pos - 1;
                if (l >= 0) {
                    r1[l] = Math.min(r1[l], pos);
                }
                if (r < n) {
                    r2[r] = Math.max(r2[r], pos);
                }
            }
            long[] dp = new long[tn + 1];
            long[] sum = new long[tn + 1];
            for (int j = 0; j <= tn; j++) dp[j] = 0;
            dp[1] = 1;
            int lst = 0;
            for (int vi = 0; vi < vn; vi++) {
                int idx = v[vi];
                sum[1] = dp[1] % MOD;
                for (int j = 2; j < tn; j++) sum[j] = (sum[j - 1] + dp[j]) % MOD;
                for (int j = 1; j < tn; j++) {
                    if (j > r2[idx] && j <= r1[idx]) {
                        long term1 = dp[j] * qry1(lst, idx, t[j]) % MOD;
                        long term2 = sum[j - 1] * qry2(lst, idx, t[j], t[j - 1]) % MOD;
                        dp[j] = (term1 + term2) % MOD;
                    } else {
                        dp[j] = 0;
                    }
                }
                lst = idx + 1;
            }
            long ans = 0;
            for (int j = 1; j < tn; j++) ans = (ans + dp[j]) % MOD;
            out.append(ans).append('\n');
        }
        System.out.print(out.toString());
    }
    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        FastScanner(InputStream is) { in = is; }
        private int read() throws IOException {
            if (ptr >= len) {
                ptr = 0;
                len = in.read(buffer);
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        int nextInt() throws IOException {
            int c;
            do { c = read(); } while (c <= ' ' && c >= 0);
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