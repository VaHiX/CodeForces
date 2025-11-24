// Problem: CF 2124 G - Maximise Sum
// https://codeforces.com/contest/2124/problem/G

/*
 * Problem: G. Maximise Sum
 * Description:
 *   Given an array a of length n with elements 0 <= a[i] <= n,
 *   perform at most one operation where we choose indices i < j and set:
 *     a[i] := a[i] + a[j]
 *     a[j] := 0
 *   The cost of this operation is j - i.
 *   For each x from 0 to n-1, output the maximum possible sum of prefix minimums
 *   over all operations with cost >= x.
 *
 * Algorithms: 
 *   - Prefix and suffix min tracking
 *   - Segment tree / binary search optimization for range queries
 *   - Monotonic stack with dynamic programming optimizations
 *
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n)
 */
import java.io.*;
import java.util.*;
public class Main {
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
            do { c = read(); } while (c <= 32);
            if (c == '-') { s = -1; c = read(); }
            while (c > 32) { x = x * 10 + (c - '0'); c = read(); }
            return x * s;
        }
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();
        int T = fs.nextInt();
        while (T-- > 0) {
            int n = fs.nextInt();
            int[] a = new int[n + 2];
            for (int i = 1; i <= n; i++) a[i] = fs.nextInt();
            long[] best = new long[n];
            Arrays.fill(best, 0L);
            int[] suf = new int[n];
            int sc = 0;
            for (int i = n; i >= 1; i--) {
                if (sc == 0 || a[i] > a[suf[sc - 1]]) suf[sc++] = i;
            }
            int INF = 1_000_000_000;
            int[] MN = new int[n + 1];
            int[] sec_mn = new int[n + 1];
            long[] pref = new long[n + 1];
            long[] pref_sec = new long[n + 1];
            int[] f = new int[n + 2];
            int mn = INF;
            sec_mn[0] = INF;
            MN[0] = INF;
            int ind = -1;
            for (int i = 1; i <= n; i++) {
                sec_mn[i] = sec_mn[i - 1];
                if (a[i] < mn) {
                    if (ind != -1) f[ind] = i;
                    sec_mn[i] = mn;
                    mn = a[i];
                    ind = i;
                } else if (a[i] < sec_mn[i]) {
                    sec_mn[i] = a[i];
                }
                MN[i] = mn;
                pref[i] = pref[i - 1] + mn;
                pref_sec[i] = pref_sec[i - 1] + sec_mn[i];
            }
            f[ind] = n + 1;
            best[0] = pref[n];
            int[] st = new int[n + 2];
            int top = 0;
            a[n + 1] = -INF;
            st[top++] = n + 1;
            for (int i = n; i >= 1; i--) {
                if (MN[i - 1] > a[i]) {
                    for (int k = 0; k < sc; k++) {
                        int id = suf[k];
                        if (id <= i) break;
                        int cur_mn = Math.min(a[i] + a[id], MN[i - 1]);
                        int l = 0, r = top;
                        while (r - l > 1) {
                            int m = (l + r) >>> 1;
                            if (a[st[m]] <= cur_mn) l = m;
                            else r = m;
                        }
                        int upto = Math.min(id - 1, st[l] - 1);
                        long val = pref[i - 1] + 1L * cur_mn * (upto - i + 1); // Compute value for current configuration
                        if (upto + 1 < id) {
                            int upup = Math.min(f[i], id);
                            val += (pref_sec[upup - 1] - pref_sec[upto]);
                            val += (pref[id - 1] - pref[upup - 1]);
                        }
                        int cost = id - i;
                        if (val > best[cost]) best[cost] = val; // Update best answer for given cost
                        if (a[i] + a[id] >= MN[i - 1]) break;
                    }
                }
                while (top > 0 && a[i] <= a[st[top - 1]]) top--;
                st[top++] = i; // Maintain monotonicity in stack
            }
            for (int i = n - 2; i >= 0; i--) if (best[i + 1] > best[i]) best[i] = best[i + 1]; // Propagate maximums backward to get all answers
            for (int i = 0; i < n; i++) {
                out.append(best[i]).append(i + 1 == n ? '\n' : ' ');
            }
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/CodeForces/