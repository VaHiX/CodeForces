// Problem: CF 2137 E - Mexification
// https://codeforces.com/contest/2137/problem/E

/*
 * E. Mexification
 *
 * Purpose:
 *   Given an array of integers and a number of operations k, for each operation,
 *   each element is replaced by the MEX (minimum excluded) of all other elements in the array.
 *   This process is repeated k times, and the final sum of the array is returned.
 *
 * Algorithm:
 *   - For each operation, we compute a new array where each element is replaced
 *     with the MEX of all other elements.
 *   - The key insight is that after applying this transformation multiple times,
 *     the sequence stabilizes quickly. In fact, it can be shown that after at most 2 operations,
 *     the values repeat in a cycle.
 *   - Therefore, we only need to compute up to 3 transformations: original array, first transformation, second transformation, and third if needed.
 *
 * Time Complexity:
 *   O(n) per test case. The number of operations is at most 3 (since the pattern repeats), making it effectively constant time per test case.
 *
 * Space Complexity:
 *   O(n). Extra space is used to store arrays for intermediate transformations.
 */

import java.io.*;
import java.util.*;

public class E {
    static final InputStream in = System.in;
    static final PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    static final byte[] buf = new byte[1 << 16];
    static int ptr = 0, len = 0;
    static int read() throws IOException {
        if (ptr >= len) {
            len = in.read(buf);
            ptr = 0;
            if (len <= 0) return -1;
        }
        return buf[ptr++];
    }
    static int ni() throws IOException {
        int c = read();
        while (c <= 32 && c >= 0) c = read();
        int s = 1;
        if (c == '-') { s = -1; c = read(); }
        int val = 0;
        while (c > 32) {
            val = val * 10 + (c - '0');
            c = read();
        }
        return val * s;
    }
    static void p(Object o) { out.print(o); }
    static void pn(Object o) { out.println(o); }
    static void pn() { out.println(); }
    public static void main(String[] args) throws Exception {
        int t = ni();
        while (t-- > 0) solve();
        out.flush();
    }
    static void solve() throws Exception {
        int n = ni();
        long k = ni();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) a[i] = ni();
        if (k == 0) {
            pn(sum(a));
            return;
        }
        int[] b = apply(a, n); // Apply one transformation
        if (k == 1) {
            pn(sum(b));
            return;
        }
        int[] c = apply(b, n); // Apply second transformation
        if (k % 2 == 0) {
            pn(sum(c)); // Result after even number of transformations
        } else {
            int[] d = apply(c, n); // Apply third transformation for odd k
            pn(sum(d));
        }
    }
    static int[] apply(int[] arr, int n) {
        int[] f = new int[n + 2]; // Frequency array to count occurrences
        for (int v : arr) if (v <= n) f[v]++; // Count valid values
        int m = 0;
        while (m <= n && f[m] > 0) m++; // Find MEX of the full array
        int[] res = new int[n];
        for (int i = 0; i < n; i++) {
            int v = arr[i];
            if (v < m && f[v] == 1) res[i] = v; // If value is less than MEX and unique, keep it
            else res[i] = m; // Otherwise replace with MEX
        }
        return res;
    }
    static long sum(int[] a) {
        long s = 0;
        for (int v : a) s += v;
        return s;
    }
}


// https://github.com/VaHiX/codeForces/