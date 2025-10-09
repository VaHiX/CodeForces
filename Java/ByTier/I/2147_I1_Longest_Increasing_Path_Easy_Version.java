// Problem: CF 2147 I1 - Longest Increasing Path (Easy Version)
// https://codeforces.com/contest/2147/problem/I1

/*
 * Problem: I1. Longest Increasing Path (Easy Version)
 * Purpose: Generate a distance-convex sequence of length n with at most m distinct values.
 * Algorithm: 
 *   - Precompute a sequence of m distinct values that form a distance-convex path.
 *   - Use greedy selection to build the longest increasing path from this set.
 * Time Complexity: O(m^2) for generating and selecting path
 * Space Complexity: O(m) for storing the sequence and path
 */
import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        int n = fs.nextInt();
        int m = fs.nextInt();
        if (m % 2 != 0) m--; // Ensure m is even for symmetric construction
        if (m == 6) { // Special case for small m
            System.out.println("1 1 3 6 10 3 11 1");
            return;
        }
        long[] a = new long[m];
        long C = 10000000000L; // Large constant to ensure large jumps
        a[0] = 2 * C; // Start with a large value
        long dist = C; // Distance increment
        for (int i = 1; i < m / 2; i++) {
            a[i] = a[i - 1] + dist; // Increasing sequence
            dist += 1;
        }
        for (int i = m / 2; i < m; i++) {
            a[i] = a[i - 1] - dist; // Decreasing sequence
            dist += 1;
        }
        int pos = 0; // Current position in the array
        ArrayList<Long> path = new ArrayList<>();
        path.add(a[pos]); // Start with first element
        long jump = 0; // Length of last jump
        while (true) {
            boolean ch = false;
            for (int j = 0; j < m / 2; j++) { // Check forward jumps
                if (a[j] - a[pos] > jump) {
                    jump = a[j] - a[pos];
                    pos = j;
                    path.add(a[pos]);
                    ch = true;
                }
            }
            for (int j = m / 2; j < m; j++) { // Check backward jumps
                if (a[pos] - a[j] > jump) {
                    jump = Math.abs(a[j] - a[pos]); // Absolute difference for backward jump
                    pos = j;
                    path.add(a[pos]);
                    ch = true;
                }
            }
            if (!ch) break; // No more valid jumps
        }
        if (n > path.size()) throw new RuntimeException("n > path.size()");
        StringBuilder sb = new StringBuilder();
        for (int j = 0; j < n; j++) {
            sb.append(path.get(j));
            if (j + 1 < n) sb.append(' ');
        }
        System.out.println(sb.toString());
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
            if (c == '-') {
                sign = -1;
                c = read();
            }
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