// Problem: CF 2167 G - Mukhammadali and the Smooth Array
// https://codeforces.com/contest/2167/problem/G

/*
 * Problem: G. Mukhammadali and the Smooth Array
 * 
 * Algorithm/Approach:
 * - We want to ensure that the array is non-decreasing (no "drops").
 * - This is a dynamic programming problem on a compressed coordinate space.
 * - We use a Fenwick tree (Binary Indexed Tree) to maintain the maximum cost
 *   of a non-decreasing subsequence ending at or before a certain value.
 * - For each element a[i], we find the best previous element (using coordinate compression)
 *   and extend the sequence by adding c[i].
 * - The result is total cost minus the maximum cost of a valid non-decreasing subsequence.
 * 
 * Time Complexity: O(n log n) per test case due to coordinate compression and Fenwick operations
 * Space Complexity: O(n) for storing arrays and Fenwick tree
 */

import java.io.*;
import java.util.*;
public class Main {
    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }
        String next() throws IOException {
            StringBuilder sb = new StringBuilder();
            int c;
            while ((c = read()) <= 32 && c != -1) {}
            if (c == -1) return null;
            do { sb.append((char)c); } while ((c = read()) > 32);
            return sb.toString();
        }
        int nextInt() throws IOException { return Integer.parseInt(next()); }
        long nextLong() throws IOException { return Long.parseLong(next()); }
    }
    static class FenwickMax {
        int n;
        long[] f;
        FenwickMax(int n) { this.n = n; f = new long[n + 1]; }
        void update(int i, long v) { for (; i <= n; i += i & -i) f[i] = Math.max(f[i], v); }
        long query(int i) { long r = 0; for (; i > 0; i -= i & -i) r = Math.max(r, f[i]); return r; }
    }
    static long[] readLongArray(FastScanner fs, int n) throws IOException {
        long[] a = new long[n];
        for (int i = 0; i < n; i++) a[i] = fs.nextLong();
        return a;
    }
    static long sum(long[] a) {
        long s = 0;
        for (long v : a) s += v;
        return s;
    }
    static long[] uniqueSorted(long[] a) {
        long[] b = a.clone();
        Arrays.sort(b);
        int m = 0;
        for (int i = 0; i < b.length; i++) if (i == 0 || b[i] != b[i - 1]) b[m++] = b[i];
        return Arrays.copyOf(b, m);
    }
    static int lowerBound(long[] a, long x) {
        int l = 0, r = a.length;
        while (l < r) {
            int m = (l + r) >>> 1;
            if (a[m] < x) l = m + 1; else r = m;
        }
        return l;
    }
    static long solveCase(int n, long[] a, long[] c) {
        long tot = sum(c); // Total cost of all elements
        long[] comp = uniqueSorted(a); // Compress coordinates to reduce Fenwick size
        FenwickMax fen = new FenwickMax(comp.length);
        long best = 0;
        for (int i = 0; i < n; i++) {
            int idx = lowerBound(comp, a[i]) + 1; // Get compressed index
            long cur = fen.query(idx) + c[i]; // Current best cost ending at or before a[i]
            fen.update(idx, cur); // Update Fenwick tree
            if (cur > best) best = cur; // Keep track of maximum
        }
        return tot - best; // Minimize cost by subtracting maximum valid non-decreasing cost
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();
        String tok = fs.next();
        if (tok == null) { System.out.print(""); return; }
        int t = Integer.parseInt(tok);
        while (t-- > 0) {
            int n = fs.nextInt();
            long[] a = readLongArray(fs, n);
            long[] c = readLongArray(fs, n);
            out.append(solveCase(n, a, c)).append('\n');
        }
        System.out.print(out.toString());
    }
}


// https://github.com/VaHiX/CodeForces/