// Problem: CF 2145 E - Predicting Popularity
// https://codeforces.com/contest/2145/problem/E

/*
E. Predicting Popularity

Algorithms/Techniques:
- Segment Tree with Range Minimum/Maximum Queries
- Binary Search on the answer using segment tree properties
- Dynamic updates and queries

Time Complexity: 
- Building the segment tree: O(n)
- Each update operation: O(log n)
- Each query (findZero): O(log n)
- Total for m operations: O(m * log n)

Space Complexity:
- Segment tree storage: O(n)
- Additional arrays: O(n)
- Overall space complexity: O(n)

The problem models a dynamic process where users watch a movie based on how many people have already watched it.
We use a segment tree to efficiently maintain and query the cumulative sum and range min/max values,
which helps us determine when a user becomes eligible to watch the movie.
Each update modifies the count of users at specific thresholds, and we recursively check
if there's a valid position where the cumulative sum hits zero (indicating all eligible users have watched it).
*/

import java.io.*;
public class Main {
    static class FastScanner {
        private final byte[] buf = new byte[1 << 16];
        private int len = 0, ptr = 0;
        private final InputStream in;
        FastScanner(InputStream in) { this.in = in; }
        int nextInt() throws IOException {
            int c; while ((c = read()) <= ' ' && c != -1);
            int s = 1, x = 0;
            if (c == '-') { s = -1; c = read(); }
            for (; c > ' '; c = read()) x = x * 10 + (c - '0');
            return x * s;
        }
        private int read() throws IOException {
            if (ptr >= len) { len = in.read(buf); ptr = 0; if (len <= 0) return -1; }
            return buf[ptr++];
        }
    }
    static int n;
    static int[] w, sum, minP, maxP;
    static void pull(int v) {
        int l = v << 1, r = l | 1;
        sum[v] = sum[l] + sum[r];
        minP[v] = Math.min(minP[l], sum[l] + minP[r]);
        maxP[v] = Math.max(maxP[l], sum[l] + maxP[r]);
    }
    static void build(int v, int l, int r) {
        if (l == r) sum[v] = minP[v] = maxP[v] = w[l];
        else {
            int m = (l + r) >>> 1, L = v << 1;
            build(L, l, m); build(L | 1, m + 1, r); pull(v);
        }
    }
    static void update(int v, int l, int r, int i, int d) {
        if (l == r) sum[v] = minP[v] = maxP[v] = (w[i] += d);
        else {
            int m = (l + r) >>> 1, L = v << 1;
            if (i <= m) update(L, l, m, i, d);
            else update(L | 1, m + 1, r, i, d);
            pull(v);
        }
    }
    static int findZero(int v, int l, int r, int s, int acc) {
        if (r < s || acc + minP[v] > 0 || acc + maxP[v] < 0) return -1;
        if (l == r) return acc + sum[v] == 0 ? l : -1;
        int m = (l + r) >>> 1, L = v << 1;
        int res = findZero(L, l, m, s, acc);
        return res != -1 ? res : findZero(L | 1, m + 1, r, s, acc + sum[L]);
    }
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        int ac = fs.nextInt(), dr = fs.nextInt();
        n = fs.nextInt();
        int[] a = new int[n + 1], d = new int[n + 1], cnt = new int[n + 1];
        for (int i = 1; i <= n; i++) a[i] = fs.nextInt();
        for (int i = 1; i <= n; i++) d[i] = fs.nextInt();
        for (int i = 1; i <= n; i++) {
            int r = Math.max(a[i] - ac, 0) + Math.max(d[i] - dr, 0);
            if (r <= n) cnt[r]++;
        }
        w = new int[n + 1];
        w[0] = cnt[0];
        for (int i = 1; i <= n; i++) w[i] = cnt[i] - 1;
        int sz = 4 * (n + 2);
        sum = new int[sz]; minP = new int[sz]; maxP = new int[sz];
        build(1, 0, n);
        StringBuilder out = new StringBuilder();
        int m = fs.nextInt();
        for (int q = 0; q < m; q++) {
            int k = fs.nextInt(), na = fs.nextInt(), nd = fs.nextInt();
            int oldr = Math.max(a[k] - ac, 0) + Math.max(d[k] - dr, 0);
            int newr = Math.max(na - ac, 0) + Math.max(nd - dr, 0);
            a[k] = na; d[k] = nd;
            if (oldr <= n) update(1, 0, n, oldr, -1);
            if (newr <= n) update(1, 0, n, newr, +1);
            int start = Math.max(0, w[0]);
            int res = findZero(1, 0, n, start, 0);
            out.append(res == -1 ? 0 : res).append('\n');
        }
        System.out.print(out);
    }
}


// https://github.com/VaHiX/CodeForces/