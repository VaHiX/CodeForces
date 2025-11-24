// Problem: CF 2167 E - khba Loves to Sleep!
// https://codeforces.com/contest/2167/problem/E

/*
 * Problem: khba Loves to Sleep!
 * Purpose: Place k teleports on a line [0, x] to maximize the minimum time
 *          for any friend to reach the nearest teleport.
 * 
 * Algorithm: Binary search on the answer (distance r) combined with a greedy
 *            placement strategy to place k teleports.
 * 
 * Time Complexity: O(n log n + log(max_x) * n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Binary search on the result (r)
 * - Greedy teleport placement strategy based on the computed r
 * - Efficient I/O using buffered reading
 */

import java.io.*;
import java.util.*;
public class Main {
    static final InputStream in = System.in;
    static final byte[] buf = new byte[1 << 16];
    static int p = 0, m = 0;
    static int read() throws IOException {
        if (p >= m) {
            m = in.read(buf);
            p = 0;
            if (m < 0) return -1;
        }
        return buf[p++];
    }
    static long nextLong() throws IOException {
        int c; long s = 1, x = 0;
        do { c = read(); } while (c <= 32);
        if (c == '-') { s = -1; c = read(); }
        while (c > 32) { x = x * 10 + c - '0'; c = read(); }
        return x * s;
    }
    static long available(long[] a, int n, long x, long r) {
        // Count how many positions can be covered by teleport radius r
        if (r == 0) return x + 1;
        long cover = 0, L = -1, R = -2;
        for (int i = 0; i < n; i++) {
            long l = a[i] - (r - 1), rr = a[i] + (r - 1);
            if (l < 0) l = 0;
            if (rr > x) rr = x;
            if (l > rr) continue;
            if (l > R + 1) {
                // Start a new interval
                if (L != -1) cover += R - L + 1;
                L = l; R = rr;
            } else {
                // Extend the current interval
                if (rr > R) R = rr;
            }
        }
        if (L != -1) cover += R - L + 1;
        // Return unused positions
        return (x + 1) - cover;
    }
    static void emit(long[] a, int n, long x, long r, int k, StringBuilder out) {
        // Place k teleports greedily to achieve the desired radius r
        if (r == 0) {
            // If r=0, place one at each index from 0 to k-1
            for (int i = 0; i < k; i++) {
                if (i > 0) out.append(' ');
                out.append(i);
            }
            out.append('\n');
            return;
        }
        long cur = 0;
        int i = 0, cnt = 0;
        while (cnt < k && cur <= x) {
            long l = a[i] - (r - 1), rr = a[i] + (r - 1);
            if (l < 0) l = 0;
            if (rr > x) rr = x;
            if (cur < l) {
                // Place a teleport at cur
                out.append(cur);
                cnt++;
                if (cnt == k) break;
                out.append(' ');
                cur++;
            } else {
                // Move past the current friend's coverage
                if (cur <= rr) cur = rr + 1;
                i++;
                if (i == n) {
                    // Place remaining teleports
                    while (cnt < k && cur <= x) {
                        if (cnt > 0) out.append(' ');
                        out.append(cur++);
                        cnt++;
                    }
                    break;
                }
            }
        }
        out.append('\n');
    }
    public static void main(String[] args) throws Exception {
        StringBuilder out = new StringBuilder();
        int t = (int) nextLong();
        while (t-- > 0) {
            int n = (int) nextLong();
            int k = (int) nextLong();
            long x = nextLong();
            long[] a = new long[n];
            for (int i = 0; i < n; i++) a[i] = nextLong();
            Arrays.sort(a);
            long lo = 0, hi = x, best = 0;
            while (lo <= hi) {
                long mid = (lo + hi) >>> 1;
                if (available(a, n, x, mid) >= k) {
                    // If we can place k teleports with radius mid, try larger radius
                    best = mid;
                    lo = mid + 1;
                } else hi = mid - 1;
            }
            emit(a, n, x, best, k, out);
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/CodeForces/